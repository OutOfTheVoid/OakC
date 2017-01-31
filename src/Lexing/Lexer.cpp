#include <Lexing/Lexer.h>

#include <Tokenization/Language/OakTokenTags.h>

Lexer :: Lexer ():
	Patterns ()
{	
}

Lexer :: ~Lexer ()
{
	
	for ( uint32_t I = 0; I < Patterns.size (); I ++ )
		delete Patterns [ I ];
	
	Patterns.clear ();
	
}

void Lexer :: AddPattern ( ILexingPattern * Pattern )
{
	
	Patterns.push_back ( Pattern );
	
}
	
bool Lexer :: LexTokens ( std :: vector <const Token *> & TokensIn, std :: vector <const Token *> & TokensOut ) const
{
	
	ILexingPattern :: ILexingInput LexingInput;
	
	uint64_t TokensInIndex = 0;
	
	LexingInput.AvailableTokens = TokensIn.size () - TokensInIndex;
	LexingInput.Tokens = & TokensIn [ 0 ];
	
	while ( TokensInIndex < TokensIn.size () )
	{
		
		bool Found = false;
		
		for ( uint32_t I = 0; I < Patterns.size (); I ++ )
		{
			
			ILexingPattern :: ILexingResult Result ( TokensOut );
			
			Result.Accepted = false;
			Result.TokensConsumed = 0;
			Result.PossibleError = false;
			Result.SuggestedError = std :: string ();
			
			Patterns [ I ] -> TryPattern ( LexingInput, Result );
			
			if ( Result.Accepted )
			{
				
				Found = true;
				TokensInIndex += Result.TokensConsumed;
				
				if ( TokensInIndex >= TokensIn.size () )
					return true;
				
				LexingInput.Tokens = & TokensIn [ TokensInIndex ];
				LexingInput.AvailableTokens = TokensIn.size () - TokensInIndex;
				
				break;
				
			}
			
		}
		
		if ( ! Found )
		{
			
			// TODO: Decide whether to pass unmatched tokens or require a pattern for everything
			// Validation in the Lexer means a more consistent gaurentee for the patterns, but assuming
			// They're properly designed, it shouldn't be needed. It would make lexing easier.
			
			// For now, just pass un-matched tokens through.
			
			TokensOut.push_back ( new Token ( * TokensIn [ TokensInIndex ] ) );
			
			TokensInIndex ++;
				
			if ( TokensInIndex >= TokensIn.size () )
				return true;
			
			LexingInput.Tokens = & TokensIn [ TokensInIndex ];
			LexingInput.AvailableTokens = TokensIn.size () - TokensInIndex;
			
		}
		
	}
	
	return false;
	
}
