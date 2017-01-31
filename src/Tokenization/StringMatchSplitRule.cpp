#include <Tokenization/StringMatchSplitRule.h>

StringMatchSplitRule :: StringMatchSplitRule ( const std :: u32string & String, uint64_t Tag ):
	String ( String ),
	Tag ( Tag )
{
}

StringMatchSplitRule :: ~StringMatchSplitRule ()
{
}

void StringMatchSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Offset + String.size () > Source.size () )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	for ( uint64_t I = 0; I < String.size (); I ++ )
	{
		
		if ( Source [ Offset + I ] != String [ I ] )
		{
			
			Result.Accepted = false;
			
			return;
			
		}
		
	}
	
	Result.Accepted = true;
	Result.SplitLength = String.size ();
	Result.Tag = Tag;
	
}
