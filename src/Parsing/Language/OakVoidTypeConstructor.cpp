#include <Parsing/Language/OakVoidTypeConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakVoidTypeConstructor & OakVoidTypeConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakVoidTypeConstructor> ();
	
}

OakVoidTypeConstructor :: OakVoidTypeConstructor ()
{
}

OakVoidTypeConstructor :: ~OakVoidTypeConstructor ()
{
}

void OakVoidTypeConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Void ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * VoidElement = new ASTElement ();
	
	VoidElement -> SetTag ( OakASTTags :: kASTTag_VoidType );
	VoidElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	Output.Accepted = true;
	Output.TokensConsumed = 1;
	Output.ConstructedElement = VoidElement;
	
}
