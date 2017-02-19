#include <EarlyAnalysis/OakOilTranslation.h>

#include <OIL/OilNamespaceDefinition.h>

#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakNamespaceDefinitionConstructor.h>
#include <Parsing/Language/OakStructDefinitionConstructor.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

#include <Compilation/CompilationUnit.h>

void WriteError ( const ASTElement * SourceRef, std :: string Error );

bool OakTranslateNamespaceTreeToOil ( const ASTElement * NamespaceElement, OilNamespaceDefinition & Container );
bool OakTranslateStructTreeToOil ( const ASTElement * StructElement, OilNamespaceDefinition & Container );

bool OakTranslateFileTreeToOil ( const ASTElement * TreeRoot, OilNamespaceDefinition & GlobalNS )
{
	
	uint64_t SumElementCount = TreeRoot -> GetSubElementCount ();
		
	for ( uint64_t I = 0; I < SumElementCount; I ++ )
	{
		
		const ASTElement * SubElement = TreeRoot -> GetSubElement ( I );
		
		switch ( SubElement -> GetTag () )
		{
			
			case OakASTTags :: kASTTag_ImportStatement:
			break;
			
			case OakASTTags :: kASTTag_StructDefinition:
			{
				
				
				
			}
			break;
			
			case OakASTTags :: kASTTag_NamespaceDefinition:
			{
				
				if ( ! OakTranslateNamespaceTreeToOil ( SubElement, GlobalNS ) )
					return false;
				
			}
			break;
			
			default:
			break;
			
		}
		
	}
	
	return true;
	
}

bool OakTranslateNamespaceTreeToOil ( const ASTElement * NamespaceElement, OilNamespaceDefinition & Container )
{
	
	OilNamespaceDefinition * DefinedNamespaceDefinition = NULL;
	
	const OakNamespaceDefinitionConstructor :: ElementData * NamespaceData = reinterpret_cast <const OakNamespaceDefinitionConstructor :: ElementData *> ( NamespaceElement -> GetData () );
	
	if ( NamespaceData -> DirectGlobalReference )
		DefinedNamespaceDefinition = Container.FindOrCreateNamespaceDefinition ( NamespaceData -> Name );
	else
	{
		
		OilNamespaceDefinition * ParentDefinition = Container.FindOrCreateNamespaceDefinition ( NamespaceData -> IdentList [ 0 ] );
		
		for ( uint32_t I = 1; I < NamespaceData -> IdentListLength; I ++ )
			ParentDefinition = ParentDefinition -> FindOrCreateNamespaceDefinition ( NamespaceData -> IdentList [ I ] );
		
		DefinedNamespaceDefinition = ParentDefinition -> FindOrCreateNamespaceDefinition ( NamespaceData -> Name );
		
	}
	
	uint64_t SumElementCount = NamespaceElement -> GetSubElementCount ();
	
	for ( uint64_t I = 0; I < SumElementCount; I ++ )
	{
		
		const ASTElement * SubElement = NamespaceElement -> GetSubElement ( I );
		
		switch ( SubElement -> GetTag () )
		{
			
			case OakASTTags :: kASTTag_StructDefinition:
			{
				
				
				
			}
			break;
			
			case OakASTTags :: kASTTag_NamespaceDefinition:
			{
				
				if ( ! OakTranslateNamespaceTreeToOil ( SubElement, * DefinedNamespaceDefinition ) )
					return false;
				
			}
			break;
			
		}
		
	}
	
	return true;
	
}

bool OakTranslateStructTreeToOil ( const ASTElement * StructElement, OilNamespaceDefinition & Container )
{
	
	const OakStructDefinitionConstructor :: ElementData * StructData = reinterpret_cast <const OakStructDefinitionConstructor :: ElementData *> ( StructElement -> GetData () );
	
	if ( Container.FindStructDefinition ( StructData -> Name ) != NULL )
	{
		
		WriteError ( StructElement, "Duplicate struct definition: " + CodeConversion :: ConvertUTF32ToUTF8 ( StructData -> Name ) );
		
		return false;
		
	}
	
	uint64_t SumElementCount = StructElement -> GetSubElementCount ();
	
	if ( StructData -> Templated )
	{
		
		
		
	}
	else
	{
		
		for ( uint64_t I = 0; I < SumElementCount; I ++ )
		{
			
			
			
		}
		
	}
	
}

void WriteError ( const ASTElement * SourceRefElement, std :: string Error )
{
	
	const Token * SourceToken = SourceRefElement -> GetToken ( 0, 0 );
	
	if ( SourceToken == NULL )
	{
		
		const ASTElement * ChildElement = SourceRefElement -> GetSubElement ( 0 );
		
		if ( ChildElement == NULL )
		{
			
			LOG_ERROR_NOFILE ( Error );
			
			return;
			
		}
		
		WriteError ( ChildElement, Error );
		
		return;
		
	}
	
	LOG_ERROR_NOFILE ( SourceToken -> GetSourceUnit () -> GetFileName () + " Line " + std :: to_string ( SourceToken -> GetLine () ) + ", Char " + std :: to_string ( SourceToken -> GetChar () ) + ": " + Error );
	
}
