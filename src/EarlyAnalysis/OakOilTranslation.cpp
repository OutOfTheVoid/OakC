#include <EarlyAnalysis/OakOilTranslation.h>
#include <EarlyAnalysis/OakLiteralParsing.h>

#include <OIL/OilTypeRef.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateSpecification.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilStatementBody.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilAllusion.h>
#include <OIL/IOilPrimary.h>
#include <OIL/IOilOperator.h>
#include <OIL/OilExpression.h>
#include <OIL/OilBoolLiteral.h>
#include <OIL/OilNullPointerLiteral.h>
#include <OIL/OilStringLiteral.h>

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
#include <Parsing/Language/OakPointerTypeConstructor.h>
#include <Parsing/Language/OakReferenceTypeConstructor.h>
#include <Parsing/Language/OakFunctionParameterConstructor.h>
#include <Parsing/Language/OakIgnoreStatementConstructor.h>
#include <Parsing/Language/OakBindingStatementConstructor.h>
#include <Parsing/Language/OakBindingAllusionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

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
OilTypeRef * OakTranslateReturnTypeToOil ( const ASTElement * ReturnElement );
OilStatementBody * OakTranslateStatementBodyToOil ( const ASTElement * BodyElement );
OilBindingStatement * OakTranslateLocalBindingStatementToOil ( const ASTElement * StatementElement );

OilExpression * OakTranslateExpressionToOil ( const ASTElement * ExpressionElement );
IOilPrimary * OakTranslatePrimaryExpressionToOil ( const ASTElement * PrimaryElement );
IOilOperator * OakTranslateOperatorToOil ( const ASTElement * OperatorElement );

IOilPrimary * OakTranslateLiteralToOil ( const ASTElement * LiteralElement );

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
			
			case OakASTTags :: kASTTag_FunctionDefinition:
			{
				
				const OakFunctionDefinitionConstructor :: ElementData * FuncData = reinterpret_cast <const OakFunctionDefinitionConstructor :: ElementData *> ( SubElement -> GetData () );
				
				if ( GlobalNS.FindFunctionDefinition ( FuncData -> Name ) != NULL )
				{
					
					WriteError ( SubElement, "Function with the same name already exists in namespace" );
					
					return false;
					
				}
				
				OilFunctionDefinition * FunctionDefinition = OakTranslateFunctionDefinitionToOil ( SubElement );
				
				if ( FunctionDefinition == NULL )
					return false;
				
				GlobalNS.AddFunctionDefinition ( FunctionDefinition );
				
			}
			
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
			
			case OakASTTags :: kASTTag_FunctionDefinition:
			{
				
				const OakFunctionDefinitionConstructor :: ElementData * FuncData = reinterpret_cast <const OakFunctionDefinitionConstructor :: ElementData *> ( SubElement -> GetData () );
				
				if ( DefinedNamespaceDefinition -> FindFunctionDefinition ( FuncData -> Name ) != NULL )
				{
					
					WriteError ( SubElement, "Function with the same name already exists in namespace" );
					
					return false;
					
				}
				
				OilFunctionDefinition * FunctionDefinition = OakTranslateFunctionDefinitionToOil ( SubElement );
				
				if ( FunctionDefinition == NULL )
					return false;
				
				DefinedNamespaceDefinition -> AddFunctionDefinition ( FunctionDefinition );
				
			}
			
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
		
		case OakASTTags :: kASTTag_PointerType:
		{
			
			const OakPointerTypeConstructor :: ElementData * PointerData = reinterpret_cast <const OakPointerTypeConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			OilTypeRef * SubTypeRef = OakTranslateTypeRefToOil ( TypeElement -> GetSubElement ( 0 ) );
			
			if ( SubTypeRef == NULL )
				return NULL;
			
			return new OilTypeRef ( OilTypeRef :: kPointer, SubTypeRef );
			
		}
		
		case OakASTTags :: kASTTag_ReferenceType:
		{
			
			const OakReferenceTypeConstructor :: ElementData * ReferenceData = reinterpret_cast <const OakReferenceTypeConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			OilTypeRef * SubTypeRef = OakTranslateTypeRefToOil ( TypeElement -> GetSubElement ( 0 ) );
			
			if ( SubTypeRef == NULL )
				return NULL;
			
			return new OilTypeRef ( OilTypeRef :: kReference, SubTypeRef );
			
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
	
	if ( FunctionDefData -> Templated )
	{
		
		OilTemplateDefinition * TemplateDefinition = OakTranslateTemplateDefinitionToOil ( FunctionDefElement -> GetSubElement ( 0 ) );
		
		if ( TemplateDefinition == NULL )
			return NULL;
		
		OilFunctionParameterList * FunctionParamList = OakTranslateFunctionParameterListToOil ( FunctionDefElement -> GetSubElement ( 1 ) );
		
		if ( FunctionParamList == NULL )
		{
			
			delete TemplateDefinition;
			
			return NULL;
			
		}
		
		if ( FunctionDefData -> ReturnTyped )
		{
			
			OilTypeRef * ReturnType = OakTranslateReturnTypeToOil ( FunctionDefElement -> GetSubElement ( 2 ) );
			
			if ( ReturnType == NULL )
			{
				
				delete TemplateDefinition;
				delete FunctionParamList;
				
				return NULL;
				
			}
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( FunctionDefElement -> GetSubElement ( 3 ) );
			
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
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( FunctionDefElement -> GetSubElement ( 2 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete TemplateDefinition;
				delete FunctionParamList;
				
				return NULL;
				
			}
			
			return new OilFunctionDefinition ( FunctionDefData -> Name, FunctionDefData -> Public, FunctionDefData -> Inline, FunctionParamList, StatementBody, NULL, TemplateDefinition );
			
		}
		
	}
	else
	{
		
		OilFunctionParameterList * FunctionParamList = OakTranslateFunctionParameterListToOil ( FunctionDefElement -> GetSubElement ( 0 ) );
		
		if ( FunctionParamList == NULL )
			return NULL;
		
		if ( FunctionDefData -> ReturnTyped )
		{
			
			OilTypeRef * ReturnType = OakTranslateReturnTypeToOil ( FunctionDefElement -> GetSubElement ( 1 ) );
			
			if ( ReturnType == NULL )
			{
				
				delete FunctionParamList;
				
				return NULL;
				
			}
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( FunctionDefElement -> GetSubElement ( 2 ) );
			
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
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( FunctionDefElement -> GetSubElement ( 1 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete FunctionParamList;
				
				return NULL;
				
			}
			
			return new OilFunctionDefinition ( FunctionDefData -> Name, FunctionDefData -> Public, FunctionDefData -> Inline, FunctionParamList, StatementBody, NULL );
			
		}
		
	}
	
}

OilFunctionParameterList * OakTranslateFunctionParameterListToOil ( const ASTElement * ParameterListElement )
{
	
	if ( ( ParameterListElement == NULL ) || ( ParameterListElement -> GetTag () != OakASTTags :: kASTTag_FunctionParameterList ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	OilFunctionParameterList * ParamList = new OilFunctionParameterList ();
	
	uint64_t ParamCount = ParameterListElement -> GetSubElementCount ();
	
	for ( uint64_t I = 0; I < ParamCount; I ++ )
	{
		
		const ASTElement * ParameterElement = ParameterListElement -> GetSubElement ( I );
		
		if ( ( ParameterElement == NULL ) || ( ParameterElement -> GetTag () != OakASTTags :: kASTTag_FunctionParameter ) )
		{
			
			delete ParamList;
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		const OakFunctionParameterConstructor :: ElementData * ParameterData = reinterpret_cast <const OakFunctionParameterConstructor :: ElementData *> ( ParameterElement -> GetData () );
		
		OilTypeRef * Type = OakTranslateTypeRefToOil ( ParameterElement -> GetSubElement ( 0 ) );
		
		if ( Type == NULL )
		{
			
			delete ParamList;
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		if ( ParamList -> FindFunctionParameter ( ParameterData -> Name ) != NULL )
		{
			
			WriteError ( ParameterElement, std :: string ( "Duplicate function parameter name \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( ParameterData -> Name ) + "\"" );
			
			delete ParamList;
			
			return NULL;
			
		}
		
		ParamList -> AddParameter ( new OilFunctionParameter ( ParameterData -> Name, Type ) );
		
	}
	
	return ParamList;
	
}

OilTypeRef * OakTranslateReturnTypeToOil ( const ASTElement * ReturnElement )
{
	
	if ( ( ReturnElement == NULL ) || ( ReturnElement -> GetTag () != OakASTTags :: kASTTag_ReturnType ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const ASTElement * TypeElement = ReturnElement -> GetSubElement ( 0 );
	
	return OakTranslateTypeRefToOil ( TypeElement );
	
}

OilStatementBody * OakTranslateStatementBodyToOil ( const ASTElement * BodyElement )
{
	
	if ( ( BodyElement == NULL ) || ( BodyElement -> GetTag () != OakASTTags :: kASTTag_StatementBlock ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	OilStatementBody * Body = new OilStatementBody ();
	
	uint64_t SubElementCount = BodyElement -> GetSubElementCount ();
	
	for ( uint64_t I = 0; I < SubElementCount; I ++ )
	{
		
		const ASTElement * StatementElement = BodyElement -> GetSubElement ( I );
		
		if ( StatementElement == NULL )
		{
			
			delete Body;
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		switch ( StatementElement -> GetTag () )
		{
			
			case OakASTTags :: kASTTag_IgnoreStatement:
			{
				
				const OakIgnoreStatementConstructor :: ElementData * IgnoreData = reinterpret_cast <const OakIgnoreStatementConstructor :: ElementData *> ( StatementElement -> GetData () );
				
				Body -> AddIgnoredParameter ( IgnoreData -> IgnoredName );
				
			}
			break;
			
			case OakASTTags :: kASTTag_StatementBlock:
			{
				
				OilStatementBody * SubBody = OakTranslateStatementBodyToOil ( StatementElement );
				
				if ( SubBody == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				Body -> TakeIgnoredParams ( * SubBody );
				Body -> AddStatement ( SubBody ); 
				
			}
			
			case OakASTTags :: kASTTag_BindingStatement:
			{
				
				OilBindingStatement * Binding = OakTranslateLocalBindingStatementToOil ( StatementElement );
				
				if ( Binding == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				// Add local
				
			}
			
			default:
				break;
			
		}
		
	}
	
	return Body;
	
}

OilBindingStatement * OakTranslateLocalBindingStatementToOil ( const ASTElement * StatementElement )
{
	
	if ( ( StatementElement == NULL ) || ( StatementElement -> GetTag () != OakASTTags :: kASTTag_BindingStatement ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const OakBindingStatementConstructor :: ElementData * BindingData = reinterpret_cast <const OakBindingStatementConstructor :: ElementData *> ( StatementElement -> GetData () );
	
	if ( BindingData -> Public )
	{
		
		WriteError ( StatementElement, std :: string ( "Local binding \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( BindingData -> Name ) + "\" cannot be made public since it is a scoped local binding" );
		
		return NULL;
		
	}
	
	OilTypeRef * Type = OakTranslateTypeRefToOil ( StatementElement -> GetSubElement ( 0 ) );
	
	if ( Type == NULL )
		return NULL;
	
	if ( BindingData -> Initialized )
	{
		
		// TODO: Handle initilizer values in locals...
		// ATTN: THIS JUST DROPS THEM
		return new OilBindingStatement ( BindingData -> Name, BindingData -> Mutable, Type );
		
	}
	else
		return new OilBindingStatement ( BindingData -> Name, BindingData -> Mutable, Type );
	
}

OilExpression * OakTranslateExpressionToOil ( const ASTElement * ExpressionElement )
{
	
	if ( ( ExpressionElement == NULL ) || ( ExpressionElement -> GetTag () != OakASTTags :: kASTTag_Expression ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const ASTElement * SubExpressionElement = ExpressionElement -> GetSubElement ( 0 );
	
	if ( SubExpressionElement -> GetTag () == OakASTTags :: kASTTag_PrimaryExpression )
	{
		
		//IOilPrimary * Primary = OakTranslatePrimaryExpressionToOil ( SubExpressionElement );
		
		
		
	}
	else if ( SubExpressionElement -> GetTag () == OakASTTags :: kASTTag_OperatorExpressionContainer )
	{
		
		//IOilOperator * Operator = OakTranslateOperatorToOil ( SubExpressionElement );
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
	
	return NULL;
	
}

IOilPrimary * OakTranslatePrimaryExpressionToOil ( const ASTElement * PrimaryElement )
{
	
	const ASTElement * SubElement = PrimaryElement -> GetSubElement ( 0 );
	
	if ( SubElement == NULL )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	switch ( SubElement -> GetTag () )
	{
		
		case OakASTTags :: kASTTag_ParenthesizedExpression:
			return OakTranslateExpressionToOil ( PrimaryElement -> GetSubElement ( 0 ) );
		
		case OakASTTags :: kASTTag_LiteralExpression:
			return OakTranslateLiteralToOil ( PrimaryElement );
		
		case OakASTTags :: kASTTag_ArrayLiteral:
		{
			
			// TODO: Implement
			
		}
		break;
		
		case OakASTTags :: kASTTag_SelfAllusion:
			return new OilAllusion ( OilAllusion :: SELF_ALLUSION );
		
		case OakASTTags :: kASTTag_BindingAllusion:
		{
			
			const OakBindingAllusionConstructor :: ElementData * AllusionData = reinterpret_cast <const OakBindingAllusionConstructor :: ElementData *> ( PrimaryElement -> GetData () );
			
			if ( AllusionData -> IdentListLength > 1 )
			{
				
				if ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 1 ].Templated )
				{
					
					if ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 2 ].Templated )
					{
						
						std :: vector <std :: u32string> NSNames;
						
						for ( uint32_t I = 0; I < AllusionData -> IdentListLength - 2; I ++ )
						{
							
							if ( AllusionData -> IdentList [ I ].Templated )
							{
								
								WriteError ( PrimaryElement, "Namespaces cannot have template specifications" );
								
								return NULL;
								
							}
							
							NSNames.push_back ( AllusionData -> IdentList [ I ].Name );
							
						}
						
						NSNames.push_back ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 2 ].Name );
						
						OilTemplateSpecification * DirectTemplateSpec = OakTranslateTemplateSpecificationToOil ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 1 ].TemplateSpecificationElement );
						
						if ( DirectTemplateSpec == NULL )
							return NULL;
						
						OilTemplateSpecification * IndirectTemplateSpec = OakTranslateTemplateSpecificationToOil ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 2 ].TemplateSpecificationElement );
						
						if ( DirectTemplateSpec == NULL )
						{
							
							delete IndirectTemplateSpec;
							
							return NULL;
							
						}
						
						return new OilAllusion ( & NSNames [ 0 ], NSNames.size (), AllusionData -> DirectGlobalReference, AllusionData -> IdentList [ AllusionData -> IdentListLength - 1 ].Name, DirectTemplateSpec, IndirectTemplateSpec );
						
					}
					else
					{
						
						std :: vector <std :: u32string> NSNames;
						
						for ( uint32_t I = 0; I < AllusionData -> IdentListLength - 1; I ++ )
						{
							
							if ( AllusionData -> IdentList [ I ].Templated )
							{
								
								WriteError ( PrimaryElement, "Namespaces cannot have template specifications" );
								
								return NULL;
								
							}
							
							NSNames.push_back ( AllusionData -> IdentList [ I ].Name );
							
						}
						
						OilTemplateSpecification * DirectTemplateSpec = OakTranslateTemplateSpecificationToOil ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 1 ].TemplateSpecificationElement );
						
						if ( DirectTemplateSpec == NULL )
							return NULL;
						
						return new OilAllusion ( & NSNames [ 0 ], NSNames.size (), AllusionData -> DirectGlobalReference, AllusionData -> IdentList [ AllusionData -> IdentListLength - 1 ].Name, DirectTemplateSpec );
						
					}
					
				}
				else if ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 2 ].Templated )
				{
					
					std :: vector <std :: u32string> NSNames;
					
					for ( uint32_t I = 0; I < AllusionData -> IdentListLength - 2; I ++ )
					{
						
						if ( AllusionData -> IdentList [ I ].Templated )
						{
								
							WriteError ( PrimaryElement, "Namespaces cannot have template specifications" );
							
							return NULL;
							
						}
						
						NSNames.push_back ( AllusionData -> IdentList [ I ].Name );
						
					}
					
					NSNames.push_back ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 2 ].Name );
					
					OilTemplateSpecification * IndirectTemplateSpec = OakTranslateTemplateSpecificationToOil ( AllusionData -> IdentList [ AllusionData -> IdentListLength - 2 ].TemplateSpecificationElement );
					
					if ( IndirectTemplateSpec == NULL )
						return NULL;
					
					return new OilAllusion ( & NSNames [ 0 ], NSNames.size (), AllusionData -> DirectGlobalReference, AllusionData -> IdentList [ AllusionData -> IdentListLength - 1 ].Name, NULL, IndirectTemplateSpec );
					
				}
				else
				{
					
					std :: vector <std :: u32string> NSNames;
					
					for ( uint32_t I = 0; I < AllusionData -> IdentListLength - 1; I ++ )
					{
						
						if ( AllusionData -> IdentList [ I ].Templated )
						{
								
							WriteError ( PrimaryElement, "Namespaces cannot have template specifications" );
							
							return NULL;
							
						}
						
						NSNames.push_back ( AllusionData -> IdentList [ I ].Name );
						
					}
					
					return new OilAllusion ( & NSNames [ 0 ], NSNames.size (), AllusionData -> DirectGlobalReference, AllusionData -> IdentList [ AllusionData -> IdentListLength - 1 ].Name );
					
				}
				
			}
			else
			{
				
				if ( AllusionData -> IdentList [ 0 ].Templated )
				{
					
					OilTemplateSpecification * DirectTemplateSpec = OakTranslateTemplateSpecificationToOil ( AllusionData -> IdentList [ 0 ].TemplateSpecificationElement );
					
					if ( DirectTemplateSpec == NULL )
						return NULL;
					
					return new OilAllusion ( AllusionData -> IdentList [ 0 ].Name, DirectTemplateSpec );
					
				}
				else
					return new OilAllusion ( AllusionData -> IdentList [ 0 ].Name );
				
			}
			
		}
		break;
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
	
	return NULL;
	
}

IOilPrimary * OakTranslateLiteralToOil ( const ASTElement * LiteralElement )
{
	
	if ( ( LiteralElement == NULL ) || ( LiteralElement -> GetTag () != OakASTTags :: kASTTag_LiteralExpression ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const Token * LiteralToken = LiteralElement -> GetToken ( 0, 0 );
	
	switch ( LiteralToken -> GetTag () )
	{
		
		case OakTokenTags :: kTokenTag_Identifier:
		{
			
			switch ( LiteralToken -> GetAuxTag () )
			{
				
				case OakKeywordTokenTags :: kKeywordAuxTags_True:
					return new OilBoolLiteral ( true );
				
				case OakKeywordTokenTags :: kKeywordAuxTags_False:
					return new OilBoolLiteral ( false );
				
				case OakKeywordTokenTags :: kKeywordAuxTags_Null:
					return new OilNullPointerLiteral ();
					
				default:
				{
					
					LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
					
					return NULL;
					
				}
				
			}
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_StringLiteralDefault:
		{
			
			std :: string ErrorString;
			std :: u32string ValueString;
			
			if ( ! OakParseStringLiteral ( LiteralToken -> GetSource (), ValueString, ErrorString ) )
			{
				
				if ( ErrorString != "" )
					WriteError ( LiteralElement, ErrorString );
				else
					WriteError ( LiteralElement, "Invalid string literal" );
				
				return NULL;
				
			}
			
			return new OilStringLiteral ( OilStringLiteral :: kEncodingType_Indeterminate, ValueString );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_StringLiteralu8:
		{
			
			std :: string ErrorString;
			std :: u32string ValueString;
			
			if ( ! OakParseStringLiteral ( LiteralToken -> GetSource (), ValueString, ErrorString ) )
			{
				
				if ( ErrorString != "" )
					WriteError ( LiteralElement, ErrorString );
				else
					WriteError ( LiteralElement, "Invalid string literal" );
				
				return NULL;
				
			}
			
			return new OilStringLiteral ( OilStringLiteral :: kEncodingType_UTF8, ValueString );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_StringLiteralu16:
		{
			
			std :: string ErrorString;
			std :: u32string ValueString;
			
			if ( ! OakParseStringLiteral ( LiteralToken -> GetSource (), ValueString, ErrorString ) )
			{
				
				if ( ErrorString != "" )
					WriteError ( LiteralElement, ErrorString );
				else
					WriteError ( LiteralElement, "Invalid string literal" );
				
				return NULL;
				
			}
			
			return new OilStringLiteral ( OilStringLiteral :: kEncodingType_UTF16, ValueString );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_StringLiteralu32:
		{
			
			std :: string ErrorString;
			std :: u32string ValueString;
			
			if ( ! OakParseStringLiteral ( LiteralToken -> GetSource (), ValueString, ErrorString ) )
			{
				
				if ( ErrorString != "" )
					WriteError ( LiteralElement, ErrorString );
				else
					WriteError ( LiteralElement, "Invalid string literal" );
				
				return NULL;
				
			}
			
			return new OilStringLiteral ( OilStringLiteral :: kEncodingType_UTF32, ValueString );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_CharLiteral:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_FloatLiteralDefaultSize:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_FloatLiteral32:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_FloatLiteral64:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteralDefault:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral8:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral16:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral32:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral64:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteralDefault:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral8:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral16:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral32:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral64:
		{
			
			// TODO: Finish
			
			return NULL;
			
		}
		break;
		
	}
	
}

IOilOperator * OakTranslateOperatorToOil ( const ASTElement * OperatorElement )
{
	
	// TODO: Implement
	
	return NULL;
	
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
