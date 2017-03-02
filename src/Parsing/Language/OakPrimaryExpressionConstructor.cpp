#include <Parsing/Language/OakPrimaryExpressionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakLiteralExpressionConstructor.h>
#include <Parsing/Language/OakParenthesizedExpressionConstructor.h>
#include <Parsing/Language/OakBindingAllusionConstructor.h>
#include <Parsing/Language/OakSelfAllusionConstructor.h>
#include <Parsing/Language/OakArrayLiteralConstructor.h>

OakPrimaryExpressionConstructor OakPrimaryExpressionConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakPrimaryExpressionConstructor_PrimaryGroupEntries [] =
{
	
	{ & OakParenthesizedExpressionConstructor :: Instance, 0 },
	{ & OakLiteralExpressionConstructor :: Instance, 1 },
	{ & OakArrayLiteralConstructor :: Instance, 1 },
	{ & OakSelfAllusionConstructor :: Instance, 2 },
	{ & OakBindingAllusionConstructor :: Instance, 2 },
	
};

OakPrimaryExpressionConstructor :: OakPrimaryExpressionConstructor ():
	PrimaryGroup ( _OakPrimaryExpressionConstructor_PrimaryGroupEntries, 5 )
{
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

