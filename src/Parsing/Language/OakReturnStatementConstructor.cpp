#include <Parsing/Language/OakReturnStatementConstructor.h>

#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakExpressionConstructor.h>
#include <Parsing/Language/OakASTTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakReturnStatementConstructor OakReturnStatementConstructor :: Instance;

OakReturnStatementConstructor :: OakReturnStatementConstructor ():
	ExpressionGroup ()
{
	
	ExpressionGroup.AddConstructorCantidate ( & OakExpressionConstructor :: Instance, 0 );
	
}

OakReturnStatementConstructor :: ~OakReturnStatementConstructor ()
{
}

void OakReturnStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Return ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * ReturnElement = new ASTElement ();
	
	ReturnElement -> SetTag ( OakASTTags :: kASTTag_ReturnStatement );
	ReturnElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( ExpressionGroup.TryConstruction ( ReturnElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete ReturnElement;
		
		Output.Accepted = false;
		
		if ( ConstructionError )
		{
			
			delete ReturnElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ReturnElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete ReturnElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of return statement";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		delete ReturnElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of return statement";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	ReturnElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.ConstructedElement = ReturnElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
