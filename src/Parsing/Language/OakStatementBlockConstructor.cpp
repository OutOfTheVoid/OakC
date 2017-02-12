#include <Parsing/Language/OakStatementBlockConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakIgnoreStatementConstructor.h>
#include <Parsing/Language/OakLoneSemicolonConstructor.h>
#include <Parsing/Language/OakExpressionStatementConstructor.h>
#include <Parsing/Language/OakReturnStatementConstructor.h>
#include <Parsing/Language/OakBindingStatementConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakStatementBlockConstructor OakStatementBlockConstructor :: Instance;

OakStatementBlockConstructor :: OakStatementBlockConstructor ():
	StatementGroup ()
{
	
	StatementGroup.AddConstructorCantidate ( & OakIgnoreStatementConstructor :: Instance, 0 );
	StatementGroup.AddConstructorCantidate ( & OakLoneSemicolonConstructor :: Instance, 0 );
	StatementGroup.AddConstructorCantidate ( & OakReturnStatementConstructor :: Instance, 0 );
	StatementGroup.AddConstructorCantidate ( & OakBindingStatementConstructor :: Instance, 0 );
	StatementGroup.AddConstructorCantidate ( & OakExpressionStatementConstructor :: Instance, 1 );
	
	StatementGroup.AddConstructorCantidate ( & Instance, 1 );
	
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
	uint64_t Offset = 0;
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		IsBlock = true;
		
		Offset ++;
		
	}
	
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
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	
	if ( StatementGroup.TryConstruction ( BlockElement, IsBlock ? 0xFFFFFFFFFFFFFFFF : 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Offset ], TokenCount ) == 0 )
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
		Output.ErrorProvokingToken = Input.Tokens [ Offset ];
		
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
			Output.ErrorProvokingToken = Input.Tokens [ Offset ];
			
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
