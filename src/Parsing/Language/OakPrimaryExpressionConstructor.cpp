#include <Parsing/Language/OakPrimaryExpressionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakLiteralExpressionConstructor.h>
#include <Parsing/Language/OakParenthesizedExpressionConstructor.h>

OakLiteralExpressionConstructor _OakPrimaryExpressionConstructor_OakLiteralExpressionConstructorInstance;
OakParenthesizedExpressionConstructor _OakPrimaryExpressionConstructor_OakParenthesizedExpressionConstructorInstance;

OakPrimaryExpressionConstructor :: OakPrimaryExpressionConstructor ():
	PrimaryGroup ()
{
	
	PrimaryGroup.AddConstructorCantidate ( & _OakPrimaryExpressionConstructor_OakParenthesizedExpressionConstructorInstance, 0 );
	PrimaryGroup.AddConstructorCantidate ( & _OakPrimaryExpressionConstructor_OakLiteralExpressionConstructorInstance, 1 );
	
}

OakPrimaryExpressionConstructor :: ~OakPrimaryExpressionConstructor ()
{
}

void OakPrimaryExpressionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * PrimaryElement = new ASTElement ();
	
	PrimaryElement -> SetTag ( OakASTTags :: kASTTag_PrimaryExpression );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( PrimaryGroup.TryConstruction ( PrimaryElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete PrimaryElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete PrimaryElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = PrimaryElement;
	
}

