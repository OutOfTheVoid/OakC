#include <Parsing/Language/OakExpressionConstructor.h>
#include <Parsing/Language/OakLiteralExpressionConstructor.h>
#include <Parsing/Language/OakParenthesizedExpressionConstructor.h>

#include <Parsing/Language/OakASTTags.h>

OakLiteralExpressionConstructor _OakExpressionConstructor_OakLiteralExpressionConstructorInstance;
OakParenthesizedExpressionConstructor _OakExpressionConstructor_OakParenthesizedExpressionConstructorInstance;

OakExpressionConstructor :: OakExpressionConstructor ():
	SubExpressionGroup ()
{
	
	SubExpressionGroup.AddConstructorCantidate ( & _OakExpressionConstructor_OakParenthesizedExpressionConstructorInstance, 0 );
	
	// This must be the highest priority ( last tested ).
	SubExpressionGroup.AddConstructorCantidate ( & _OakExpressionConstructor_OakLiteralExpressionConstructorInstance, 1 );
	
}

OakExpressionConstructor :: ~OakExpressionConstructor ()
{
}

void OakExpressionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * ExpressionStatementElement = new ASTElement ();
	
	ExpressionStatementElement -> SetTag ( OakASTTags :: kASTTag_Expression );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( SubExpressionGroup.TryConstruction ( ExpressionStatementElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete ExpressionStatementElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ExpressionStatementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = ExpressionStatementElement;
	
}

