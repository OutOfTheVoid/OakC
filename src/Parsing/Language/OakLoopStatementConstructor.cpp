#include <Parsing/Language/OakLoopStatementConstructor.h>
#include <Parsing/Language/OakLoopLabelConstructor.h>
#include <Parsing/Language/OakStatementBlockConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

OakLoopStatementConstructor OakLoopStatementConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakLoopStatementConstructor_LoopLabelGroupEntries [] = { { & OakLoopLabelConstructor :: Instance, 0 } };
ASTConstructionGroup :: StaticInitEntry _OakLoopStatementConstructor_StatementBodyGroupEntries [] = { { & OakStatementBlockConstructor :: Instance, 0 } };

OakLoopStatementConstructor :: OakLoopStatementConstructor ():
	LoopLabelGroup ( _OakLoopStatementConstructor_LoopLabelGroupEntries, 1 ),
	StatementBodyGroup ( _OakLoopStatementConstructor_StatementBodyGroupEntries, 1 )
{
}

OakLoopStatementConstructor :: ~OakLoopStatementConstructor ()
{
}

void OakLoopStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Loop ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * Data = new ElementData ();
	
	ASTElement * LoopElement = new ASTElement ();
	
	LoopElement -> SetTag ( OakASTTags :: kASTTag_LoopStatement );
	LoopElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( LoopLabelGroup.TryConstruction ( LoopElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
		{
			
			delete LoopElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected colon between loop label and loop body";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		LoopElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
	}
	
	if ( Error )
	{
		
		delete LoopElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( StatementBodyGroup.TryConstruction ( LoopElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete LoopElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected statement or block after loop statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete LoopElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.ConstructedElement = LoopElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
		
}

void OakLoopStatementConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
