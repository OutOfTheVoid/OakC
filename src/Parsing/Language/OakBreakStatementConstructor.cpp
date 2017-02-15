#include <Parsing/Language/OakBreakStatementConstructor.h>
#include <Parsing/Language/OakLoopLabelConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakBreakStatementConstructor OakBreakStatementConstructor :: Instance;

OakBreakStatementConstructor :: OakBreakStatementConstructor ():
	LabelGroup ()
{
	
	LabelGroup.AddConstructorCantidate ( & OakLoopLabelConstructor :: Instance, 0 );
	
}

OakBreakStatementConstructor :: ~OakBreakStatementConstructor ()
{
}

void OakBreakStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Break ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * BreakData = new ElementData ();
	
	BreakData -> Labeled = false;
	
	ASTElement * BreakElement = new ASTElement ();
	
	BreakElement -> SetTag ( OakASTTags :: kASTTag_BreakStatement );
	BreakElement -> SetData ( BreakData, & ElementDataDestructor );
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Semicolon )
	{
		
		BreakElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
		
		Output.Accepted = true;
		Output.ConstructedElement = BreakElement;
		Output.TokensConsumed = 2;
		
		return;
		
	}
	
	BreakElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
		
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( LabelGroup.TryConstruction ( BreakElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete BreakElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected loop label or semicolon in break statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete BreakElement;
		
		Output.Error = true;
		Output.Accepted = false;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete BreakElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of break statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	BreakData -> Labeled = true;
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		delete BreakElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of break statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	BreakElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.ConstructedElement = BreakElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}

void OakBreakStatementConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
