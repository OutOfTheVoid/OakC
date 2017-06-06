#include <EarlyAnalysis/OakImportResolution.h>
#include <EarlyAnalysis/OakLiteralParsing.h>
#include <EarlyAnalysis/OakOilTranslation.h>
#include <EarlyAnalysis/OilDecorators.h>

#include <OIL/OilDecoratorTag.h>

#include <Compilation/CompilationUnit.h>

#include <Parsing/ASTElement.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakImportStatementConstructor.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

bool GetImportName ( const ASTElement * ImportStatementElement, std :: u32string & FileName, std :: string & ParseError );

bool OakResolveImports ( const ASTElement * FileRootElement, const std :: string & SourceFileName, FileTable & GlobalFileTable, std :: vector <CompilationUnit *> & UnitsOut, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount )
{
	
	uint64_t SubElementCount = FileRootElement -> GetSubElementCount ();
	uint64_t I = 0;
	
	std :: vector <const OilDecoratorTag *> ConditionalTags;
	
	while ( I < SubElementCount )
	{
		
		const ASTElement * SubElement = FileRootElement -> GetSubElement ( I );
		
		if ( SubElement -> GetTag () == OakASTTags :: kASTTag_DecoratorTag )
		{
			
			OilDecoratorTag * Tag = OakTranslateDecoratorTagToOil ( SubElement );
			
			if ( Tag == NULL )
			{
				
				for ( uint32_t I = 0; I < ConditionalTags.size (); I ++ )
					delete ConditionalTags [ I ];
				
				return false;
				
			}
			
			ConditionalTags.push_back ( Tag );
			
		}
		else if ( SubElement -> GetTag () == OakASTTags :: kASTTag_ImportStatement )
		{
			
			std :: u32string FileName;
			std :: string ParseError;
			
			if ( ! GetImportName ( SubElement, FileName, ParseError ) )
			{
					
				const Token * FirstToken = SubElement -> GetToken ( 0, 0 );
				
				if ( FirstToken == NULL )
					LOG_ERROR ( "Null first token for import statement" );
				
				LOG_ERROR_NOFILE ( ParseError );
				LOG_ERROR_NOFILE ( SourceFileName + " Line " + std :: to_string ( FirstToken -> GetSourceRef ().GetLine () ) + ", Char " + std :: to_string ( FirstToken -> GetSourceRef ().GetChar () ) + ": " + ParseError );
				
				return false;
				
			}
			
			if ( ( ConditionalTags.size () == 0 ) || TestConditionalCompilationDecorators ( & ConditionalTags [ 0 ], ConditionalTags.size (), CompilationConditions, CompilationConditionCount ) )
			{
				
				std :: string UTF8FileName = CodeConversion :: ConvertUTF32ToUTF8 ( FileName );
				
				CompilationUnit * FileUnit = GlobalFileTable.GetUnit ( UTF8FileName );
				
				if ( FileUnit == NULL )
				{
					
					FileUnit = new CompilationUnit ( UTF8FileName );
					
					if ( ! FileUnit -> RunIndependantCompilationSteps ( GlobalFileTable, CompilationConditions, CompilationConditionCount ) )
						return false;
						
				}
				
				UnitsOut.push_back ( FileUnit );
				
			}
			
			for ( uint32_t I = 0; I < ConditionalTags.size (); I ++ )
				delete ConditionalTags [ I ];
			
			ConditionalTags.clear ();
			
		}
		else
		{
			
			for ( uint32_t I = 0; I < ConditionalTags.size (); I ++ )
				delete ConditionalTags [ I ];
			
			ConditionalTags.clear ();
			
		}
		
		I ++;
		
	}
	
	return true;
	
}

bool GetImportName ( const ASTElement * ImportStatementElement, std :: u32string & FileName, std :: string & ParseError )
{
	
	const OakImportStatementConstructor :: ElementData * ImportData = reinterpret_cast <const OakImportStatementConstructor :: ElementData *> ( ImportStatementElement -> GetData () );
	
	return OakParseStringLiteral ( ImportData -> ImportFilenameLiteral, FileName, ParseError );
	
}
