#include <Parsing/Language/OakIgnoreStatementConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakIgnoreStatementConstructor OakIgnoreStatementConstructor :: Instance;

OakIgnoreStatementConstructor :: OakIgnoreStatementConstructor ()
{
}

OakIgnoreStatementConstructor :: ~OakIgnoreStatementConstructor ()
{
}

void OakIgnoreStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ignore ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier in ignore statement after ignore keyword";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 2 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon after end of ignore statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ElementData * IgnoreData = new ElementData ();
	
	IgnoreData -> IgnoredName = CurrentToken -> GetSource ();
	
	ASTElement * IgnoreElement = new ASTElement ();
	
	IgnoreElement -> SetTag ( OakASTTags :: kASTTag_IgnoreStatement );
	IgnoreElement -> AddTokenSection ( & Input.Tokens [ 0 ], 3 );
	IgnoreElement -> SetData ( IgnoreData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.ConstructedElement = IgnoreElement;
	Output.TokensConsumed = 3;
	
}

void OakIgnoreStatementConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
