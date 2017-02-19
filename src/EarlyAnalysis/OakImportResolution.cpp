#include <EarlyAnalysis/OakImportResolution.h>
#include <EarlyAnalysis/OakLiteralParsing.h>

#include <Compilation/CompilationUnit.h>

#include <Parsing/ASTElement.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakImportStatementConstructor.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

bool GetImportName ( const ASTElement * ImportStatementElement, std :: u32string & FileName, std :: string & ParseError );

bool OakResolveImports ( const ASTElement * FileRootElement, const std :: string & SourceFileName, FileTable & GlobalFileTable, std :: vector <CompilationUnit *> & UnitsOut )
{
	
	uint64_t SubElementCount = FileRootElement -> GetSubElementCount ();
	uint64_t I = 0;
	
	while ( I < SubElementCount )
	{
		
		const ASTElement * SubElement = FileRootElement -> GetSubElement ( I );
		
		if ( SubElement -> GetTag () == OakASTTags :: kASTTag_ImportStatement )
		{
			
			std :: u32string FileName;
			std :: string ParseError;
			
			if ( ! GetImportName ( SubElement, FileName, ParseError ) )
			{
					
				const Token * FirstToken = SubElement -> GetToken ( 0, 0 );
				
				if ( FirstToken == NULL )
					LOG_ERROR ( "Null first token for import statement" );
				
				LOG_ERROR_NOFILE ( ParseError );
				LOG_ERROR_NOFILE ( SourceFileName + " Line " + std :: to_string ( FirstToken -> GetLine () ) + ", Char " + std :: to_string ( FirstToken -> GetChar () ) + ": " + ParseError );
				
				return false;
				
			}
			
			std :: string UTF8FileName = CodeConversion :: ConvertUTF32ToUTF8 ( FileName );
			
			CompilationUnit * FileUnit = GlobalFileTable.GetUnit ( UTF8FileName );
			
			if ( FileUnit == NULL )
			{
				
				FileUnit = new CompilationUnit ( UTF8FileName );
				
				if ( ! FileUnit -> RunIndependantCompilationSteps ( GlobalFileTable ) )
					return false;
					
			}
			
			UnitsOut.push_back ( FileUnit );
			
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
