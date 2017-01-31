#include <Tokenization/Language/OakMultilineCommentSplitRule.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakMultilineCommentSplitRule :: OakMultilineCommentSplitRule ()
{
}

OakMultilineCommentSplitRule :: ~OakMultilineCommentSplitRule ()
{
}

void OakMultilineCommentSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( ( Source.size () - Offset ) < 4 )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	if ( ( Source.at ( Offset ) != U'/' ) || ( Source.at ( Offset + 1 ) != U'*' ) )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	uint64_t CommentLength = 2;
	
	while ( ( CommentLength + 1 ) < ( Source.size () - Offset ) )
	{
		
		if ( ( Source.at ( Offset + CommentLength ) == U'*' ) && ( Source.at ( Offset + CommentLength + 1 ) == U'/' ) )
		{
			
			Result.SplitLength = CommentLength + 2;
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_Comment;
			
			return;
			
		}
		
		CommentLength ++;
		
	}
	
	Result.Accepted = false;
	Result.PossibleError = true;
	Result.SuggestedError = "Expected end of multiline comment.";
	
}
