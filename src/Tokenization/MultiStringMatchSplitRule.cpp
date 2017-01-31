#include <Tokenization/MultiStringMatchSplitRule.h>

MultiStringMatchSplitRule :: MultiStringMatchSplitRule ( const char32_t * Strings [], uint32_t StringCount, uint64_t Tag ):
	Strings ( new std :: u32string [ StringCount ] ),
	StringCount ( StringCount ),
	Tag ( Tag )
{
	
	for ( uint32_t I = 0; I < StringCount; I ++ )
		this -> Strings [ I ] = Strings [ I ];
	
}

MultiStringMatchSplitRule :: ~MultiStringMatchSplitRule ()
{
	
	delete [] Strings;
	
}

void MultiStringMatchSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	for ( uint32_t I = 0; I < StringCount; I ++ )
	{
		
		bool Match = true;
		
		if ( Offset + Strings [ I ].size () < Source.size () )
		{
			
			for ( uint64_t J = 0; J < Strings [ I ].size (); J ++ )
			{
				
				if ( Source [ Offset + J ] != Strings [ I ][ J ] )
				{
					
					Match = false;
					
					break;
					
				}
				
			}
			
		}
		
		if ( Match )
		{
			
			Result.Accepted = true;
			Result.SplitLength = Strings [ I ].size ();
			Result.Tag = Tag;
			
			return;
			
		}
		
	}
	
	Result.Accepted = false;
	
}
