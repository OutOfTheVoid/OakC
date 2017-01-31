#include <Tokenization/CharMatchSplitRule.h>


CharMatchSplitRule :: CharMatchSplitRule ( char32_t MatchChar, uint64_t Tag ):
	MatchChar ( MatchChar ),
	Tag ( Tag )
{
}

CharMatchSplitRule :: ~CharMatchSplitRule ()
{
}

void CharMatchSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Offset >= Source.size () )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	if ( Source.at ( Offset ) == MatchChar )
	{
		
		Result.Accepted = true;
		Result.Tag = Tag;
		Result.SplitLength = 1;
		
		return;
		
	}
	
	Result.Accepted = false;
	
}
