#include <Parsing/Language/OakParenthesizedExpressionConstructor.h>

#include <Parsing/Language/OakExpressionConstructor.h>
#include <Parsing/Language/OakASTTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakParenthesizedExpressionConstructor & OakParenthesizedExpressionConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakParenthesizedExpressionConstructor> ();
	
}

OakParenthesizedExpressionConstructor :: OakParenthesizedExpressionConstructor ():
	ExpressionGroup ( { { & ( OakExpressionConstructor :: Instance () ), 0 } } )
{
}

OakParenthesizedExpressionConstructor :: ~OakParenthesizedExpressionConstructor ()
{
}

void OakParenthesizedExpressionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Open )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * ParenthesizedElement = new ASTElement ();
	
	ParenthesizedElement -> SetTag ( OakASTTags :: kASTTag_ParenthesizedExpression );
	ParenthesizedElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( ExpressionGroup.TryConstruction ( ParenthesizedElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete ParenthesizedElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ParenthesizedElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete ParenthesizedElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after begining of parenthetical expression";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
	{
		
		delete ParenthesizedElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after begining of parenthetical expression";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	ParenthesizedElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.ConstructedElement = ParenthesizedElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
