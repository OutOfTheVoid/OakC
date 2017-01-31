#include <Tokenization/Language/OakSingleLineCommentSplitRule.h>

#include <Tokenization/Language/OakTokenTags.h>

OakSingleLineCommentSplitRule :: OakSingleLineCommentSplitRule ()
{
}

OakSingleLineCommentSplitRule :: ~OakSingleLineCommentSplitRule ()
{
}

void OakSingleLineCommentSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Source.size () - Offset < 3 )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	if ( ( Source.at ( Offset ) != U'/' ) || ( Source.at ( Offset + 1 ) != U'/' ) )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	Result.Accepted = true;
	Result.Tag = OakTokenTags :: kTokenTag_Comment;
	
	uint64_t CommentLength = 2;
	
	while ( CommentLength < ( Source.size () - Offset ) )
	{
		
		if ( Source.at ( Offset + CommentLength ) == '\n' )
		{
			
			Result.SplitLength = CommentLength + 1;
			
			return;
			
		}
		
		CommentLength ++;
		
	}
	
	Result.SplitLength = Source.size () - Offset;
	
}
	
