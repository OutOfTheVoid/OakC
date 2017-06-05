#include <Parsing/Language/OakMemberAccessNameConstructor.h>

#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

OakMemberAccessNameConstructor OakMemberAccessNameConstructor :: Instance;

OakMemberAccessNameConstructor :: OakMemberAccessNameConstructor ()
{
}

OakMemberAccessNameConstructor :: ~OakMemberAccessNameConstructor ()
{
}

void OakMemberAccessNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 1 )
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
	
	ASTElement * NameElement = new ASTElement ();
	
	NameElement -> SetTag ( OakASTTags :: kASTTag_MemberAccessName );
	NameElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	Output.Accepted = true;
	Output.TokensConsumed = 1;
	Output.ConstructedElement = NameElement;
	
}
