#include <Tokenization/Language/OakStringSplitRule.h>

#include <Tokenization/Language/OakTokenTags.h>

OakStringSplitRule :: OakStringSplitRule ()
{
}

OakStringSplitRule :: ~OakStringSplitRule ()
{
}

void OakStringSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Source.size () - Offset < 2 )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	if ( Source.at ( Offset ) != U'\"' )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	uint64_t StringLength = 1;
	
	while ( StringLength < Source.size () - Offset )
	{
		
		if ( ( Source.at ( Offset + StringLength ) == U'\"' ) && ( Source.at ( Offset + StringLength - 1 ) != U'\\' ) )
		{
			
			if ( StringLength + 3 < Source.size () - Offset )
			{
				
				if ( Source.at ( Offset + StringLength + 1 ) == U'u' )
				{
					
					if ( Source.at ( Offset + StringLength + 2 ) == U'8' )
					{
						
						Result.Tag = OakTokenTags :: kTokenTag_StringLiteralu8;
						Result.Accepted = true;
						Result.SplitLength = StringLength + 3;
						
						return;
						
					}
					else if ( StringLength + 4 < Source.size () - Offset )
					{
						
						if ( ( Source.at ( Offset + StringLength + 2 ) == U'1' ) && ( Source.at ( Offset + StringLength + 3 ) == U'6' ) )
						{
							
							Result.Tag = OakTokenTags :: kTokenTag_StringLiteralu16;
							Result.Accepted = true;
							Result.SplitLength = StringLength + 4;
							
							return;
							
						}
						else if ( ( Source.at ( Offset + StringLength + 2 ) == U'3' ) && ( Source.at ( Offset + StringLength + 3 ) == U'2' ) )
						{
							
							Result.Tag = OakTokenTags :: kTokenTag_StringLiteralu32;
							Result.Accepted = true;
							Result.SplitLength = StringLength + 4;
							
							return;
							
						}
						else
						{
							
							Result.Accepted = false;
							Result.PossibleError = true;
							Result.SuggestedError = "Invalid string suffix";
							
							return;
							
						}
						
					}
					else
					{
						
						Result.Accepted = false;
						Result.PossibleError = true;
						Result.SuggestedError = "Invalid string suffix";
						
						return;
						
					}
					
				}
				
			}
			
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_StringLiteralDefault;
			Result.SplitLength = StringLength + 1;
			
			return;
			
		}
		
		StringLength ++;
		
	}
	
	Result.Accepted = false;
	Result.PossibleError = true;
	Result.SuggestedError = "Unclosed string literal";
	
}
