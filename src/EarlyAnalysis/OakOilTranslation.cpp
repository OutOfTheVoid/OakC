#include <EarlyAnalysis/OakOilTranslation.h>

#include <OIL/OilTypeRef.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateSpecification.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilFunctionParameterList.h>

#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakNamespaceDefinitionConstructor.h>
#include <Parsing/Language/OakStructDefinitionConstructor.h>
#include <Parsing/Language/OakUnrestrictedTemplateParameterConstructor.h>
#include <Parsing/Language/OakRestrictedTemplateParameterConstructor.h>
#include <Parsing/Language/OakBareTraitNameConstructor.h>
#include <Parsing/Language/OakTemplatedTraitNameConstructor.h>
#include <Parsing/Language/OakNamespacedTraitNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTraitNameConstructor.h>
#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakTemplateSpecificationConstructor.h>
#include <Parsing/Language/OakStructBindingConstructor.h>
#include <Parsing/Language/OakFunctionDefinitionConstructor.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

#include <Compilation/CompilationUnit.h>

void WriteError ( const ASTElement * SourceRef, std :: string Error );

bool OakTranslateNamespaceTreeToOil ( const ASTElement * NamespaceElement, OilNamespaceDefinition & Container );
bool OakTranslateStructTreeToOil ( const ASTElement * StructElement, OilNamespaceDefinition & Container );
OilTemplateDefinition * OakTranslateTemplateDefinitionToOil ( const ASTElement * TemplateDefinitionElement );
OilTemplateSpecification * OakTranslateTemplateSpecificationToOil ( const ASTElement * TemplateSpecificationElement );
OilTypeRef * OakTranslateTraitRefToOil ( const ASTElement * TypeElement );
OilTypeRef * OakTranslateTypeRefToOil ( const ASTElement * TypeElement );
OilStructBinding * OakTranslateStructBindingToOil ( const ASTElement * BindingElement );
OilFunctionDefinition * OakTranslateFunctionDefinitionToOil ( const ASTElement * FunctionDefElement );
OilFunctionParameterList * OakTranslateFunctionParameterListToOil ( const ASTElement * ParameterListElement );

bool OakTranslateFileTreeToOil ( const ASTElement * TreeRoot, OilNamespaceDefinition & GlobalNS )
{
	
	if ( ( TreeRoot == NULL ) || ( TreeRoot -> GetTag () != OakASTTags :: kASTTag_File ) )
	{
		
		LOG_FATALERROR ( "Invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	uint64_t SubElementCount = TreeRoot -> GetSubElementCount ();
	
	for ( uint64_t I = 0; I < SubElementCount; I ++ )
	{
		
		const ASTElement * SubElement = TreeRoot -> GetSubElement ( I );
		
		switch ( SubElement -> GetTag () )
		{
			
			case OakASTTags :: kASTTag_ImportStatement:
			break;
			
			case OakASTTags :: kASTTag_StructDefinition:
			{
				
				if ( ! OakTranslateStructTreeToOil ( SubElement, GlobalNS ) )
					return false;
				
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
	
	if ( ( NamespaceElement == NULL ) || ( NamespaceElement -> GetTag () != OakASTTags :: kASTTag_NamespaceDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
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
				
				if ( ! OakTranslateStructTreeToOil ( SubElement, * DefinedNamespaceDefinition ) )
					return false;
				
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
	
	if ( ( StructElement == NULL ) || ( StructElement -> GetTag () != OakASTTags :: kASTTag_StructDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const OakStructDefinitionConstructor :: ElementData * StructData = reinterpret_cast <const OakStructDefinitionConstructor :: ElementData *> ( StructElement -> GetData () );
	
	if ( Container.FindStructDefinition ( StructData -> Name ) != NULL )
	{
		
		WriteError ( StructElement, "Duplicate struct definition: " + CodeConversion :: ConvertUTF32ToUTF8 ( StructData -> Name ) );
		
		return false;
		
	}
	
	uint64_t SubElementCount = StructElement -> GetSubElementCount ();
	
	if ( StructData -> Templated )
	{
		
		OilTemplateDefinition * TemplateDefinition = OakTranslateTemplateDefinitionToOil ( StructElement -> GetSubElement ( 0 ) );
		
		if ( TemplateDefinition == NULL )
			return false;
		
		OilStructDefinition * StructDef = new OilStructDefinition ( StructData -> Name, TemplateDefinition );
		
		for ( uint64_t I = 1; I < SubElementCount; I ++ )
		{
			
			const ASTElement * BindingElement = StructElement -> GetSubElement ( I );
			
			OilStructBinding * Binding = OakTranslateStructBindingToOil ( BindingElement );
			
			if ( Binding == NULL )
			{
				
				delete StructDef;
				
				return false;
				
			}
			
			StructDef -> AddBinding ( Binding );
			
		}
		
		Container.AddStructDefinition ( StructDef );
		
	}
	else
	{
		
		OilStructDefinition * StructDef = new OilStructDefinition ( StructData -> Name );
		
		for ( uint64_t I = 0; I < SubElementCount; I ++ )
		{
			
			const ASTElement * BindingElement = StructElement -> GetSubElement ( I );
			
			OilStructBinding * Binding = OakTranslateStructBindingToOil ( BindingElement );
			
			if ( Binding == NULL )
			{
				
				delete StructDef;
				
				return false;
				
			}
			
			StructDef -> AddBinding ( Binding );
			
		}
		
		Container.AddStructDefinition ( StructDef );
		
	}
	
	return true;
	
}

OilTemplateDefinition * OakTranslateTemplateDefinitionToOil ( const ASTElement * TemplateDefinitionElement )
{
	
	if ( ( TemplateDefinitionElement == NULL ) || ( TemplateDefinitionElement -> GetTag () != OakASTTags :: kASTTag_TemplateDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	if ( TemplateDefinitionElement -> GetTag () != OakASTTags :: kASTTag_TemplateDefinition )
		return NULL;
	
	OilTemplateDefinition * Result = new OilTemplateDefinition ();
	
	uint64_t SubElementCount = TemplateDefinitionElement -> GetSubElementCount ();
	
	for ( uint64_t I = 0; I < SubElementCount; I ++ )
	{
		
		const ASTElement * ParamElement = TemplateDefinitionElement -> GetSubElement ( I );
		
		if ( ParamElement -> GetTag () == OakASTTags :: kASTTag_UnrestrictedTemplateParameter )
		{
			
			const OakUnrestrictedTemplateParameterConstructor :: ElementData * ParamData = reinterpret_cast <const OakUnrestrictedTemplateParameterConstructor :: ElementData *> ( ParamElement -> GetData () );
			
			Result -> AddParameter ( new OilTemplateDefinitionParameter ( ParamData -> Name ) );
			
		}
		else if ( ParamElement -> GetTag () == OakASTTags :: kASTTag_RestrictedTemplateParameter )
		{
			
			const OakRestrictedTemplateParameterConstructor :: ElementData * ParamData = reinterpret_cast <const OakRestrictedTemplateParameterConstructor :: ElementData *> ( ParamElement -> GetData () );
			
			uint64_t RestrictionCount = ParamElement -> GetSubElementCount ();
			
			std :: vector <OilTypeRef *> RestrictionTypes;
			
			for ( uint64_t J = 0; J < RestrictionCount; J ++ )
			{
				
				const ASTElement * RestrictionElement = ParamElement -> GetSubElement ( J );
				
				OilTypeRef * Trait = OakTranslateTraitRefToOil ( RestrictionElement );
				
				if ( Trait == NULL )
				{
					
					for ( uint64_t K = 0; K < RestrictionTypes.size (); K ++ )
						delete RestrictionTypes [ K ];
						
					delete Result;
					
					return NULL;
					
				}
				
				RestrictionTypes.push_back ( Trait );
				
			}
			
			Result -> AddParameter ( new OilTemplateDefinitionParameter ( ParamData -> Name, & RestrictionTypes [ 0 ], RestrictionTypes.size () ) );
			
		}
		else
		{
			
			delete Result;
			
			return NULL;
			
		}
		
	}
	
	return Result;
	
}

OilTemplateSpecification * OakTranslateTemplateSpecificationToOil ( const ASTElement * TemplateSpecificationElement )
{
	
	if ( ( TemplateSpecificationElement == NULL ) || ( TemplateSpecificationElement -> GetTag () != OakASTTags :: kASTTag_TemplateSpecification ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	uint64_t SubElementCount = TemplateSpecificationElement -> GetSubElementCount ();
	
	std :: vector <OilTypeRef *> TypeList;
	
	for ( uint64_t I = 0; I < SubElementCount; I ++ )
	{
		
		OilTypeRef * Type = OakTranslateTypeRefToOil ( TemplateSpecificationElement -> GetSubElement ( I ) );
		
		if ( Type == NULL )
		{
			
			for ( uint64_t J = 0; J < TypeList.size (); J ++ )
				delete TypeList [ J ];
			
			return NULL;
			
		}
		
		TypeList.push_back ( Type );
		
	}
	
	const OakTemplateSpecificationConstructor :: ElementData * SpecificationData = reinterpret_cast <const OakTemplateSpecificationConstructor :: ElementData *> ( TemplateSpecificationElement -> GetData () );
	
	return new OilTemplateSpecification ( & TypeList [ 0 ], TypeList.size () );
	
}

OilTypeRef * OakTranslateTraitRefToOil ( const ASTElement * TraitElement )
{
	
	if ( TraitElement == NULL )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	switch ( TraitElement -> GetTag () )
	{
		
		case OakASTTags :: kASTTag_TraitName_Bare:
		{
			
			const OakBareTraitNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakBareTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			return new OilTypeRef ( RestrictionData -> Name, OilTypeRef :: kRefFlag_Trait );
			
		}
		
		case OakASTTags :: kASTTag_TraitName_Templated:
		{
			
			const OakTemplatedTraitNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakTemplatedTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TraitElement -> GetSubElement ( 0 ) );
			
			return new OilTypeRef ( RestrictionData -> Name, TemplateSpecification, OilTypeRef :: kRefFlag_Trait );
			
		}
		
		case OakASTTags :: kASTTag_TraitName_Namespaced:
		{
			
			const OakNamespacedTraitNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakNamespacedTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			return new OilTypeRef ( RestrictionData -> Name, RestrictionData -> IdentList, RestrictionData -> IdentListLength, OilTypeRef :: kRefFlag_Trait );
			
		}
		
		case OakASTTags :: kASTTag_TraitName_NamespacedTemplated:
		{
			
			const OakNamespacedTemplatedTraitNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakNamespacedTemplatedTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TraitElement -> GetSubElement ( 0 ) );
			
			return new OilTypeRef ( RestrictionData -> Name, RestrictionData -> IdentList, RestrictionData -> IdentListLength, TemplateSpecification, OilTypeRef :: kRefFlag_Trait );
			
		}
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
	
	return NULL;
	
}

OilTypeRef * OakTranslateTypeRefToOil ( const ASTElement * TypeElement )
{
	
	if ( TypeElement == NULL )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	switch ( TypeElement -> GetTag () )
	{
		
		case OakASTTags :: kASTTag_TypeName_Bare:
		{
			
			const OakBareTypeNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakBareTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			return new OilTypeRef ( RestrictionData -> TypeName );
			
		}
		
		case OakASTTags :: kASTTag_TypeName_Templated:
		{
			
			const OakTemplatedTypeNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakTemplatedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TypeElement -> GetSubElement ( 0 ) );
			
			if ( TemplateSpecification == NULL )
				return NULL;
			
			return new OilTypeRef ( RestrictionData -> TypeName, TemplateSpecification );
			
		}
		
		case OakASTTags :: kASTTag_TypeName_Namespaced:
		{
			
			const OakNamespacedTypeNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakNamespacedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			return new OilTypeRef ( RestrictionData -> TypeName, RestrictionData -> IdentList, RestrictionData -> IdentListLength );
			
		}
		
		case OakASTTags :: kASTTag_TypeName_NamespacedTemplated:
		{
			
			const OakNamespacedTemplatedTypeNameConstructor :: ElementData * RestrictionData = reinterpret_cast <const OakNamespacedTemplatedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TypeElement -> GetSubElement ( 0 ) );
			
			if ( TemplateSpecification == NULL )
				return NULL;
			
			return new OilTypeRef ( RestrictionData -> TypeName, RestrictionData -> IdentList, RestrictionData -> IdentListLength, TemplateSpecification );
			
		}
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
	
	return NULL;
	
}

OilStructBinding * OakTranslateStructBindingToOil ( const ASTElement * BindingElement )
{
	
	if ( BindingElement == NULL )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const ASTElement * TypeElement = BindingElement -> GetSubElement ( 0 );
	
	OilTypeRef * BindingType = OakTranslateTypeRefToOil ( TypeElement );
	
	if ( BindingType == NULL )
		return NULL;
	
	const OakStructBindingConstructor :: ElementData * BindingData = reinterpret_cast <const OakStructBindingConstructor :: ElementData *> ( BindingElement -> GetData () );
	
	return new OilStructBinding ( BindingData -> Name, BindingType );
	
}

OilFunctionDefinition * OakTranslateFunctionDefinitionToOil ( const ASTElement * FunctionDefElement )
{
	
	if ( ( FunctionDefElement == NULL ) || ( FunctionDefElement -> GetTag () != OakASTTags :: kASTTag_FunctionDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const OakFunctionDefinitionConstructor :: ElementData * FunctionDefData = reinterpret_cast <const OakFunctionDefinitionConstructor :: ElementData *> ( FunctionDefElement -> GetData () );
	
	/*if ( FunctionDefData -> Templated )
	{
		
		OilTemplateDefinition * TemplateDefinition = OakTranslateTemplateDefinitionToOil ( FunctionDefElement -> GetSubElement ( 0 ) );
		
		if ( TemplateDefinition == NULL )
			return NULL;
		
		OilFunctionParameterList * FunctionParamList = OakTranslateFunctionParameterListToOil ( FunctionDefElement -> GetSubElement ( 1 ) );
		
		if ( StatementBody == NULL )
		{
			
			delete TemplateDefinition;
			
			return NULL;
			
		}
		
		if ( FunctionDefData -> ReturnTyped )
		{
			
			OilTypeRef * ReturnType = OakTranslateReturnType ( FunctionDefElement -> GetSubElement ( 2 ) );
			
			if ( ReturnType == NULL )
			{
				
				delete TemplateDefinition;
				delete FunctionParamList;
				
				return NULL;
				
			}
			
			OilStatementBody * StatementBody = OakTranslateStatementBody ( FunctionDefElement -> GetSubElement ( 3 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete TemplateDefinition;
				delete FunctionParamList;
				delete ReturnType;
				
				return NULL;
				
			}
			
			return new OilFunctionDefinition ( FunctionDefData -> Name, FunctionDefData -> Public, FunctionDefData -> Inline, FunctionParamList, StatementBody, ReturnType, TemplateDefinition );
			
		}
		else
		{
			
			OilStatementBody * StatementBody = OakTranslateStatementBody ( FunctionDefElement -> GetSubElement ( 2 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete TemplateDefinition;
				delete FunctionParamList;
				delete ReturnType;
				
				return NULL;
				
			}
			
			return new OilFunctionDefinition ( FunctionDefData -> Name, FunctionDefData -> Public, FunctionDefData -> Inline, FunctionParamList, StatementBody, NULL, TemplateDefinition );
			
		}
		
	}
	else
	{
		
		OilFunctionParameterList * FunctionParamList = OakFunctionParameterList ( FunctionDefElement -> GetSubElement ( 0 ) );
		
		if ( StatementBody == NULL )
			return NULL;
		
		if ( FunctionDefData -> ReturnTyped )
		{
			
			OilTypeRef * ReturnType = OakTranslateReturnType ( FunctionDefElement -> GetSubElement ( 1 ) );
			
			if ( ReturnType == NULL )
			{
				
				delete FunctionParamList;
				
				return NULL;
				
			}
			
			OilStatementBody * StatementBody = OakTranslateStatementBody ( FunctionDefElement -> GetSubElement ( 2 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete FunctionParamList;
				delete ReturnType;
				
				return NULL;
				
			}
			
			return new OilFunctionDefinition ( FunctionDefData -> Name, FunctionDefData -> Public, FunctionDefData -> Inline, FunctionParamList, StatementBody, ReturnType );
			
		}
		else
		{
			
			OilStatementBody * StatementBody = OakTranslateStatementBody ( FunctionDefElement -> GetSubElement ( 1 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete FunctionParamList;
				
				return NULL;
				
			}
			
			return new OilFunctionDefinition ( FunctionDefData -> Name, FunctionDefData -> Public, FunctionDefData -> Inline, FunctionParamList, StatementBody, NULL );
			
		}
		
	}*/
	
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

OilFunctionParameterList * OakTranslateFunctionParameterListToOil ( const ASTElement * ParameterListElement )
{
	
	if ( ( ParameterListElement == NULL ) || ( ParameterListElement -> GetTag () != OakASTTags :: kASTTag_FunctionParameterList ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	
	
}
