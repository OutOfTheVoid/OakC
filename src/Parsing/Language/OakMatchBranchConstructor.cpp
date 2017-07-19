#include <Parsing/Language/OakMatchBranchConstructor.h>
#include <Parsing/Language/OakStructDestructureConstructor.h>
#include <Parsing/Language/OakLiteralExpressionConstructor.h>
#include <Parsing/Language/OakArrayLiteralConstructor.h>
#include <Parsing/Language/OakStructLiteralConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakAllusionConstructor.h>
#include <Parsing/Language/OakStatementBlockConstructor.h>

#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#ifndef NULL
	#define NULL nullptr
#endif

#include <Utils/GlobalSingleton.h>

OakMatchBranchConstructor & OakMatchBranchConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakMatchBranchConstructor> ();
	
}

OakMatchBranchConstructor :: OakMatchBranchConstructor ():
	LiteralGroup ( 
	{
		
		{ & ( OakLiteralExpressionConstructor :: Instance () ), 0 },
		{ & ( OakArrayLiteralConstructor :: Instance () ), 0 },
		{ & ( OakStructLiteralConstructor :: Instance () ), 0 },
		
	} ),
	DestructureGroup ( { { & ( OakStructDestructureConstructor :: Instance () ), 0 } } ),
	AllusionGroup ( { { & ( OakAllusionConstructor :: Instance () ), 0 } } ),
	StatementBlockGroup ( { { & ( OakStatementBlockConstructor :: Instance () ), 0 } } )
{
}

OakMatchBranchConstructor :: ~OakMatchBranchConstructor ()
{
}

void OakMatchBranchConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	ElementData * MatchData = new ElementData;
	
	ASTElement * MatchElement = new ASTElement ();
	
	MatchElement -> SetTag ( OakASTTags :: kASTTag_MatchBranch );
	MatchElement -> SetData ( MatchData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount;
	
	bool Solved = false;
	
	const Token * CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Other ) )
	{
		
		TokenCount --;
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
		{
			
			delete MatchElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected colon after other match branch";
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		Solved = true;
		
		MatchData -> Type = kBranchType_Other;
		
		TokenCount --;
		
	}
	
	if ( ( ! Solved ) && ( AllusionGroup.TryConstruction ( MatchElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 ) )
	{
		
		if ( Error )
		{
			
			delete MatchElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TokenCount < 3 )
		{
			
			delete MatchElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected body for match branch";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Parenthesis_Open )
		{
			
			TokenCount --;
			
			CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
			{
				
				delete MatchElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = "Expected body for match branch";
				Output.ErrorProvokingToken = CurrentToken;
				
				return;
				
			}
			
			MatchData -> BindingName = CurrentToken -> GetSource ();
			
			TokenCount --;
			
			CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
			{
				
				delete MatchElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = "Expected closing parenthesis after target value of match branch";
				Output.ErrorProvokingToken = CurrentToken;
				
				return;
				
			}
			
			TokenCount --;
			
			CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
			{
				
				delete MatchElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = "Expected colon after match branch target value";
				Output.ErrorProvokingToken = CurrentToken;
				
				return;
				
			}
			
			Solved = true;
			
			MatchData -> Type = kBranchType_ValueAllusionMatch;
			
			TokenCount --;
			
		}
		else if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Colon )
		{
			
			Solved = true;
			
			MatchData -> Type = kBranchType_BasicAllusionMatch;
			
			TokenCount --;
			
		}
		else if ( DestructureGroup.TryConstruction ( MatchElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
		{
			
			if ( Error )
			{
				
				delete MatchElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = ErrorString;
				Output.ErrorProvokingToken = ErrorToken;
				
				return;
				
			}
			
			CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
			{
				
				delete MatchElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = "Expected colon after match branch target value";
				Output.ErrorProvokingToken = ErrorToken;
				
				return;
				
			}
			
			Solved = true;
			
			MatchData -> Type = kBranchType_DestructureMatch;
			
			TokenCount --;
			
		}
		
	}
	
	ASTElement * PrimaryExpressionContainerElement = new ASTElement ();
	PrimaryExpressionContainerElement -> SetTag ( OakASTTags :: kASTTag_PrimaryExpression );
	
	if ( ( ! Solved ) && ( LiteralGroup.TryConstruction ( PrimaryExpressionContainerElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 ) )
	{
		
		if ( Error )
		{
			
			delete MatchElement;
			delete PrimaryExpressionContainerElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
		{
			
			delete MatchElement;
			delete PrimaryExpressionContainerElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected colon after literal match branch";
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		Solved = true;
		
		MatchElement -> AddSubElement ( PrimaryExpressionContainerElement );
		
		MatchData -> Type = kBranchType_LiteralMatch;
		
		TokenCount --;
		
	}
	else if ( ! Solved )
	{
		
		delete MatchElement;
		
		Output.Accepted = false;
		
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
	
	if ( StatementBlockGroup.TryConstruction ( MatchElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( Error )
		{
			
			delete MatchElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		delete MatchElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for match branch";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
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
	
	Output.Accepted = true;
	Output.ConstructedElement = MatchElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}

void OakMatchBranchConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
