#include <Parsing/Language/OakMatchStatementConstructor.h>
#include <Parsing/Language/OakMatchBranchConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

OakMatchStatementConstructor OakMatchStatementConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakMatchStatementConstructor_ExpressionGroupEntries [] = { { & OakExpressionConstructor :: Instance, 0 } };

ASTConstructionGroup :: StaticInitEntry _OakMatchStatementConstructor_MatchesGroupEntries [] =
{
	
	{ & OakMatchBranchConstructor :: Instance, 0 }
	
};

OakMatchStatementConstructor :: OakMatchStatementConstructor ():
	ExpressionGroup ( _OakMatchStatementConstructor_ExpressionGroupEntries, 1 ),
	MatchesGroup ( _OakMatchStatementConstructor_MatchesGroupEntries, 1 )
{	
}

OakMatchStatementConstructor :: ~OakMatchStatementConstructor ()
{
}

void OakMatchStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 6 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Match ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Open )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * MatchElement = new ASTElement ();
	
	MatchElement -> SetTag ( OakASTTags :: kASTTag_Match );
	MatchElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( ExpressionGroup.TryConstruction ( MatchElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected expression after match statement open parenthesis";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after match statement matchee";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after matchee expression in match statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	if ( TokenCount == 0 )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected opening curly bracket after matchee expression in match statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected opening curly bracket after matchee expression in match statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	MatchElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ], 2 );
	
	TokenCount --;
	
	if ( TokenCount == 0 )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of match statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	MatchesGroup.TryConstruction ( MatchElement, 0xFFFFFFFF, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
	
	if ( Error )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of match statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket after matchee expression in match statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.ConstructedElement = MatchElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}


