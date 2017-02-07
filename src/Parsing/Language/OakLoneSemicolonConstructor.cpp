#include <Parsing/Language/OakLoneSemicolonConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

#ifndef NULL
	#define NULL nullptr
#endif

OakLoneSemicolonConstructor :: OakLoneSemicolonConstructor ()
{
}

OakLoneSemicolonConstructor :: ~OakLoneSemicolonConstructor ()
{
}

void OakLoneSemicolonConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.ConstructedElement = NULL;
	Output.TokensConsumed = 1;
	
}
