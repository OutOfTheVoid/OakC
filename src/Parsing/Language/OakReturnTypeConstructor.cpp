#include <Parsing/Language/OakReturnTypeConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakPointerTypeConstructor.h>
#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

OakPointerTypeConstructor _OakReturnTypeConstructor_OakPointerTypeConstructorInstance;
OakBareTypeNameConstructor _OakReturnTypeConstructor_OakBareTypeNameConstructorInstance;
OakTemplatedTypeNameConstructor _OakReturnTypeConstructor_OakTemplatedTypeNameConstructorInstance;
OakNamespacedTypeNameConstructor _OakReturnTypeConstructor_OakNamespacedTypeNameConstructorIstance;
OakNamespacedTemplatedTypeNameConstructor _OakReturnTypeConstructor_OakNamespacedTemplatedTypeNameConstructorInstance;

OakReturnTypeConstructor :: OakReturnTypeConstructor ():
	TypeGroup ()
{
	
	TypeGroup.AddConstructorCantidate ( & _OakReturnTypeConstructor_OakPointerTypeConstructorInstance, 0 );
	TypeGroup.AddConstructorCantidate ( & _OakReturnTypeConstructor_OakNamespacedTemplatedTypeNameConstructorInstance, 0 );
	TypeGroup.AddConstructorCantidate ( & _OakReturnTypeConstructor_OakNamespacedTypeNameConstructorIstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakReturnTypeConstructor_OakTemplatedTypeNameConstructorInstance, 1 );
	TypeGroup.AddConstructorCantidate ( & _OakReturnTypeConstructor_OakBareTypeNameConstructorInstance, 2 );
	
}

OakReturnTypeConstructor :: ~OakReturnTypeConstructor ()
{
}

void OakReturnTypeConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( Input.Tokens [ 0 ] -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * ReturnTypeElement = new ASTElement ();
	
	ReturnTypeElement -> SetTag ( OakASTTags :: kASTTag_ReturnType );
	ReturnTypeElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( ReturnTypeElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete ReturnTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "expected type name after colon in return type";
		Output.ErrorProvokingToken = Input.Tokens [ 1 ];
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ReturnTypeElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.ConstructedElement = ReturnTypeElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
