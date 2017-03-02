#include <Parsing/Language/OakStatementBlockConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakIgnoreStatementConstructor.h>
#include <Parsing/Language/OakLoneSemicolonConstructor.h>
#include <Parsing/Language/OakExpressionStatementConstructor.h>
#include <Parsing/Language/OakReturnStatementConstructor.h>
#include <Parsing/Language/OakBindingStatementConstructor.h>
#include <Parsing/Language/OakIfElseStatementConstructor.h>
#include <Parsing/Language/OakWhileStatementConstructor.h>
#include <Parsing/Language/OakDoWhileStatementConstructor.h>
#include <Parsing/Language/OakLoopStatementConstructor.h>
#include <Parsing/Language/OakBreakStatementConstructor.h>
#include <Parsing/Language/OakBindingStatementConstructor.h>
#include <Parsing/Language/OakConstStatementConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakStatementBlockConstructor OakStatementBlockConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakStatementBlockConstructor_StatementGroupEntries [] =
{
	
	{ & OakIgnoreStatementConstructor :: Instance, 0 },
	{ & OakLoneSemicolonConstructor :: Instance, 0 },
	{ & OakReturnStatementConstructor :: Instance, 0 },
	{ & OakIfElseStatementConstructor :: Instance, 0 },
	{ & OakWhileStatementConstructor :: Instance, 0 },
	{ & OakDoWhileStatementConstructor :: Instance, 0 },
	{ & OakBreakStatementConstructor :: Instance, 0 },
	{ & OakLoopStatementConstructor :: Instance, 0 },
	{ & OakConstStatementConstructor :: Instance, 0 },
	{ & OakBindingStatementConstructor :: Instance, 0 },
	{ & OakExpressionStatementConstructor :: Instance, 1 },
	
	{ & OakStatementBlockConstructor :: Instance, 1 },
	
};

OakStatementBlockConstructor :: OakStatementBlockConstructor ():
	StatementGroup ( _OakStatementBlockConstructor_StatementGroupEntries, 13 )
{
}

OakStatementBlockConstructor :: ~OakStatementBlockConstructor ()
{
}

void OakStatementBlockConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 1 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	bool IsBlock = false;
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_CurlyBracket_Open )
		IsBlock = true;
	
	if ( Input.ParentElement -> GetTag () == OakASTTags :: kASTTag_StatementBlock )
	{
		
		const ElementData * ParentBlockData = reinterpret_cast <const ElementData *> ( Input.ParentElement -> GetData () );
		
		if ( ! ParentBlockData -> IsBlock )
		{
			
			Output.Accepted = false;
			
			return;
			
		}
		
	}
	
	ElementData * BlockData = new ElementData ();
	
	BlockData -> IsBlock = IsBlock;
	
	ASTElement * BlockElement = new ASTElement ();
	
	BlockElement -> SetTag ( OakASTTags :: kASTTag_StatementBlock );
	BlockElement -> SetData ( BlockData, & ElementDataDestructor );
	
	if ( IsBlock )
		BlockElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - ( IsBlock ? 1 : 0 );
	
	if ( StatementGroup.TryConstruction ( BlockElement, IsBlock ? 0xFFFFFFFFFFFFFFFF : 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( ! IsBlock )
		{
			
			delete BlockElement;
			
			Output.Accepted = false;
			
			if ( Error )
			{
				
				Output.Error = true;
				Output.ErrorSuggestion = ErrorString;
				Output.ErrorProvokingToken = ErrorToken;
				
			}
			
			return;
			
		}
		
	}
	
	if ( Error )
	{
		
		delete BlockElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( ( TokenCount == 0 ) && IsBlock )
	{
		
		delete BlockElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "expected closing curly bracket at end of block";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	if ( IsBlock )
	{
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
		{
			
			delete BlockElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "expected closing curly bracket at end of block";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			return;
			
		}
		
		BlockElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		TokenCount --;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = BlockElement;
	
}

void OakStatementBlockConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
