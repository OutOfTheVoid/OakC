#include <Parsing/Language/OakIfElseStatementConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>
#include <Parsing/Language/OakStatementBlockConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakIfElseStatementConstructor & OakIfElseStatementConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakIfElseStatementConstructor> ();
	
}

OakIfElseStatementConstructor :: OakIfElseStatementConstructor ():
	ExpressionGroup ( { { & ( OakExpressionConstructor :: Instance () ), 0 } } ),
	StatementBodyGroup ( { { & ( OakStatementBlockConstructor :: Instance () ), 0 } } )
{
}

OakIfElseStatementConstructor :: ~OakIfElseStatementConstructor ()
{
}

void OakIfElseStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 5 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_If ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Open )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected condition after if statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ElementData * IfElseData = new ElementData ();
	
	IfElseData -> Else = 0;
	IfElseData -> ElseIfCount = 0;
	
	ASTElement * IfElseElement = new ASTElement ();
	
	IfElseElement -> SetTag ( OakASTTags :: kASTTag_IfElseStatement );
	IfElseElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	IfElseElement -> SetData ( IfElseData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( ExpressionGroup.TryConstruction ( IfElseElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected in parenthesized boolean expression after if statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis after if statement condition";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
	{
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected condition after if statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	IfElseElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	TokenCount --;
	
	if ( StatementBodyGroup.TryConstruction ( IfElseElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( Error )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected statement or block after if statement condition";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	while ( true )
	{
		
		if ( TokenCount < 5 )
		{
			
			Output.Accepted = true;
			Output.ConstructedElement = IfElseElement;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			
			return;
			
		}
		
		CurrentToken = CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Else ) )
		{
			
			Output.Accepted = true;
			Output.ConstructedElement = IfElseElement;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			
			return;
			
		}
		
		IfElseElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		TokenCount --;
		
		CurrentToken = CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_If ) )
			break;
		
		IfElseElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 2 );
		TokenCount --;
		
		CurrentToken = CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Open )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected in parenthesized boolean expression after if statement";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		TokenCount --;
		
		if ( ExpressionGroup.TryConstruction ( IfElseElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected in parenthesized boolean expression after else-if statement";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		if ( Error )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing parenthesis after if statement condition";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		CurrentToken = CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing parenthesis after condition expression in if statement";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		IfElseElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		TokenCount --;
		
		if ( StatementBodyGroup.TryConstruction ( IfElseElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected statement or block after else-if statement condition";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		if ( Error )
		{
			
			delete IfElseElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		IfElseData -> ElseIfCount ++;
		
	}
	
	if ( StatementBodyGroup.TryConstruction ( IfElseElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected statement or block after else statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete IfElseElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	IfElseData -> Else = true;
	
	Output.Accepted = true;
	Output.ConstructedElement = IfElseElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;		
	
}

void OakIfElseStatementConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}

