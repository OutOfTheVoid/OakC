#include <EarlyAnalysis/OakOilTranslation.h>
#include <EarlyAnalysis/OakLiteralParsing.h>
#include <EarlyAnalysis/OakDecorators.h>

#include <Math/BigFloat.h>
#include <Math/BigInteger.h>

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
#include <OIL/OilIntegerLiteral.h>
#include <OIL/OilCharLiteral.h>
#include <OIL/OilFloatLiteral.h>
#include <OIL/OilUnaryOperator.h>
#include <OIL/OilBinaryOperator.h>
#include <OIL/OilArrayLiteral.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraitFunction.h>
#include <OIL/OilTraitMethod.h>
#include <OIL/OilReturn.h>
#include <OIL/OilIfElse.h>
#include <OIL/OilWhileLoop.h>
#include <OIL/OilDoWhileLoop.h>
#include <OIL/OilBreak.h>
#include <OIL/OilLoop.h>
#include <OIL/OilMethodDefinition.h>
#include <OIL/OilMethodParameterList.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilDecoratorTag.h>
#include <OIL/OilConstStatement.h>

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
#include <Parsing/Language/OakReferenceTypeConstructor.h>
#include <Parsing/Language/OakFunctionParameterConstructor.h>
#include <Parsing/Language/OakIgnoreStatementConstructor.h>
#include <Parsing/Language/OakBindingStatementConstructor.h>
#include <Parsing/Language/OakConstStatementConstructor.h>
#include <Parsing/Language/OakBindingAllusionConstructor.h>
#include <Parsing/Language/OakArrayLiteralConstructor.h>
#include <Parsing/Language/OakTraitDefinitionConstructor.h>
#include <Parsing/Language/OakTraitFunctionConstructor.h>
#include <Parsing/Language/OakTraitMethodConstructor.h>
#include <Parsing/Language/OakIfElseStatementConstructor.h>
#include <Parsing/Language/OakWhileStatementConstructor.h>
#include <Parsing/Language/OakLoopLabelConstructor.h>
#include <Parsing/Language/OakBreakStatementConstructor.h>
#include <Parsing/Language/OakLoopStatementConstructor.h>
#include <Parsing/Language/OakImplementDefinitionConstructor.h>
#include <Parsing/Language/OakMethodDefinitionConstructor.h>
#include <Parsing/Language/OakDecoratorTagConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

#include <Compilation/CompilationUnit.h>

void WriteError ( const ASTElement * SourceRef, std :: string Error );

bool OakTranslateNamespaceTreeToOil ( const ASTElement * NamespaceElement, OilNamespaceDefinition & Container );
bool OakTranslateStructTreeToOil ( const ASTElement * StructElement, OilNamespaceDefinition & Container );
OilTemplateDefinition * OakTranslateTemplateDefinitionToOil ( const ASTElement * TemplateDefinitionElement );
OilTemplateDefinition * OakTranslateWhereClauseToOil ( const ASTElement * WhereDefinitionElement );
OilTemplateSpecification * OakTranslateTemplateSpecificationToOil ( const ASTElement * TemplateSpecificationElement );
OilTypeRef * OakTranslateTraitRefToOil ( const ASTElement * TypeElement );
OilTypeRef * OakTranslateTypeRefToOil ( const ASTElement * TypeElement );
OilStructBinding * OakTranslateStructBindingToOil ( const ASTElement * BindingElement );
OilFunctionDefinition * OakTranslateFunctionDefinitionToOil ( const ASTElement * FunctionDefElement );
OilFunctionParameterList * OakTranslateFunctionParameterListToOil ( const ASTElement * ParameterListElement );
OilTypeRef * OakTranslateReturnTypeToOil ( const ASTElement * ReturnElement );
OilStatementBody * OakTranslateStatementBodyToOil ( const ASTElement * BodyElement );
OilBindingStatement * OakTranslateBindingStatementToOil ( const ASTElement * StatementElement );
OilArrayLiteral * OakTranslateArrayLiteral ( const ASTElement * ArrayElement );
IOilPrimary * OakTranslateLiteralToOil ( const ASTElement * LiteralElement );
OilTraitDefinition * OakTranslateTraitToOil ( const ASTElement * TraitElement, OilDecoratorTag ** Decorators, uint32_t DecoratorCount );
OilTraitFunction * OakTranslateTraitFunctionToOil ( const ASTElement * FunctionElement );
OilTraitMethod * OakTranslateTraitMethodToOil ( const ASTElement * MethodElement );
OilMethodParameterList * OakTranslateMethodParameterListToOil ( const ASTElement * ParameterListElement );
OilMethodDefinition * OakTranslateMethodDefinitionToOil ( const ASTElement * MethodDefElement );
OilImplementBlock * OakTranslateImplementBlockToOil ( const ASTElement * ImplementElement );
OilExpression * OakTranslateExpressionToOil ( const ASTElement * ExpressionElement );
IOilPrimary * OakTranslatePrimaryExpressionToOil ( const ASTElement * PrimaryElement );
IOilOperator * OakTranslateOperatorToOil ( const ASTElement * OperatorElement );
OilDecoratorTag * OakTranslateDecoratorTagToOil ( const ASTElement * DecoratorTagElement );
OilConstStatement * OakTranslateConstStatementToOil ( const ASTElement * ConstElement );

bool OakTranslateFileTreeToOil ( const ASTElement * TreeRoot, OilNamespaceDefinition & GlobalNS )
{
	
	if ( ( TreeRoot == NULL ) || ( TreeRoot -> GetTag () != OakASTTags :: kASTTag_File ) )
	{
		
		LOG_FATALERROR ( "Invalid AST passed to OIL parser with NULL element" );
		
		return false;
		
	}
	
	uint64_t SubElementCount = TreeRoot -> GetSubElementCount ();
	
	std :: vector <OilDecoratorTag *> Decorators;
	
	const ASTElement * SubElement = NULL;
	
	OilNamespaceDefinition :: NameSearchResult SearchResult;
	
	for ( uint64_t I = 0; I < SubElementCount; I ++ )
	{
		
		SubElement = TreeRoot -> GetSubElement ( I );
		
		switch ( SubElement -> GetTag () )
		{
			
			case OakASTTags :: kASTTag_ImportStatement:
			break;
			
			case OakASTTags :: kASTTag_DecoratorTag:
			{
				
				OilDecoratorTag * Decorator = OakTranslateDecoratorTagToOil ( SubElement );
				
				if ( Decorator == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				Decorators.push_back ( Decorator );
				
			}
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
				
				GlobalNS.SearchName ( FuncData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Function name conflicts with previously defined namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilFunctionDefinition * FunctionDefinition = OakTranslateFunctionDefinitionToOil ( SubElement );
				
				if ( FunctionDefinition == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				GlobalNS.AddFunctionDefinition ( FunctionDefinition );
				
			}
			break;
			
			case OakASTTags :: kASTTag_BindingStatement:
			{
				
				const OakBindingStatementConstructor :: ElementData * BindingData = reinterpret_cast <const OakBindingStatementConstructor :: ElementData *> ( SubElement -> GetData () );
				
				GlobalNS.SearchName ( BindingData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Binding name conflicts with previously defined namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilBindingStatement * BindingStatement = OakTranslateBindingStatementToOil ( SubElement );
				
				if ( BindingStatement == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				GlobalNS.AddBindingStatement ( BindingStatement );
				
			}
			break;
			
			case OakASTTags :: kASTTag_ConstStatement:
			{
				
				const OakConstStatementConstructor :: ElementData * ConstData = reinterpret_cast <const OakConstStatementConstructor :: ElementData *> ( SubElement -> GetData () );
				
				GlobalNS.SearchName ( ConstData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Constant name conflicts with previously defined namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilConstStatement * ConstStatement = OakTranslateConstStatementToOil ( SubElement );
				
				if ( ConstStatement == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				GlobalNS.AddConstStatement ( ConstStatement );
				
			}
			break;
			
			case OakASTTags :: kASTTag_TraitDefinition:
			{
				
				const OakTraitDefinitionConstructor :: ElementData * TraitData = reinterpret_cast <const OakTraitDefinitionConstructor :: ElementData *> ( SubElement -> GetData () );
				
				GlobalNS.SearchName ( TraitData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Trait name conflicts with previous namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilTraitDefinition * TraitDefinition = OakTranslateTraitToOil ( SubElement, & Decorators [ 0 ], Decorators.size () );
				Decorators.clear ();
				
				if ( TraitDefinition == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				GlobalNS.AddTraitDefinition ( TraitDefinition );
				
			}
			break;
			
			case OakASTTags :: kASTTag_ImplementDefinition:
			{
				
				OilImplementBlock * Block = OakTranslateImplementBlockToOil ( SubElement );
				
				if ( Block == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				GlobalNS.AddUnresolvedImplementBlock ( Block );
				
			}
			break;
			
			default:
			break;
			
		}
		
	}
	
	if ( Decorators.size () != 0 )
	{
		
		WriteError ( SubElement, "Unassociated decorator at end of file" );
		
		while ( Decorators.size () != 0 )
		{
			
			delete Decorators [ Decorators.size () - 1 ];
			
			Decorators.pop_back ();
			
		}
		
		return false;
		
	}
	
	return true;
	
}

bool OakTranslateNamespaceTreeToOil ( const ASTElement * NamespaceElement, OilNamespaceDefinition & Container )
{
	
	if ( ( NamespaceElement == NULL ) || ( NamespaceElement -> GetTag () != OakASTTags :: kASTTag_NamespaceDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return false;
		
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
	
	std :: vector <OilDecoratorTag *> Decorators;
	
	uint64_t SumElementCount = NamespaceElement -> GetSubElementCount ();
	
	const ASTElement * SubElement = NULL;
	
	OilNamespaceDefinition :: NameSearchResult SearchResult;
	
	for ( uint64_t I = 0; I < SumElementCount; I ++ )
	{
		
		SubElement = NamespaceElement -> GetSubElement ( I );
		
		switch ( SubElement -> GetTag () )
		{
			
			case OakASTTags :: kASTTag_DecoratorTag:
			{
				
				OilDecoratorTag * Decorator = OakTranslateDecoratorTagToOil ( SubElement );
				
				if ( Decorator == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				Decorators.push_back ( Decorator );
				
			}
			break;
			
			case OakASTTags :: kASTTag_StructDefinition:
			{
				
				if ( ! OakTranslateStructTreeToOil ( SubElement, * DefinedNamespaceDefinition ) )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
			}
			break;
			
			case OakASTTags :: kASTTag_NamespaceDefinition:
			{
				
				if ( ! OakTranslateNamespaceTreeToOil ( SubElement, * DefinedNamespaceDefinition ) )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
			}
			break;
			
			case OakASTTags :: kASTTag_FunctionDefinition:
			{
				
				const OakFunctionDefinitionConstructor :: ElementData * FuncData = reinterpret_cast <const OakFunctionDefinitionConstructor :: ElementData *> ( SubElement -> GetData () );
				
				DefinedNamespaceDefinition -> SearchName ( FuncData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Function name conflicts with previously defined namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilFunctionDefinition * FunctionDefinition = OakTranslateFunctionDefinitionToOil ( SubElement );
				
				if ( FunctionDefinition == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				DefinedNamespaceDefinition -> AddFunctionDefinition ( FunctionDefinition );
				
			}
			break;
			
			case OakASTTags :: kASTTag_BindingStatement:
			{
				
				const OakBindingStatementConstructor :: ElementData * BindingData = reinterpret_cast <const OakBindingStatementConstructor :: ElementData *> ( SubElement -> GetData () );
				
				DefinedNamespaceDefinition -> SearchName ( BindingData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Binding name conflicts with previously defined namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilBindingStatement * BindingStatement = OakTranslateBindingStatementToOil ( SubElement );
				
				if ( BindingStatement == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				DefinedNamespaceDefinition -> AddBindingStatement ( BindingStatement );
				
			}
			break;
			
			case OakASTTags :: kASTTag_ConstStatement:
			{
				
				const OakConstStatementConstructor :: ElementData * ConstData = reinterpret_cast <const OakConstStatementConstructor :: ElementData *> ( SubElement -> GetData () );
				
				DefinedNamespaceDefinition -> SearchName ( ConstData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Constant name conflicts with previously defined namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilConstStatement * ConstStatement = OakTranslateConstStatementToOil ( SubElement );
				
				if ( ConstStatement == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				DefinedNamespaceDefinition -> AddConstStatement ( ConstStatement );
				
			}
			break;
			
			case OakASTTags :: kASTTag_TraitDefinition:
			{
				
				const OakTraitDefinitionConstructor :: ElementData * TraitData = reinterpret_cast <const OakTraitDefinitionConstructor :: ElementData *> ( SubElement -> GetData () );
				
				DefinedNamespaceDefinition -> SearchName ( TraitData -> Name, SearchResult );
				
				if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
				{
					
					WriteError ( SubElement, "Trait name conflicts with previously defined namespace member" );
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				OilTraitDefinition * TraitDefinition = OakTranslateTraitToOil ( SubElement, & Decorators [ 0 ], Decorators.size () );
				Decorators.clear ();
				
				if ( TraitDefinition == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				DefinedNamespaceDefinition -> AddTraitDefinition ( TraitDefinition );
				
			}
			break;
			
			case OakASTTags :: kASTTag_ImplementDefinition:
			{
				
				OilImplementBlock * Block = OakTranslateImplementBlockToOil ( SubElement );
				
				if ( Block == NULL )
				{
					
					while ( Decorators.size () != 0 )
					{
						
						delete Decorators [ Decorators.size () - 1 ];
						
						Decorators.pop_back ();
						
					}
					
					return false;
					
				}
				
				DefinedNamespaceDefinition -> AddUnresolvedImplementBlock ( Block );
				
			}
			break;
			
		}
		
	}
	
	if ( Decorators.size () != 0 )
	{
		
		WriteError ( SubElement, "Unassociated decorator at end of namespace" );
		
		while ( Decorators.size () != 0 )
		{
			
			delete Decorators [ Decorators.size () - 1 ];
			
			Decorators.pop_back ();
			
		}
		
		return false;
		
	}
	
	return true;
	
}

bool OakTranslateStructTreeToOil ( const ASTElement * StructElement, OilNamespaceDefinition & Container )
{
	
	if ( ( StructElement == NULL ) || ( StructElement -> GetTag () != OakASTTags :: kASTTag_StructDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return false;
		
	}
	
	const OakStructDefinitionConstructor :: ElementData * StructData = reinterpret_cast <const OakStructDefinitionConstructor :: ElementData *> ( StructElement -> GetData () );
	
	OilNamespaceDefinition :: NameSearchResult SearchResult;
	
	Container.SearchName ( StructData -> Name, SearchResult );
	
	if ( SearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_None )
	{
		
		WriteError ( StructElement, "Struct definition conflicts with previously defined namespace member" );
		
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
		
		Container.AddTypeDefinition ( new OilTypeDefinition ( StructDef ) );
		
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
		
		Container.AddTypeDefinition ( new OilTypeDefinition ( StructDef ) );
		
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
			
			const OakBareTraitNameConstructor :: ElementData * TraitRefData = reinterpret_cast <const OakBareTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			return new OilTypeRef ( TraitRefData -> Name, OilTypeRef :: kRefFlag_Trait | ( TraitRefData -> Absolute ? OilTypeRef :: kRefFlag_Absolute : 0 ) );
			
		}
		
		case OakASTTags :: kASTTag_TraitName_Templated:
		{
			
			const OakTemplatedTraitNameConstructor :: ElementData * TraitRefData = reinterpret_cast <const OakTemplatedTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TraitElement -> GetSubElement ( 0 ) );
			
			return new OilTypeRef ( TraitRefData -> Name, TemplateSpecification, OilTypeRef :: kRefFlag_Trait );
			
		}
		
		case OakASTTags :: kASTTag_TraitName_Namespaced:
		{
			
			const OakNamespacedTraitNameConstructor :: ElementData * TraitRefData = reinterpret_cast <const OakNamespacedTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			return new OilTypeRef ( TraitRefData -> Name, TraitRefData -> IdentList, TraitRefData -> IdentListLength, OilTypeRef :: kRefFlag_Trait | ( TraitRefData -> DirectGlobalReference ? OilTypeRef :: kRefFlag_Absolute : 0 ) );
			
		}
		
		case OakASTTags :: kASTTag_TraitName_NamespacedTemplated:
		{
			
			const OakNamespacedTemplatedTraitNameConstructor :: ElementData * TraitRefData = reinterpret_cast <const OakNamespacedTemplatedTraitNameConstructor :: ElementData *> ( TraitElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TraitElement -> GetSubElement ( 0 ) );
			
			return new OilTypeRef ( TraitRefData -> Name, TraitRefData -> IdentList, TraitRefData -> IdentListLength, TemplateSpecification, OilTypeRef :: kRefFlag_Trait | ( TraitRefData -> DirectGlobalReference ? OilTypeRef :: kRefFlag_Absolute : 0 ) );
			
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
			
			const OakBareTypeNameConstructor :: ElementData * TypeRefData = reinterpret_cast <const OakBareTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			return new OilTypeRef ( TypeRefData -> TypeName, TypeRefData -> Absolute ? OilTypeRef :: kRefFlag_Absolute : 0 );
			
		}
		
		case OakASTTags :: kASTTag_TypeName_Templated:
		{
			
			const OakTemplatedTypeNameConstructor :: ElementData * TypeRefData = reinterpret_cast <const OakTemplatedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TypeElement -> GetSubElement ( 0 ) );
			
			if ( TemplateSpecification == NULL )
				return NULL;
			
			return new OilTypeRef ( TypeRefData -> TypeName, TemplateSpecification );
			
		}
		
		case OakASTTags :: kASTTag_TypeName_Namespaced:
		{
			
			const OakNamespacedTypeNameConstructor :: ElementData * TypeRefData = reinterpret_cast <const OakNamespacedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			return new OilTypeRef ( TypeRefData -> TypeName, TypeRefData -> IdentList, TypeRefData -> IdentListLength, TypeRefData -> DirectGlobalReference ? OilTypeRef :: kRefFlag_Absolute : 0 );
			
		}
		
		case OakASTTags :: kASTTag_TypeName_NamespacedTemplated:
		{
			
			const OakNamespacedTemplatedTypeNameConstructor :: ElementData * TypeRefData = reinterpret_cast <const OakNamespacedTemplatedTypeNameConstructor :: ElementData *> ( TypeElement -> GetData () );
			
			OilTemplateSpecification * TemplateSpecification = OakTranslateTemplateSpecificationToOil ( TypeElement -> GetSubElement ( 0 ) );
			
			if ( TemplateSpecification == NULL )
				return NULL;
			
			return new OilTypeRef ( TypeRefData -> TypeName, TypeRefData -> IdentList, TypeRefData -> IdentListLength, TemplateSpecification, TypeRefData -> DirectGlobalReference ? OilTypeRef :: kRefFlag_Absolute : 0 );
			
		}
		
		case OakASTTags :: kASTTag_ReferenceType:
		{
			
			OilTypeRef * SubTypeRef = OakTranslateTypeRefToOil ( TypeElement -> GetSubElement ( 0 ) );
			
			if ( SubTypeRef == NULL )
				return NULL;
			
			return new OilTypeRef ( OilTypeRef :: kReference, SubTypeRef );
			
		}
		
		case OakASTTags :: kASTTag_VoidType:
			return new OilTypeRef ( OilTypeRef :: kVoid );
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
	
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

OilImplementBlock * OakTranslateImplementBlockToOil ( const ASTElement * ImplementElement )
{
	
	if ( ( ImplementElement == NULL ) || ( ImplementElement -> GetTag () != OakASTTags :: kASTTag_ImplementDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const OakImplementDefinitionConstructor :: ElementData * ImplementData = reinterpret_cast <const OakImplementDefinitionConstructor :: ElementData *> ( ImplementElement -> GetData () );
	
	OilTypeRef * ImplementedType = OakTranslateTypeRefToOil ( ImplementElement -> GetSubElement ( 0 ) );
	
	OilImplementBlock * Block = NULL;
		
	if ( ImplementedType == NULL )
		return NULL;
	
	uint32_t ElementOffset = 1;
	
	if ( ImplementData -> ImplementsTrait )
	{
		
		OilTypeRef * ForTrait = OakTranslateTraitRefToOil ( ImplementElement -> GetSubElement ( ElementOffset ) );
		
		ElementOffset ++;
		
		if ( ForTrait == NULL )
		{
			
			delete ImplementedType;
			
			return NULL;
			
		}
		
		if ( ImplementData -> HasWhereClause )
		{
			
			OilTemplateDefinition * WhereDefinition = OakTranslateWhereClauseToOil ( ImplementElement -> GetSubElement ( ElementOffset ) );
			
			ElementOffset ++;
			
			if ( WhereDefinition == NULL )
			{
				
				delete ImplementedType;
				delete ForTrait;
				
				return NULL;
				
			}
			
			if ( ! ( ImplementedType -> IsTemplated () || ForTrait -> IsTemplated () ) )
			{
				
				WriteError ( ImplementElement, "Implement block of non-generic type for non-generic trait cannot contain a where clause." );
				
				delete ImplementedType;
				delete ForTrait;
				
				return NULL;
				
			}
			
			OilTemplateSpecification * ImplementedSpecification = ImplementedType -> GetTemplateSpecification ();
			OilTemplateSpecification * ForSpecification = ForTrait -> GetTemplateSpecification ();
			
			for ( uint32_t I = 0; I < WhereDefinition -> GetTemplateParameterCount (); I ++ )
			{
				
				OilTemplateDefinitionParameter * WhereParam = WhereDefinition -> GetTemplateParameter ( I );
				
				bool Found = false;
				
				for ( uint32_t J = 0; J < ImplementedSpecification -> GetTypeRefCount (); J ++ )
				{
					
					OilTypeRef * Ref = ImplementedSpecification -> GetTypeRef ( J );
					
					if ( ( ! Ref -> IsNamespaced () ) && Ref -> IsDirectType () )
					{
						
						if ( Ref -> GetName () == WhereParam -> GetName () )
						{
							
							Found = true;
							
							break;
							
						}
						
					}
					
				}
				
				if ( Found )
					continue;
				
				for ( uint32_t J = 0; J < ForSpecification -> GetTypeRefCount (); J ++ )
				{
					
					OilTypeRef * Ref = ForSpecification -> GetTypeRef ( J );
					
					if ( ( ! Ref -> IsNamespaced () ) && Ref -> IsDirectType () )
					{
						
						if ( Ref -> GetName () == WhereParam -> GetName () )
						{
							
							Found = true;
							
							break;
							
						}
						
					}
					
				}
				
				if ( ! Found )
				{
					
					WriteError ( ImplementElement, "Where clause of implement block cannot contain type parameter not used in trait or implemented type reference" );
					
					delete ImplementedType;
					delete ForTrait;
					
					return NULL;
					
				}
				
			}
			
			Block = new OilImplementBlock ( ImplementedType, ForTrait, WhereDefinition );
			
		}
		else	
			Block = new OilImplementBlock ( ImplementedType, ForTrait );
		
	}
	else
	{
		
		if ( ImplementData -> HasWhereClause )
		{
			
			OilTemplateDefinition * WhereDefinition = OakTranslateWhereClauseToOil ( ImplementElement -> GetSubElement ( ElementOffset ) );
			
			ElementOffset ++;
			
			if ( WhereDefinition == NULL )
			{
				
				delete ImplementedType;
				
				return NULL;
				
			}
			
			if ( ! ImplementedType -> IsTemplated () )
			{
				
				WriteError ( ImplementElement, "Implement block of non-generic type cannot contain a where clause." );
				
				delete ImplementedType;
				
				return NULL;
				
			}
			
			OilTemplateSpecification * ImplementedSpecification = ImplementedType -> GetTemplateSpecification ();
			
			for ( uint32_t I = 0; I < WhereDefinition -> GetTemplateParameterCount (); I ++ )
			{
				
				OilTemplateDefinitionParameter * WhereParam = WhereDefinition -> GetTemplateParameter ( I );
				
				bool Found = false;
				
				for ( uint32_t J = 0; J < ImplementedSpecification -> GetTypeRefCount (); J ++ )
				{
					
					OilTypeRef * Ref = ImplementedSpecification -> GetTypeRef ( J );
					
					if ( ( ! Ref -> IsNamespaced () ) && Ref -> IsDirectType () )
					{
						
						if ( Ref -> GetName () == WhereParam -> GetName () )
						{
							
							Found = true;
							
							break;
							
						}
						
					}
					
				}
				
				if ( ! Found )
				{
					
					WriteError ( ImplementElement, "Where clause of implement block cannot contain type parameter not used in implemented type reference" );
					
					delete ImplementedType;
					
					return NULL;
					
				}
				
			}
			
			Block = new OilImplementBlock ( ImplementedType, WhereDefinition );
			
		}
		else	
			Block = new OilImplementBlock ( ImplementedType );
		
	}
	
	const ASTElement * ChildElement = ImplementElement -> GetSubElement ( ElementOffset );
	ElementOffset ++;
	
	while ( ChildElement != NULL )
	{
		
		if ( ChildElement -> GetTag () == OakASTTags :: kASTTag_FunctionDefinition )
		{
			
			OilFunctionDefinition * Function = OakTranslateFunctionDefinitionToOil ( ChildElement );
			
			if ( Function == NULL )
			{
				
				delete Block;
				
				return NULL;
				
			}
			
			if ( Block -> FindFunction ( Function -> GetName () ) != NULL )
			{
				
				WriteError ( ChildElement, "Duplicate function, function definition of same name already exists in implement block" );
				
				delete Function;
				delete Block;
				
				return NULL;
				
			}
			
			Block -> AddFunction ( Function );
			
		}
		else
		{
			
			OilMethodDefinition * Method = OakTranslateMethodDefinitionToOil ( ChildElement );
			
			if ( Method == NULL )
			{
				
				delete Block;
				
				return NULL;
				
			}
			
			if ( Block -> FindMethod ( Method -> GetName () ) != NULL )
			{
				
				WriteError ( ChildElement, "Duplicate method, method definition of same name already exists in implement block" );
				
				delete Method;
				delete Block;
				
				return NULL;
				
			}
			
			Block -> AddMethod ( Method );
			
		}
		
		ChildElement = ImplementElement -> GetSubElement ( ElementOffset );
		ElementOffset ++;
		
	}
	
	return Block;
	
}

OilTemplateDefinition * OakTranslateWhereClauseToOil ( const ASTElement * WhereDefinitionElement )
{
	
	if ( ( WhereDefinitionElement == NULL ) || ( WhereDefinitionElement -> GetTag () != OakASTTags :: kASTTag_WhereClause ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	OilTemplateDefinition * WhereTemplate = OakTranslateTemplateDefinitionToOil ( WhereDefinitionElement -> GetSubElement ( 0 ) );
	
	// MAYBE: restrict where clauses to only allowing restricted template types? Fully generic implements might be useful, but also hard to implement properly...
	
	return WhereTemplate;
	
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


OilMethodDefinition * OakTranslateMethodDefinitionToOil ( const ASTElement * MethodDefElement )
{
	
	if ( ( MethodDefElement == NULL ) || ( MethodDefElement -> GetTag () != OakASTTags :: kASTTag_MethodDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
		
		return NULL;
		
	}
	
	const OakMethodDefinitionConstructor :: ElementData * MethodDefData = reinterpret_cast <const OakMethodDefinitionConstructor :: ElementData *> ( MethodDefElement -> GetData () );
	
	if ( MethodDefData -> Templated )
	{
		
		OilTemplateDefinition * TemplateDefinition = OakTranslateTemplateDefinitionToOil ( MethodDefElement -> GetSubElement ( 0 ) );
		
		if ( TemplateDefinition == NULL )
			return NULL;
		
		OilMethodParameterList * MethodParamList = OakTranslateMethodParameterListToOil ( MethodDefElement -> GetSubElement ( 1 ) );
		
		if ( MethodParamList == NULL )
		{
			
			delete TemplateDefinition;
			
			return NULL;
			
		}
		
		if ( MethodDefData -> ReturnTyped )
		{
			
			OilTypeRef * ReturnType = OakTranslateReturnTypeToOil ( MethodDefElement -> GetSubElement ( 2 ) );
			
			if ( ReturnType == NULL )
			{
				
				delete TemplateDefinition;
				delete MethodParamList;
				
				return NULL;
				
			}
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( MethodDefElement -> GetSubElement ( 3 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete TemplateDefinition;
				delete MethodParamList;
				delete ReturnType;
				
				return NULL;
				
			}
			
			return new OilMethodDefinition ( MethodDefData -> Name, MethodDefData -> Public, MethodDefData -> Inline, MethodParamList, StatementBody, ReturnType, TemplateDefinition );
			
		}
		else
		{
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( MethodDefElement -> GetSubElement ( 2 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete TemplateDefinition;
				delete MethodParamList;
				
				return NULL;
				
			}
			
			return new OilMethodDefinition ( MethodDefData -> Name, MethodDefData -> Public, MethodDefData -> Inline, MethodParamList, StatementBody, NULL, TemplateDefinition );
			
		}
		
	}
	else
	{
		
		OilMethodParameterList * MethodParamList = OakTranslateMethodParameterListToOil ( MethodDefElement -> GetSubElement ( 0 ) );
		
		if ( MethodParamList == NULL )
			return NULL;
		
		if ( MethodDefData -> ReturnTyped )
		{
			
			OilTypeRef * ReturnType = OakTranslateReturnTypeToOil ( MethodDefElement -> GetSubElement ( 1 ) );
			
			if ( ReturnType == NULL )
			{
				
				delete MethodParamList;
				
				return NULL;
				
			}
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( MethodDefElement -> GetSubElement ( 2 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete MethodParamList;
				delete ReturnType;
				
				return NULL;
				
			}
			
			return new OilMethodDefinition ( MethodDefData -> Name, MethodDefData -> Public, MethodDefData -> Inline, MethodParamList, StatementBody, ReturnType );
			
		}
		else
		{
			
			OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( MethodDefElement -> GetSubElement ( 1 ) );
			
			if ( StatementBody == NULL )
			{
				
				delete MethodParamList;
				
				return NULL;
				
			}
			
			return new OilMethodDefinition ( MethodDefData -> Name, MethodDefData -> Public, MethodDefData -> Inline, MethodParamList, StatementBody, NULL );
			
		}
		
	}
	
}

OilMethodParameterList * OakTranslateMethodParameterListToOil ( const ASTElement * ParameterListElement )
{
	
	if ( ( ParameterListElement == NULL ) || ( ParameterListElement -> GetTag () != OakASTTags :: kASTTag_MethodParameterList ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const ASTElement * ParameterElement = ParameterListElement -> GetSubElement ( 0 );
	
	if ( ParameterElement == NULL )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	bool SelfIsReference = false;
	
	if ( ParameterElement -> GetTag () == OakASTTags :: kASTTag_SelfParameterReference )
		SelfIsReference = true;
	else if ( ParameterElement -> GetTag () != OakASTTags :: kASTTag_SelfParameter )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	uint64_t ParamCount = ParameterListElement -> GetSubElementCount ();
	
	OilMethodParameterList * ParamList = new OilMethodParameterList ( SelfIsReference );
	
	for ( uint64_t I = 1; I < ParamCount; I ++ )
	{
		
		ParameterElement = ParameterListElement -> GetSubElement ( I );
		
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
		
		ParamList -> AddParameter ( new OilFunctionParameter ( ParameterData -> Name, Type, ParameterData -> Mut ) );
		
	}
	
	return ParamList;
	
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
		
		ParamList -> AddParameter ( new OilFunctionParameter ( ParameterData -> Name, Type, ParameterData -> Mut ) );
		
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
					
					LOG_FATALERROR ( "Structurally invalid AST passed to parser" );
					
					delete Body;
					
					return NULL;
					
				}
				
				Body -> TakeIgnoredParams ( * SubBody );
				Body -> AddStatement ( SubBody ); 
				
			}
			break;
			
			case OakASTTags :: kASTTag_ExpressionStatement:
			{
				
				const ASTElement * ExpressionElement = StatementElement -> GetSubElement ( 0 );
				
				if ( ExpressionElement == NULL )
				{
					
					LOG_FATALERROR ( "Structurally invalid AST passed to parser" );
					
					delete Body;
					
					return NULL;
					
				}
				
				OilExpression * Expression = OakTranslateExpressionToOil ( ExpressionElement );
				
				if ( Expression == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				Body -> AddStatement ( Expression );
				
			}
			break;
			
			case OakASTTags :: kASTTag_ReturnStatement:
			{
				
				const ASTElement * ReturnedExpressionElement = StatementElement -> GetSubElement ( 0 );
				
				if ( ReturnedExpressionElement != NULL )
				{
					
					OilExpression * ReturnedExpression = OakTranslateExpressionToOil ( ReturnedExpressionElement );
					
					if ( ReturnedExpression == NULL )
					{
						
						delete Body;
						
						return NULL;
						
					}
					
					Body -> AddStatement ( new OilReturn ( ReturnedExpression ) );
					
				}
				else
					Body -> AddStatement ( new OilReturn () );
				
			}
			break;
			
			case OakASTTags :: kASTTag_BindingStatement:
			{
				
				OilBindingStatement * Binding = OakTranslateBindingStatementToOil ( StatementElement );
				
				if ( Binding == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				if ( Binding -> IsPublic () )
				{
					
					WriteError ( StatementElement, "Local bindings cannot have access modifiers" );
					
					delete Binding;
					delete Body;
					
					return NULL;
					
				}
				
				Body -> AddLocalBinding ( Binding );
				
			}
			break;
			
			case OakASTTags :: kASTTag_ConstStatement:
			{
				
				OilConstStatement * Constant = OakTranslateConstStatementToOil ( StatementElement );
				
				if ( Constant == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				if ( Constant -> IsPublic () )
				{
					
					WriteError ( StatementElement, "Local constants cannot have access modifiers" );
					
					delete Constant;
					delete Body;
					
					return NULL;
					
				}
				
				Body -> AddLocalConst ( Constant );
				
			}
			break;
			
			case OakASTTags :: kASTTag_WhileStatement:
			{
				
				OilExpression * ConditionExpression = OakTranslateExpressionToOil ( StatementElement -> GetSubElement ( 0 ) );
				
				if ( ConditionExpression == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				const ASTElement * Next = StatementElement -> GetSubElement ( 1 );
				
				std :: u32string LoopLabel ( U"" );
				
				if ( Next == NULL )
				{
					
					delete ConditionExpression;
					delete Body;
					
					return NULL;
					
				}
				
				if ( Next -> GetTag () == OakASTTags :: kASTTag_LoopLabel )
				{
					
					const OakLoopLabelConstructor :: ElementData * LabelData = reinterpret_cast <const OakLoopLabelConstructor :: ElementData *> ( Next -> GetData () );
					
					LoopLabel = LabelData -> Label;
					
					Next = StatementElement -> GetSubElement ( 2 );
					
				}
				
				OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( Next );
				
				if ( StatementBody == NULL )
				{
					
					delete ConditionExpression;
					delete Body;
					
					return NULL;
					
				}
				
				Body -> AddStatement ( new OilWhileLoop ( ConditionExpression, StatementBody, LoopLabel ) );
				
			}
			break;
			
			case OakASTTags :: kASTTag_DoWhileStatement:
			{
				
				const ASTElement * Next = StatementElement -> GetSubElement ( 0 );
				
				std :: u32string LoopLabel ( U"" );
				
				if ( Next == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				bool HasLabel = false;
				
				if ( Next -> GetTag () == OakASTTags :: kASTTag_LoopLabel )
				{
					
					const OakLoopLabelConstructor :: ElementData * LabelData = reinterpret_cast <const OakLoopLabelConstructor :: ElementData *> ( Next -> GetData () );
					
					LoopLabel = LabelData -> Label;
					
					Next = StatementElement -> GetSubElement ( 1 );
					
					HasLabel = true;
					
				}
				
				OilStatementBody * StatementBody = OakTranslateStatementBodyToOil ( Next );
				
				if ( StatementBody == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				Next = StatementElement -> GetSubElement ( HasLabel ? 2 : 1 );
				
				OilExpression * ConditionExpression = OakTranslateExpressionToOil ( Next );
				
				if ( ConditionExpression == NULL )
				{
					
					delete StatementBody;
					delete Body;
					
					return NULL;
					
				}
				
				Body -> AddStatement ( new OilDoWhileLoop ( StatementBody, ConditionExpression, LoopLabel ) );
				
			}
			break;
			
			case OakASTTags :: kASTTag_LoopStatement:
			{
				
				const OakLoopStatementConstructor :: ElementData * LoopData = reinterpret_cast <const OakLoopStatementConstructor :: ElementData *> ( StatementElement -> GetData () ); 
				
				std :: u32string LoopLabel;
				OilStatementBody * StatementBody = NULL;
				
				if ( LoopData -> Labeled )
				{
					
					const ASTElement * LoopLabelElement = StatementElement -> GetSubElement ( 0 );
					
					if ( ( LoopLabelElement == NULL ) || ( LoopLabelElement -> GetTag () != OakASTTags :: kASTTag_LoopLabel ) )
					{
						
						LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
						
						delete Body;
						
						return NULL;
						
					}
					
					LoopLabel = reinterpret_cast <const OakLoopLabelConstructor :: ElementData *> ( LoopLabelElement -> GetData () ) -> Label;
					
					StatementBody = OakTranslateStatementBodyToOil ( StatementElement -> GetSubElement ( 1 ) );
					
				}
				else
					StatementBody = OakTranslateStatementBodyToOil ( StatementElement -> GetSubElement ( 0 ) );
				
				if ( StatementBody == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				Body -> AddStatement ( new OilLoop ( StatementBody, LoopLabel ) );
				
			}
			break;
			
			case OakASTTags :: kASTTag_BreakStatement:
			{
				
				const OakBreakStatementConstructor :: ElementData * BreakData = reinterpret_cast <const OakBreakStatementConstructor :: ElementData *> ( StatementElement -> GetData () ); 
				
				if ( BreakData -> Labeled )
				{
					
					const ASTElement * LoopLabelElement = StatementElement -> GetSubElement ( 0 );
					
					if ( ( LoopLabelElement == NULL ) || ( LoopLabelElement -> GetTag () != OakASTTags :: kASTTag_LoopLabel ) )
					{
						
						LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
						
						delete Body;
						
						return NULL;
						
					}
					
					Body -> AddStatement ( new OilBreak ( reinterpret_cast <const OakLoopLabelConstructor :: ElementData *> ( LoopLabelElement -> GetData () ) -> Label ) );
					
				}
				else
					Body -> AddStatement ( new OilBreak () );
				
			}
			break;
			
			case OakASTTags :: kASTTag_IfElseStatement:
			{
				
				const OakIfElseStatementConstructor :: ElementData * IfElseData = reinterpret_cast <const OakIfElseStatementConstructor :: ElementData *> ( StatementElement -> GetData () );
				
				uint32_t ElementOffset = 0;
				
				OilExpression * IfCondition = OakTranslateExpressionToOil ( StatementElement -> GetSubElement ( ElementOffset ) );
				
				if ( IfCondition == NULL )
				{
					
					delete Body;
					
					return NULL;
					
				}
				
				ElementOffset ++;
				
				OilStatementBody * IfStatementBody = OakTranslateStatementBodyToOil ( StatementElement -> GetSubElement ( ElementOffset ) );
				
				if ( IfStatementBody == NULL )
				{
					
					delete IfCondition;
					delete Body;
					
					return NULL;
					
				}
				
				ElementOffset ++;
				
				std :: vector <OilExpression *> ElseIfConditions;
				std :: vector <OilStatementBody *> ElseIfStatementBodies;
				
				for ( uint32_t J = 0; J < IfElseData -> ElseIfCount; J ++ )
				{
					
					OilExpression * ElseIfCondition = OakTranslateExpressionToOil ( StatementElement -> GetSubElement ( ElementOffset ) );
					
					if ( ElseIfCondition == NULL )
					{
						
						delete IfCondition;
						delete IfStatementBody;
						delete Body;
						
						for ( uint32_t K = 0; K < ElseIfConditions.size (); K ++ )
							delete ElseIfConditions [ K ];
						
						for ( uint32_t K = 0; K < ElseIfStatementBodies.size (); K ++ )
							delete ElseIfStatementBodies [ K ];
						
						return NULL;
						
					}
					
					ElseIfConditions.push_back ( ElseIfCondition );
					
					ElementOffset ++;
					
					OilStatementBody * ElseIfStatementBody = OakTranslateStatementBodyToOil ( StatementElement -> GetSubElement ( ElementOffset ) );
					
					if ( ElseIfStatementBody == NULL )
					{
						
						delete IfCondition;
						delete IfStatementBody;
						delete Body;
						
						for ( uint32_t K = 0; K < ElseIfConditions.size (); K ++ )
							delete ElseIfConditions [ K ];
						
						for ( uint32_t K = 0; K < ElseIfStatementBodies.size (); K ++ )
							delete ElseIfStatementBodies [ K ];
						
						return NULL;
						
					}
					
					ElseIfStatementBodies.push_back ( ElseIfStatementBody );
					
					ElementOffset ++;
					
				}
				
				OilStatementBody * ElseStatementBody = NULL;
				
				if ( IfElseData -> Else )
				{
					
					ElseStatementBody = OakTranslateStatementBodyToOil ( StatementElement -> GetSubElement ( ElementOffset ) );
					
					if ( ElseStatementBody == NULL )
					{
						
						delete IfCondition;
						delete IfStatementBody;
						delete Body;
						
						for ( uint32_t K = 0; K < ElseIfConditions.size (); K ++ )
							delete ElseIfConditions [ K ];
						
						for ( uint32_t K = 0; K < ElseIfStatementBodies.size (); K ++ )
							delete ElseIfStatementBodies [ K ];
						
						return NULL;
						
					}
					
				}
				
				Body -> AddStatement ( new OilIfElse ( IfCondition, IfStatementBody, & ElseIfConditions [ 0 ], & ElseIfStatementBodies [ 0 ], IfElseData -> ElseIfCount, ElseStatementBody ) );
				
			}
			break;
			
			default:
				break;
			
		}
		
	}
	
	return Body;
	
}

OilConstStatement * OakTranslateConstStatementToOil ( const ASTElement * StatementElement )
{
	
	if ( ( StatementElement == NULL ) || ( StatementElement -> GetTag () != OakASTTags :: kASTTag_ConstStatement ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const OakConstStatementConstructor :: ElementData * BindingData = reinterpret_cast <const OakConstStatementConstructor :: ElementData *> ( StatementElement -> GetData () );
	
	OilTypeRef * Type = OakTranslateTypeRefToOil ( StatementElement -> GetSubElement ( 0 ) );
	
	if ( Type == NULL )
		return NULL;
	
	const ASTElement * IntiailizerElement = StatementElement -> GetSubElement ( 1 );
	
	OilExpression * InitializerExpression = OakTranslateExpressionToOil ( IntiailizerElement );
	
	if ( InitializerExpression == NULL )
	{
		
		delete Type;
		
		return NULL;
		
	}
	
	return new OilConstStatement ( BindingData -> Name, BindingData -> Public, Type, InitializerExpression );
	
}

OilBindingStatement * OakTranslateBindingStatementToOil ( const ASTElement * StatementElement )
{
	
	if ( ( StatementElement == NULL ) || ( StatementElement -> GetTag () != OakASTTags :: kASTTag_BindingStatement ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const OakBindingStatementConstructor :: ElementData * BindingData = reinterpret_cast <const OakBindingStatementConstructor :: ElementData *> ( StatementElement -> GetData () );
	
	OilTypeRef * Type = OakTranslateTypeRefToOil ( StatementElement -> GetSubElement ( 0 ) );
	
	if ( Type == NULL )
		return NULL;
	
	if ( BindingData -> Initialized )
	{
		
		const ASTElement * IntiailizerElement = StatementElement -> GetSubElement ( 1 );
		
		OilExpression * InitializerExpression = OakTranslateExpressionToOil ( IntiailizerElement );
		
		if ( InitializerExpression == NULL )
		{
			
			delete Type;
			
			return NULL;
			
		}
		
		return new OilBindingStatement ( BindingData -> Name, BindingData -> Public, BindingData -> Mutable, Type, InitializerExpression );
		
	}
	else
		return new OilBindingStatement ( BindingData -> Name, BindingData -> Public, BindingData -> Mutable, Type );
	
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
		
		IOilPrimary * Primary = OakTranslatePrimaryExpressionToOil ( SubExpressionElement );
		
		if ( Primary == NULL )
			return NULL;
		
		return new OilExpression ( Primary );
		
		
	}
	else if ( SubExpressionElement -> GetTag () == OakASTTags :: kASTTag_OperatorExpressionContainer )
	{
		
		const ASTElement * OperatorExpression = SubExpressionElement -> GetSubElement ( 0 );
		
		if ( OperatorExpression == NULL )
		{
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		IOilOperator * Operator = OakTranslateOperatorToOil ( OperatorExpression );
		
		if ( Operator == NULL )
			return NULL;
		
		return new OilExpression ( Operator );
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
	
	return NULL;
	
}

OilArrayLiteral * OakTranslateArrayLiteral ( const ASTElement * ArrayElement )
{
	
	if ( ( ArrayElement == NULL ) || ( ArrayElement -> GetTag () != OakASTTags :: kASTTag_ArrayLiteral ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
		
		return NULL;
		
	}
	
	const OakArrayLiteralConstructor :: ElementData * LiteralData = reinterpret_cast <const OakArrayLiteralConstructor :: ElementData *> ( ArrayElement -> GetData () );
	
	uint64_t ElementOffset = 0;
	
	IOilPrimary * SizePrimary = NULL;
	
	if ( LiteralData -> ExplicitCount )
	{
		
		const ASTElement * SizeElement = ArrayElement -> GetSubElement ( ElementOffset );
		ElementOffset ++;
		
		if ( SizeElement == NULL )
		{
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		SizePrimary = OakTranslateExpressionToOil ( SizeElement );
		
		if ( SizePrimary == NULL )
			return NULL;
		
	}
	
	OilTypeRef * TypeSpecifier = NULL;
	
	if ( LiteralData -> ExplicitType )
	{
		
		const ASTElement * TypeElement = ArrayElement -> GetSubElement ( ElementOffset );
		ElementOffset ++;
		
		if ( TypeElement == NULL )
		{
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		TypeSpecifier = OakTranslateTypeRefToOil ( TypeElement );
		
		if ( TypeSpecifier == NULL )
			return NULL;
		
	}
	
	std :: vector <IOilPrimary *> InitializerValues;
	
	uint64_t SubElementCount = ArrayElement -> GetSubElementCount ();
	
	for ( uint64_t I = ElementOffset; I < SubElementCount; I ++ )
	{
		
		const ASTElement * InitializerElement = ArrayElement -> GetSubElement ( I );
		
		IOilPrimary * Initializer = NULL;
		
		
		if ( InitializerElement -> GetTag () == OakASTTags :: kASTTag_PrimaryExpression )
			Initializer = OakTranslatePrimaryExpressionToOil ( InitializerElement );
		else if ( InitializerElement -> GetTag () == OakASTTags :: kASTTag_Expression )
			Initializer = OakTranslateExpressionToOil ( InitializerElement );
		else
		{
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		if ( Initializer == NULL )
		{
			
			for ( uint64_t I = 0; I < InitializerValues.size (); I ++ )
				delete InitializerValues [ I ];
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
			
			return NULL;
			
		}
		
		InitializerValues.push_back ( Initializer );
		
	}
	
	if ( LiteralData -> ExplicitCount )
	{
		
		if ( InitializerValues.size () > 0 )
			return new OilArrayLiteral ( SizePrimary, TypeSpecifier, & InitializerValues [ 0 ], InitializerValues.size () );
		else
			return new OilArrayLiteral ( SizePrimary, TypeSpecifier );
		
	}
	
	if ( InitializerValues.size () > 0 )
		return new OilArrayLiteral ( TypeSpecifier, & InitializerValues [ 0 ], InitializerValues.size () );
	
	return new OilArrayLiteral ( TypeSpecifier );
	
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
			return OakTranslateExpressionToOil ( SubElement -> GetSubElement ( 0 ) );
		
		case OakASTTags :: kASTTag_LiteralExpression:
			return OakTranslateLiteralToOil ( SubElement );
		
		case OakASTTags :: kASTTag_ArrayLiteral:
			return OakTranslateArrayLiteral ( SubElement );
		
		case OakASTTags :: kASTTag_SelfAllusion:
			return new OilAllusion ( OilAllusion :: SELF_ALLUSION );
		
		case OakASTTags :: kASTTag_BindingAllusion:
		{
			
			const OakBindingAllusionConstructor :: ElementData * AllusionData = reinterpret_cast <const OakBindingAllusionConstructor :: ElementData *> ( SubElement -> GetData () );
			
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
								
								WriteError ( SubElement, "Namespaces cannot have template specifications" );
								
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
								
								WriteError ( SubElement, "Namespaces cannot have template specifications" );
								
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
								
							WriteError ( SubElement, "Namespaces cannot have template specifications" );
							
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
								
							WriteError ( SubElement, "Namespaces cannot have template specifications" );
							
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
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser: " );
		
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
			
			std :: string ErrorString;
			
			char32_t Charachter;
			
			if ( ! OakParseCharLiteral ( LiteralToken -> GetSource (), Charachter, ErrorString ) )
			{
				
				if ( ErrorString != "" )
					WriteError ( LiteralElement, ErrorString );
				else
					WriteError ( LiteralElement, "Invalid char literal" );
				
				return NULL;
				
			}
			
			return new OilCharLiteral ( Charachter );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_FloatLiteralDefaultSize:
		{
			
			BigFloat FloatValue ( 0LL );
			
			if ( ! OakParseFloatLiteral ( LiteralToken -> GetSource (), FloatValue ) )
			{
				
				WriteError ( LiteralElement, "Invalid float literal" );
				
				return NULL;
				
			}
			
			return new OilFloatLiteral ( FloatValue, OilFloatLiteral :: kFloatType_Indeterminate );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_FloatLiteral32:
		{
			
			BigFloat FloatValue ( 0LL );
			
			if ( ! OakParseFloatLiteral ( LiteralToken -> GetSource (), FloatValue ) )
			{
				
				WriteError ( LiteralElement, "Invalid float literal" );
				
				return NULL;
				
			}
			
			return new OilFloatLiteral ( FloatValue, OilFloatLiteral :: kFloatType_32 );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_FloatLiteral64:
		{
			
			BigFloat FloatValue ( 0LL );
			
			if ( ! OakParseFloatLiteral ( LiteralToken -> GetSource (), FloatValue ) )
			{
				
				WriteError ( LiteralElement, "Invalid float literal" );
				
				return NULL;
				
			}
			
			return new OilFloatLiteral ( FloatValue, OilFloatLiteral :: kFloatType_64 );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteralDefault:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed 64-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x80 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI8, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x80 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI8_IfNegative, static_cast <int64_t> ( Value ) );
			
			if ( Value < 0x8000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI16, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x8000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI16_IfNegative, static_cast <int64_t> ( Value ) );
			
			if ( Value < 0x80000000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI32, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x80000000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI32_IfNegative, static_cast <int64_t> ( Value ) );
			
			if ( Value < 0x8000000000000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI64, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x8000000000000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinI64_IfNegative, static_cast <int64_t> ( Value ) );
			
			WriteError ( LiteralElement, "Integer literal overflows signed 64-bit precision" );
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral8:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed 8-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x80 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I8, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x80 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I8_IfNegative, static_cast <int64_t> ( Value ) );
			
			WriteError ( LiteralElement, "Integer literal overflows signed 8-bit precision" );
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral16:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed 16-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x8000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I16, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x8000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I16_IfNegative, static_cast <int64_t> ( Value ) );
			
			WriteError ( LiteralElement, "Integer literal overflows signed 16-bit precision" );
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral32:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed 32-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x80000000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I32, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x80000000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I32_IfNegative, static_cast <int64_t> ( Value ) );
			
			WriteError ( LiteralElement, "Integer literal overflows signed 32-bit precision" );
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_SignedIntegerLiteral64:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed 64-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x8000000000000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I64, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x8000000000000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_I64_IfNegative, static_cast <int64_t> ( Value ) );
			
			WriteError ( LiteralElement, "Integer literal overflows signed 64-bit precision" );
			
			return NULL;
			
		}
		break;
		
		// TODO: Make this detect machine pointer overflows dependent on target architecture...
		case OakTokenTags :: kTokenTag_SignedIntegerLiteralPointer:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed pointer precision" );
				
				return NULL;
				
			}
			
			return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_IPtr, static_cast <int64_t> ( Value ) );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteralDefault:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed 64-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x100 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinU8, Value );
			
			if ( Value < 0x10000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinU16, Value );
			
			if ( Value < 0x100000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Implied_MinU32, Value );
			
			return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_U64, Value );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral8:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows unsigned 8-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x100 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_U8, Value );
			
			WriteError ( LiteralElement, "Integer literal overflows unsigned 8-bit precision" );
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral16:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows unsigned 16-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x100 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_U16, Value );
			
			WriteError ( LiteralElement, "Integer literal overflows unsigned 16-bit precision" );
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral32:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows unsigned 32-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x100000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_U32, Value );
			
			WriteError ( LiteralElement, "Integer literal overflows unsigned 32-bit precision" );
			
			return NULL;
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteral64:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows unsigned 32-bit precision" );
				
				return NULL;
				
			}
			
			return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_U64, Value );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_UnsignedIntegerLiteralPointer:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows signed 64-bit precision" );
				
				return NULL;
				
			}
			
			return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_UPtr, static_cast <int64_t> ( Value ) );
			
		}
		break;
		
		case OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral:
		{
			
			bool Overflow64 = false;
			uint64_t Value = 0;
			
			OakParseIntegerLiteral ( LiteralToken -> GetSource (), Value, Overflow64 );
			
			if ( Overflow64 )
			{
				
				WriteError ( LiteralElement, "Integer literal overflows unsigned 64-bit precision" );
				
				return NULL;
				
			}
			
			if ( Value < 0x80 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI8, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x80 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI8_IfNegative, static_cast <int64_t> ( Value ) );
			
			if ( Value < 0x8000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI16, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x8000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI16_IfNegative, static_cast <int64_t> ( Value ) );
			
			if ( Value < 0x80000000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI32, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x80000000 )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI32_IfNegative, static_cast <int64_t> ( Value ) );
			
			if ( Value < 0x8000000000000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI64, static_cast <int64_t> ( Value ) );
			
			if ( Value == 0x8000000000000000ULL )
				return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Indeterminate_MinI64_IfNegative, Value );
			
			return new OilIntegerLiteral ( OilIntegerLiteral :: kIntType_Explicit_U64, Value );
			
			return NULL;
			
		}
		break;
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser with NULL element" );
	
	return NULL;
	
}

const std :: map <uint64_t, OilUnaryOperator :: Operator> _OakOilTranslation_OperatorTypeMap_Unary =
{
	
	{ OakASTTags :: kASTTag_Operator_PostfixIncrement, OilUnaryOperator :: kOperator_PostfixIncrement },
	{ OakASTTags :: kASTTag_Operator_PostfixDecrement, OilUnaryOperator :: kOperator_PostfixDecrement },
	{ OakASTTags :: kASTTag_Operator_PrefixIncrement, OilUnaryOperator :: kOperator_PrefixIncrement },
	{ OakASTTags :: kASTTag_Operator_PrefixDecrement, OilUnaryOperator :: kOperator_PrefixDecrement },
	{ OakASTTags :: kASTTag_Operator_BitwiseNot, OilUnaryOperator :: kOperator_BitwiseNot },
	{ OakASTTags :: kASTTag_Operator_LogicalNot, OilUnaryOperator :: kOperator_LogicalNot },
	{ OakASTTags :: kASTTag_Operator_UnaryPositive, OilUnaryOperator :: kOperator_UnaryPositive },
	{ OakASTTags :: kASTTag_Operator_UnaryNegate, OilUnaryOperator :: kOperator_UnaryNegative },
	{ OakASTTags :: kASTTag_Operator_Reference, OilUnaryOperator :: kOperator_Reference},
	{ OakASTTags :: kASTTag_Operator_ArrayAccess, OilUnaryOperator :: kOperator_ArrayAccess },
	{ OakASTTags :: kASTTag_Operator_FunctionCall, OilUnaryOperator :: kOperator_FunctionCall },
	
};

const std :: map <uint64_t, OilBinaryOperator :: Operator> _OakOilTranslation_OperatorTypeMap_Binary =
{
	
	{ OakASTTags :: kASTTag_Operator_DirectMemberAccess, OilBinaryOperator :: kOperator_DirectMemberAccess },
	{ OakASTTags :: kASTTag_Operator_IndirectMemberAccess, OilBinaryOperator :: kOperator_IndirectMemberAccess },
	{ OakASTTags :: kASTTag_Operator_Multiply, OilBinaryOperator :: kOperator_Multiply },
	{ OakASTTags :: kASTTag_Operator_Divide, OilBinaryOperator :: kOperator_Divide },
	{ OakASTTags :: kASTTag_Operator_Modulo, OilBinaryOperator :: kOperator_Modulus },
	{ OakASTTags :: kASTTag_Operator_Add, OilBinaryOperator :: kOperator_Addition },
	{ OakASTTags :: kASTTag_Operator_Subtract, OilBinaryOperator :: kOperator_Subtraction },
	{ OakASTTags :: kASTTag_Operator_LeftShift, OilBinaryOperator :: kOperator_ShiftLeft },
	{ OakASTTags :: kASTTag_Operator_LogicalRightShift, OilBinaryOperator :: kOperator_LogicalShiftRight },
	{ OakASTTags :: kASTTag_Operator_RightShift, OilBinaryOperator :: kOperator_ArithmeticShiftRight },
	{ OakASTTags :: kASTTag_Operator_GreaterThan, OilBinaryOperator :: kOperator_GreaterThan },
	{ OakASTTags :: kASTTag_Operator_LessThan, OilBinaryOperator :: kOperator_LessThan },
	{ OakASTTags :: kASTTag_Operator_GreaterThanOrEqual, OilBinaryOperator :: kOperator_GreaterThanOrEqual },
	{ OakASTTags :: kASTTag_Operator_LessThanOrEqual, OilBinaryOperator :: kOperator_LessThanOrEqual },
	{ OakASTTags :: kASTTag_Operator_NotEqual, OilBinaryOperator :: kOperator_NotEqual },
	{ OakASTTags :: kASTTag_Operator_Equal, OilBinaryOperator :: kOperator_Equal },
	{ OakASTTags :: kASTTag_Operator_BitwiseAnd, OilBinaryOperator :: kOperator_BitwiseAnd },
	{ OakASTTags :: kASTTag_Operator_BitwiseXor, OilBinaryOperator :: kOperator_BitwiseXor },
	{ OakASTTags :: kASTTag_Operator_BitwiseOr, OilBinaryOperator :: kOperator_BitwiseOr },
	{ OakASTTags :: kASTTag_Operator_LogicalAnd, OilBinaryOperator :: kOperator_LogicalAnd },
	{ OakASTTags :: kASTTag_Operator_LogicalOr, OilBinaryOperator :: kOperator_LogicalOr },
	{ OakASTTags :: kASTTag_Operator_Assignment, OilBinaryOperator :: kOperator_Assignment },
	{ OakASTTags :: kASTTag_Operator_CompoundMultiply, OilBinaryOperator :: kOperator_CompoundMultiply },
	{ OakASTTags :: kASTTag_Operator_CompoundDivide, OilBinaryOperator :: kOperator_CompoundDivide },
	{ OakASTTags :: kASTTag_Operator_CompoundModulo, OilBinaryOperator :: kOperator_CompoundModulus },
	{ OakASTTags :: kASTTag_Operator_CompoundAdd, OilBinaryOperator :: kOperator_CompoundAddition },
	{ OakASTTags :: kASTTag_Operator_CompoundSubtract, OilBinaryOperator :: kOperator_CompoundSubtraction },
	{ OakASTTags :: kASTTag_Operator_CompoundLeftShift, OilBinaryOperator :: kOperator_CompoundShiftLeft },
	{ OakASTTags :: kASTTag_Operator_CompoundLogicalRightShift, OilBinaryOperator :: kOperator_CompoundLogicalShiftRight },
	{ OakASTTags :: kASTTag_Operator_CompoundRightShift, OilBinaryOperator :: kOperator_CompoundArithmeticShiftRight },
	{ OakASTTags :: kASTTag_Operator_CompoundBitwiseAnd, OilBinaryOperator :: kOperator_CompoundBitwiseAnd },
	{ OakASTTags :: kASTTag_Operator_CompoundBitwiseOr, OilBinaryOperator :: kOperator_CompoundBitwiseOr },
	{ OakASTTags :: kASTTag_Operator_CompoundBitwiseXor, OilBinaryOperator :: kOperator_CompoundBitwiseXor },
	{ OakASTTags :: kASTTag_Operator_CompoundLogicalAnd, OilBinaryOperator :: kOperator_CompoundLogicalAnd },
	{ OakASTTags :: kASTTag_Operator_CompoundLogicalOr, OilBinaryOperator :: kOperator_CompoundLogicalOr },
	
};

IOilOperator * OakTranslateOperatorToOil ( const ASTElement * OperatorElement )
{
	
	uint64_t Tag = OperatorElement -> GetTag ();
	
	if ( ( Tag < OakASTTags :: kASTTag_Operator_Meta_EnumBoundsMin ) || ( Tag > OakASTTags :: kASTTag_Operator_Meta_EnumBoundsMax ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
		
		return NULL;
		
	}
	
	std :: map <uint64_t, OilUnaryOperator :: Operator> :: const_iterator UnaryIter = _OakOilTranslation_OperatorTypeMap_Unary.find ( Tag );
	std :: map <uint64_t, OilBinaryOperator :: Operator> :: const_iterator BinaryIter = ( UnaryIter == _OakOilTranslation_OperatorTypeMap_Unary.end () ) ? _OakOilTranslation_OperatorTypeMap_Binary.find ( Tag ) : _OakOilTranslation_OperatorTypeMap_Binary.end ();
	
	if ( UnaryIter != _OakOilTranslation_OperatorTypeMap_Unary.end () )
	{
		
		const ASTElement * TermElement = OperatorElement -> GetSubElement ( 0 );
		
		if ( TermElement == NULL )
		{
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
			
			return NULL;
			
		}
		
		if ( TermElement -> GetTag () == OakASTTags :: kASTTag_PrimaryExpression )
		{
			
			IOilPrimary * PrimaryTerm = OakTranslatePrimaryExpressionToOil ( TermElement );
			
			if ( PrimaryTerm == NULL )
				return NULL;
			
			return new OilUnaryOperator ( UnaryIter -> second, PrimaryTerm );
			
		}
		
		IOilOperator * OperatorTerm = OakTranslateOperatorToOil ( TermElement );
		
		if ( OperatorTerm == NULL )
			return NULL;
		
		return new OilUnaryOperator ( UnaryIter -> second, OperatorTerm );
		
	}
	else if ( BinaryIter != _OakOilTranslation_OperatorTypeMap_Binary.end () )
	{
		
		const ASTElement * LeftTermElement = OperatorElement -> GetSubElement ( 0 );
		const ASTElement * RightTermElement = OperatorElement -> GetSubElement ( 1 );
		
		if ( ( LeftTermElement == NULL ) || ( RightTermElement == NULL ) )
		{
			
			LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
			
			return NULL;
			
		}
		
		if ( LeftTermElement -> GetTag () == OakASTTags :: kASTTag_PrimaryExpression )
		{
			
			IOilPrimary * LeftPrimary = OakTranslatePrimaryExpressionToOil ( LeftTermElement );
			
			if ( LeftPrimary == NULL )
				return NULL;
			
			if ( RightTermElement -> GetTag () == OakASTTags :: kASTTag_PrimaryExpression )
			{
				
				IOilPrimary * RightPrimary = OakTranslatePrimaryExpressionToOil ( RightTermElement );
				
				if ( RightPrimary == NULL )
				{
					
					delete LeftPrimary;
					
					return NULL;
					
				}
				
				return new OilBinaryOperator ( BinaryIter -> second, LeftPrimary, RightPrimary );
				
			}
			
			IOilOperator * RightOperator = OakTranslateOperatorToOil ( RightTermElement );
			
			if ( RightOperator == NULL )
			{
				
				delete LeftPrimary;
				
				return NULL;
				
			}
			
			return new OilBinaryOperator ( BinaryIter -> second, LeftPrimary, RightOperator );
			
		}
		
		IOilOperator * LeftOperator = OakTranslateOperatorToOil ( LeftTermElement );
		
		if ( LeftOperator == NULL )
			return NULL;
		
		if ( RightTermElement -> GetTag () == OakASTTags :: kASTTag_PrimaryExpression )
		{
			
			IOilPrimary * RightPrimary = OakTranslatePrimaryExpressionToOil ( RightTermElement );
			
			if ( RightPrimary == NULL )
			{
				
				delete LeftOperator;
				
				return NULL;
				
			}
			
			return new OilBinaryOperator ( BinaryIter -> second, LeftOperator, RightPrimary );
			
		}
		
		IOilOperator * RightOperator = OakTranslateOperatorToOil ( RightTermElement );
		
		if ( RightOperator == NULL )
		{
			
			LeftOperator = NULL;
			
			return NULL;
			
		}
		
		return new OilBinaryOperator ( BinaryIter -> second, LeftOperator, RightOperator );
		
	}
	
	LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
	
	return NULL;
	
}

OilTraitDefinition * OakTranslateTraitToOil ( const ASTElement * TraitElement, OilDecoratorTag ** Decorators, uint32_t DecoratorCount )
{
	
	if ( ( TraitElement == NULL ) || ( TraitElement -> GetTag () != OakASTTags :: kASTTag_TraitDefinition ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
		
		return NULL;
		
	}
	
	const OakTraitDefinitionConstructor :: ElementData * TraitData = reinterpret_cast <const OakTraitDefinitionConstructor :: ElementData *> ( TraitElement -> GetData () );
	
	OilTemplateDefinition * TemplateDefinition = NULL;
	
	uint32_t ElementOffset = 0;
	
	if ( TraitData -> Templated )
	{
		
		const ASTElement * TemplateDefinitionElement = TraitElement -> GetSubElement ( 0 );
		
		TemplateDefinition = OakTranslateTemplateDefinitionToOil ( TemplateDefinitionElement );
		
		if ( TemplateDefinition == NULL )
			return NULL;
		
		ElementOffset = 1;
		
	}
	
	bool Builtin = false;
	
	for ( uint32_t I = 0; I < DecoratorCount; I ++ )
	{
		
		if ( IsSimpleDecoratorWithID ( Decorators [ I ], kDecoratorID_Builtin ) )
			Builtin = true;
		
		delete Decorators [ I ];
		
	}
	
	std :: vector <OilTraitFunction *> TraitFunctions;
	std :: vector <OilTraitMethod *> TraitMethods;
	std :: vector <OilTypeRef *> RequiredTraitRefs;
	
	if ( ! TraitData -> Empty )
	{
		
		const ASTElement * TraitMemberElement = TraitElement -> GetSubElement ( ElementOffset );
		
		while ( TraitMemberElement != NULL )
		{
			
			ElementOffset ++;
			
			if ( TraitMemberElement -> GetTag () == OakASTTags :: kASTTag_TraitRequirement )
			{
				
				const ASTElement * RequiredTraitElement = TraitMemberElement -> GetSubElement ( 0 );
				
				OilTypeRef * RequiredTraitRef = OakTranslateTraitRefToOil ( RequiredTraitElement );
				
				if ( RequiredTraitRef == NULL )
				{
					
					if ( TemplateDefinition != NULL )
						delete TemplateDefinition;
					
					for ( uint32_t I = 0; I < TraitFunctions.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < TraitMethods.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < RequiredTraitRefs.size (); I ++ )
						delete RequiredTraitRefs [ I ];
					
					return NULL;
					
				}
				
				RequiredTraitRefs.push_back ( RequiredTraitRef );
				
			}
			else if ( TraitMemberElement -> GetTag () == OakASTTags :: kASTTag_TraitFunction )
			{
				
				OilTraitFunction * Function = OakTranslateTraitFunctionToOil ( TraitMemberElement );
				
				if ( Function == NULL )
				{
					
					if ( TemplateDefinition != NULL )
						delete TemplateDefinition;
					
					for ( uint32_t I = 0; I < TraitFunctions.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < TraitMethods.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < RequiredTraitRefs.size (); I ++ )
						delete RequiredTraitRefs [ I ];
					
					return NULL;
					
				}
				
				TraitFunctions.push_back ( Function );
				
			}
			else
			{
				
				if ( TraitMemberElement -> GetTag () != OakASTTags :: kASTTag_TraitMethod )
				{
					
					WriteError ( TraitMemberElement, "Expected requirement, function, or method in trait definition" );
					
					if ( TemplateDefinition != NULL )
						delete TemplateDefinition;
					
					for ( uint32_t I = 0; I < TraitFunctions.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < TraitMethods.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < RequiredTraitRefs.size (); I ++ )
						delete RequiredTraitRefs [ I ];
					
					return NULL;
					
				}
				
				OilTraitMethod * Method = OakTranslateTraitMethodToOil ( TraitMemberElement );
				
				if ( Method == NULL )
				{
					
					if ( TemplateDefinition != NULL )
						delete TemplateDefinition;
					
					for ( uint32_t I = 0; I < TraitFunctions.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < TraitMethods.size (); I ++ )
						delete TraitFunctions [ I ];
					
					for ( uint32_t I = 0; I < RequiredTraitRefs.size (); I ++ )
						delete RequiredTraitRefs [ I ];
					
					return NULL;
					
				}
				
				TraitMethods.push_back ( Method );
				
			}	
			
			TraitMemberElement = TraitElement -> GetSubElement ( ElementOffset );
			
		}
		
	}
	
	OilTraitDefinition * TraitDef = new OilTraitDefinition ( TraitData -> Name, & RequiredTraitRefs [ 0 ], RequiredTraitRefs.size (), & TraitFunctions [ 0 ], TraitFunctions.size (), & TraitMethods [ 0 ], TraitMethods.size (), TemplateDefinition, Builtin );
	
	if ( TraitDef -> IsBuiltin () && ( ! Builtin ) )
		LOG_FATALERROR ( "BUILTIN FAILURE" );
	
	return TraitDef;
	
}

OilTraitMethod * OakTranslateTraitMethodToOil ( const ASTElement * MethodElement )
{
	
	if ( ( MethodElement == NULL ) || ( MethodElement -> GetTag () != OakASTTags :: kASTTag_TraitMethod ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
		
		return NULL;
		
	}
	
	const OakTraitMethodConstructor :: ElementData * TraitMethodData = reinterpret_cast <const OakTraitMethodConstructor :: ElementData *> ( MethodElement -> GetData () );
	
	OilTemplateDefinition * TemplateDefinition = NULL;
	
	uint32_t ElementOffset = 0;
	
	if ( TraitMethodData -> Templated )
	{
		
		const ASTElement * TemplateDefinitionElement = MethodElement -> GetSubElement ( ElementOffset );
		
		TemplateDefinition = OakTranslateTemplateDefinitionToOil ( TemplateDefinitionElement );
		
		if ( TemplateDefinition == NULL )
			return NULL;
		
		ElementOffset ++;
		
	}
	
	const ASTElement * ParameterListElement = MethodElement -> GetSubElement ( ElementOffset );
	
	OilMethodParameterList * ParameterList = OakTranslateMethodParameterListToOil ( ParameterListElement );
	
	if ( ParameterList == NULL )
	{
		
		delete TemplateDefinition;
		
		return NULL;
		
	}
	
	ElementOffset ++;
	
	OilTypeRef * ReturnType = NULL;
	
	if ( TraitMethodData -> ReturnTyped )
	{
		
		const ASTElement * ReturnTypeElement = MethodElement -> GetSubElement ( ElementOffset );
		
		ReturnType = OakTranslateReturnTypeToOil ( ReturnTypeElement );
		
		if ( ReturnType == NULL )
		{
			
			delete TemplateDefinition;
			delete ParameterList;
			
			return NULL;
			
		}
		
	}
	
	return new OilTraitMethod ( TraitMethodData -> Name, ParameterList, ReturnType, TemplateDefinition );
	
}

OilTraitFunction * OakTranslateTraitFunctionToOil ( const ASTElement * FunctionElement )
{
	
	if ( ( FunctionElement == NULL ) || ( FunctionElement -> GetTag () != OakASTTags :: kASTTag_TraitFunction ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
		
		return NULL;
		
	}
	
	const OakTraitFunctionConstructor :: ElementData * TraitFunctionData = reinterpret_cast <const OakTraitFunctionConstructor :: ElementData *> ( FunctionElement -> GetData () );
	
	OilTemplateDefinition * TemplateDefinition = NULL;
	
	uint32_t ElementOffset = 0;
	
	if ( TraitFunctionData -> Templated )
	{
		
		const ASTElement * TemplateDefinitionElement = FunctionElement -> GetSubElement ( ElementOffset );
		
		TemplateDefinition = OakTranslateTemplateDefinitionToOil ( TemplateDefinitionElement );
		
		if ( TemplateDefinition == NULL )
			return NULL;
		
		ElementOffset ++;
		
	}
	
	const ASTElement * ParameterListElement = FunctionElement -> GetSubElement ( ElementOffset );
	
	OilFunctionParameterList * ParameterList = OakTranslateFunctionParameterListToOil ( ParameterListElement );
	
	if ( ParameterList == NULL )
	{
		
		delete TemplateDefinition;
		
		return NULL;
		
	}
	
	ElementOffset ++;
	
	OilTypeRef * ReturnType = NULL;
	
	if ( TraitFunctionData -> ReturnTyped )
	{
		
		const ASTElement * ReturnTypeElement = FunctionElement -> GetSubElement ( ElementOffset );
		
		ReturnType = OakTranslateReturnTypeToOil ( ReturnTypeElement );
		
		if ( ReturnType == NULL )
		{
			
			delete TemplateDefinition;
			delete ParameterList;
			
			return NULL;
			
		}
		
	}
	
	return new OilTraitFunction ( TraitFunctionData -> Name, ParameterList, ReturnType, TemplateDefinition );
	
}

OilDecoratorTag * OakTranslateDecoratorTagToOil ( const ASTElement * DecoratorTagElement )
{
	
	if ( ( DecoratorTagElement == NULL ) || ( DecoratorTagElement -> GetTag () != OakASTTags :: kASTTag_DecoratorTag ) )
	{
		
		LOG_FATALERROR ( "Structurally invalid AST passed to OIL parser" );
		
		return NULL;
		
	}
	
	const OakDecoratorTagConstructor :: ElementData * DecoratorData = reinterpret_cast <const OakDecoratorTagConstructor :: ElementData *> ( DecoratorTagElement -> GetData () );
	
	OilDecoratorTag * NewTag = new OilDecoratorTag ( DecoratorData -> ID );
	
	return NewTag;
	
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
