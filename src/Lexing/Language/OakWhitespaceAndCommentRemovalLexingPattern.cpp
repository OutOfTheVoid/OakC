#include <Lexing/Language/OakWhitespaceAndCommentRemovalLexingPattern.h>

#include <Tokenization/Language/OakTokenTags.h>

OakWhitespaceAndCommentRemovalLexingPattern :: OakWhitespaceAndCommentRemovalLexingPattern ()
{
}

OakWhitespaceAndCommentRemovalLexingPattern :: ~OakWhitespaceAndCommentRemovalLexingPattern ()
{
}

void OakWhitespaceAndCommentRemovalLexingPattern :: TryPattern ( ILexingInput & Input, ILexingResult & Result )
{
	
	if ( Input.AvailableTokens == 0 )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	const Token * Current = Input.Tokens [ 0 ];
	
	if ( ( Current -> GetTag () != OakTokenTags :: kTokenTag_Comment ) && ( Current -> GetTag () != OakTokenTags :: kTokenTag_Whitespace ) )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	Result.Accepted = true;
	Result.TokensConsumed = 1;
	
}
