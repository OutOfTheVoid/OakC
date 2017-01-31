#include <Tokenization/CharMatchRunSplitRule.h>

#include <Logging/Logging.h>

CharMatchRunSplitRule :: CharMatchRunSplitRule ( const char32_t CharList [], uint32_t CharCount, bool FreeOnDestruct, uint64_t Tag ):
	CharList ( CharList, CharCount, FreeOnDestruct ),
	Tag ( Tag )
{
}

CharMatchRunSplitRule :: ~CharMatchRunSplitRule ()
{
}

void CharMatchRunSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( ! CharList.Contains ( Source.at ( Offset ) ) )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	Result.Accepted = true;
	Result.Tag = Tag;
	
	uint64_t Length = 1;
	
	while ( Offset + Length < Source.size () )
	{
		
		if ( ! CharList.Contains ( Source.at ( Offset + Length ) ) )
			break;
		
		Length ++;
			
	}
	
	Result.SplitLength = Length;
	
}