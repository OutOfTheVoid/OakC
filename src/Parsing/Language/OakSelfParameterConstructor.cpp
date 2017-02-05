#include <Parsing/Language/OakSelfParameterConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

OakSelfParameterConstructor :: OakSelfParameterConstructor ()
{
}

OakSelfParameterConstructor :: ~OakSelfParameterConstructor ()
{
}

void OakSelfParameterConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 1 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Self ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * SelfElement = new ASTElement ();
	
	SelfElement -> SetTag ( OakASTTags :: kASTTag_SelfParameter );
	SelfElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	Output.Accepted = true;
	Output.TokensConsumed = 1;
	Output.ConstructedElement = SelfElement;
	
}