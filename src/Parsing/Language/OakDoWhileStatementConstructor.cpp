#include <Parsing/Language/OakDoWhileStatementConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>
#include <Parsing/Language/OakStatementBlockConstructor.h>
#include <Parsing/Language/OakLoopLabelConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

OakDoWhileStatementConstructor OakDoWhileStatementConstructor :: Instance;

OakDoWhileStatementConstructor :: OakDoWhileStatementConstructor ():
	ExpressionGroup (),
	StatementBodyGroup ()
{
	
	ExpressionGroup.AddConstructorCantidate ( & OakExpressionConstructor :: Instance, 0 );
	StatementBodyGroup.AddConstructorCantidate ( & OakStatementBlockConstructor :: Instance, 0 );
	LoopLabelGroup.AddConstructorCantidate ( & OakLoopLabelConstructor :: Instance, 0 );
	
}

OakDoWhileStatementConstructor :: ~OakDoWhileStatementConstructor ()
{
}

void OakDoWhileStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 5 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Do ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * WhileElement = new ASTElement ();
	
	WhileElement -> SetTag ( OakASTTags :: kASTTag_DoWhileStatement );
	WhileElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( LoopLabelGroup.TryConstruction ( WhileElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
		{
			
			delete WhileElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected colon between loop label and loop body";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		WhileElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
	}
	
	if ( Error )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( StatementBodyGroup.TryConstruction ( WhileElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected statement or block after do statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount < 5 )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected while condition after do block";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_While ) )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after while statement condition";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Open )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected condition after while statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	WhileElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ], 2 );
	TokenCount --;
	
	if ( ExpressionGroup.TryConstruction ( WhileElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected in parenthesized boolean expression after while statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after while statement condition";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after while statement condition";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		delete WhileElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon after while statement condition in do-while loop";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	WhileElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ], 2 );
	TokenCount --;
	
	Output.Accepted = true;
	Output.ConstructedElement = WhileElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
