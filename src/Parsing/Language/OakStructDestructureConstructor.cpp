#include <Parsing/Language/OakStructDestructureConstructor.h>
#include <Parsing/Language/OakMemberDestructureConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

OakStructDestructureConstructor OakStructDestructureConstructor :: Instance;


ASTConstructionGroup :: StaticInitEntry _OakStructDestructureConstructor_MemberDestructGroupEntries [] =
{
	
	{ & OakMemberDestructureConstructor :: Instance, 0 }
	
};

OakStructDestructureConstructor :: OakStructDestructureConstructor ():
	MemberDestructGroup ( _OakStructDestructureConstructor_MemberDestructGroupEntries, 1 )
{
}

OakStructDestructureConstructor :: ~OakStructDestructureConstructor ()
{
}

void OakStructDestructureConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * DestructureElement = new ASTElement ();
	
	DestructureElement -> SetTag ( OakASTTags :: kASTTag_StructDestructure );
	DestructureElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	while ( MemberDestructGroup.TryConstruction ( DestructureElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		if ( Error )
		{
			
			delete DestructureElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete DestructureElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing curly bracket at end of destructure";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
			break;
			
		TokenCount --;
		
	}
	
	if ( Error )
	{
		
		delete DestructureElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete DestructureElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of destructure";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete DestructureElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of destructure";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = DestructureElement;
	
}
