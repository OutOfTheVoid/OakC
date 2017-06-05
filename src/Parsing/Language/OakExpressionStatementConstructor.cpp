#include <Parsing/Language/OakExpressionStatementConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakExpressionConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

OakExpressionStatementConstructor OakExpressionStatementConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakExpressionStatementConstructor_RValueGroupGroup [] = { { & OakExpressionConstructor :: Instance, 0 } };

OakExpressionStatementConstructor :: OakExpressionStatementConstructor ():
	RValueGroup ( _OakExpressionStatementConstructor_RValueGroupGroup, 1 )
{
}
	
OakExpressionStatementConstructor :: ~OakExpressionStatementConstructor ()
{
}

void OakExpressionStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * StatementElement = new ASTElement ();
	
	StatementElement -> SetTag ( OakASTTags :: kASTTag_ExpressionStatement );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( RValueGroup.TryConstruction ( StatementElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete StatementElement;
		
		Output.Accepted = false;
		
		if ( ConstructionError )
		{
			
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
		}
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete StatementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete StatementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of statement";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		delete StatementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = StatementElement;
	
}
