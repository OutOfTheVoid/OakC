#include <Parsing/Language/OakMemberDestructureConstructor.h>
#include <Parsing/Language/OakStructDestructureConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

OakMemberDestructureConstructor OakMemberDestructureConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakMemberDestructureConstructor_DestructureGroupEntries [] =
{
	
	{ & OakStructDestructureConstructor :: Instance, 0 }
	
};

OakMemberDestructureConstructor :: OakMemberDestructureConstructor ():
	DestructureGroup ( _OakMemberDestructureConstructor_DestructureGroupEntries, 1 )
{
}

OakMemberDestructureConstructor :: ~OakMemberDestructureConstructor ()
{
}

void OakMemberDestructureConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 2 ];
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		ElementData * DestructureData = new ElementData ();
		
		DestructureData -> Type = kDestructureType_Named;
		DestructureData -> MemberName = Input.Tokens [ 0 ] -> GetSource ();
		DestructureData -> BindingName = CurrentToken -> GetSource ();
		
		ASTElement * DestructureElement = new ASTElement ();
		
		DestructureElement -> SetTag ( OakASTTags :: kASTTag_MemberDestructure );
		DestructureElement -> SetData ( DestructureData, & ElementDataDestructor );
		DestructureElement -> AddTokenSection ( & Input.Tokens [ 0 ], 3 );
		
		Output.Accepted = true;
		Output.ConstructedElement = DestructureElement;
		Output.TokensConsumed = 3;
		
		return;
		
	}
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ignore ) )
	{
		
		ElementData * DestructureData = new ElementData ();
		
		DestructureData -> Type = kDestructureType_Ignored;
		DestructureData -> MemberName = Input.Tokens [ 0 ] -> GetSource ();
		
		ASTElement * DestructureElement = new ASTElement ();
		
		DestructureElement -> SetTag ( OakASTTags :: kASTTag_MemberDestructure );
		DestructureElement -> SetData ( DestructureData, & ElementDataDestructor );
		DestructureElement -> AddTokenSection ( & Input.Tokens [ 0 ], 3 );
		
		Output.Accepted = true;
		Output.ConstructedElement = DestructureElement;
		Output.TokensConsumed = 3;
		
		return;
		
	}
	
	ElementData * DestructureData = new ElementData ();
	
	DestructureData -> Type = kDestrucutreType_SubDestructure;
	DestructureData -> MemberName = Input.Tokens [ 0 ] -> GetSource ();
	
	ASTElement * DestructureElement = new ASTElement ();
	
	DestructureElement -> SetTag ( OakASTTags :: kASTTag_MemberDestructure );
	DestructureElement -> SetData ( DestructureData, & ElementDataDestructor );
	DestructureElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( DestructureGroup.TryConstruction ( DestructureElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete DestructureElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected output name or complex destructure after member destructure";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
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
	
	Output.Accepted = true;
	Output.ConstructedElement = DestructureElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}


void OakMemberDestructureConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
