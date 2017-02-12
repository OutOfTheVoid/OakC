#include <Tokenization/Tokenizer.h>

#include <Logging/Logging.h>

Tokenizer :: Tokenizer ():
	Rules ()
{
}

Tokenizer :: ~Tokenizer ()
{
	
	for ( uint32_t Precedence = 0; Precedence < Rules.size (); Precedence ++ )
	{
		
		for ( uint32_t I = 0; I < Rules [ Precedence ].size (); I ++ )
		{
			
			delete Rules [ Precedence ][ I ];
			Rules [ Precedence ][ I ] = NULL;
			
		}
		
	}
	
}
	
void Tokenizer :: AddSplitRule ( ITokenSplitRule * Rule, uint32_t Precedence )
{
	
	while ( Rules.size () < Precedence + 1 )
		Rules.push_back ( std :: vector <ITokenSplitRule *> () );
	
	Rules [ Precedence ].push_back ( Rule );
	
}

bool Tokenizer :: TokenizeString ( const std :: u32string & Source, std :: vector <const Token *> & TokenList, const std :: string & ErrorFileName ) const
{
	
	uint64_t Offset = 0;
	
	uint64_t Line = 0;
	uint64_t Char = 0;
	
	uint64_t LastLineOffset = 0;
	
	while ( Offset < Source.size () )
	{
		
		bool PossibleError = false;
		std :: string SuggestedError = "";
		
		bool Found = false;
		
		for ( uint32_t Precedence = 0; Precedence < Rules.size (); Precedence ++ )
		{
			
			for ( uint32_t I = 0; I < Rules [ Precedence ].size (); I ++ )
			{
				
				ITokenSplitRule :: TokenSplitResult SplitResult;
				SplitResult.Tag = ITokenSplitRule :: kTag_Default;
				SplitResult.AuxTag = ITokenSplitRule :: kAuxTag_Default;
				SplitResult.PossibleError = false;
				SplitResult.SuggestedError = "";
				
				Rules [ Precedence ][ I ] -> TrySplit ( Source, Offset, SplitResult );
				
				if ( SplitResult.Accepted )
				{
					
					Found = true;
					
					TokenList.push_back ( new Token ( Source.substr ( Offset, SplitResult.SplitLength ), Char + 1, Line + 1, SplitResult.Tag, SplitResult.AuxTag ) );
					
					uint64_t NewOffset = Offset + SplitResult.SplitLength;
					
					if ( NewOffset >= Source.size () )
					{
						
						Offset = Source.size ();
						Precedence = Rules.size ();
						
						break;
						
					}
					
					while ( Offset < NewOffset )
					{
						
						if ( Source.at ( Offset ) == '\n' )
						{
							
							Line ++;
							LastLineOffset = Offset + 1;
							
						}
						
						Offset ++;
						
					}
					
					Char = Offset - LastLineOffset;
					
					break;
					
				}
				else if ( SplitResult.PossibleError && ! PossibleError )
				{
					
					PossibleError = true;
					SuggestedError = SplitResult.SuggestedError;
					
				}
				
			}
			
			if ( Found )
				break;
			
		}
		
		if ( ! Found )
		{
			
			if ( PossibleError )
			{
			 		
				LOG_ERROR_NOFILE ( ErrorFileName + ", " + std :: to_string ( Line + 1 ) + ": " + SuggestedError );
				
				return false;
				
			}
			else
			{
				
				LOG_ERROR_NOFILE ( ErrorFileName + ", " + std :: to_string ( Line + 1 ) + ": Unkown parsing error" );
				
				return false;
				
			}
			
		}
		
	}
	
	return true;
	
}
