#include <Parsing/Language/OakFunctionParameterConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakPointerTypeConstructor.h>
#include <Parsing/Language/OakReferenceTypeConstructor.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakPointerTypeConstructor _OakFunctionParameterConstructor_OakPointerTypeConstructorInstructor;
OakReferenceTypeConstructor _OakFunctionParameterConstructor_OakReferenceTypeConstructorInstance;

OakBareTypeNameConstructor _OakFunctionParameterConstructor_OakBareTypeNameConstructorInstance;
OakTemplatedTypeNameConstructor _OakFunctionParameterConstructor_OakTemplatedTypeNameConstructorInstance;
OakNamespacedTypeNameConstructor _OakFunctionParameterConstructor_OakNamespacedTypeNameConstructorIstance;
OakNamespacedTemplatedTypeNameConstructor _OakFunctionParameterConstructor_OakNamespacedTemplatedTypeNameConstructorInstance;

OakFunctionParameterConstructor :: OakFunctionParameterConstructor ():
	TypeGroup ()
{
	
	TypeGroup.AddConstructorCantidate ( & _OakFunctionParameterConstructor_OakPointerTypeConstructorInstructor, 0 );
	TypeGroup.AddConstructorCantidate ( & _OakFunctionParameterConstructor_OakReferenceTypeConstructorInstance, 0 );
	
	TypeGroup.AddConstructorCantidate ( & _OakFunctionParameterConstructor_OakNamespacedTemplatedTypeNameConstructorInstance, 0 );
	TypeGroup.AddConstructorCantidate ( & _OakFunctionParameterConstructor_OakNamespacedTypeNameConstructorIstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakFunctionParameterConstructor_OakTemplatedTypeNameConstructorInstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakFunctionParameterConstructor_OakBareTypeNameConstructorInstance, 2 );
	
	
}

OakFunctionParameterConstructor :: ~OakFunctionParameterConstructor ()
{
}

void OakFunctionParameterConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * FunctionParamData = new ElementData ();
	
	FunctionParamData -> Name = Input.Tokens [ 0 ] -> GetSource ();
	
	ASTElement * FunctionParamElement = new ASTElement ();
	
	FunctionParamElement -> SetTag ( OakASTTags :: kASTTag_FunctionParameter );
	FunctionParamElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	FunctionParamElement -> SetData ( FunctionParamData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( FunctionParamElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete FunctionParamElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected type name after colon in function parameter constructor";
		Output.ErrorProvokingToken = Input.Tokens [ 3 ];
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete FunctionParamElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = FunctionParamElement;
	
}

void OakFunctionParameterConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
