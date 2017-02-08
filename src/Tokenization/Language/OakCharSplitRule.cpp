#include <Tokenization/Language/OakCharSplitRule.h>

#include <Tokenization/Language/OakTokenTags.h>

OakCharSplitRule :: OakCharSplitRule ()
{
}

OakCharSplitRule :: ~OakCharSplitRule ()
{
}

void OakCharSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Source.size () - Offset < 3 )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	if ( Source.at ( Offset ) != U'\'' )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	uint64_t StringLength = 1;
	
	char32_t Current = Source.at ( StringLength + Offset );
	StringLength ++;
	
	if ( Current == U'\'' )
	{
		
		Result.Accepted = false;
		Result.PossibleError = true;
		Result.SuggestedError = "Expected charachter or value before \"\'\" at end of charachter literal";
		
		return;
		
	}
	
	if ( Current == U'\\' )
	{
		
		Current = Source.at ( StringLength + Offset );
		StringLength ++;
		
		switch ( Current )
		{
			
			case U'u':
			{
				
				if ( StringLength + 5 >= Source.size () - Offset )
				{
					
					Result.Accepted = false;
					Result.PossibleError = true;
					Result.SuggestedError = "Invalid end of charachter literal";
					
					return;
					
				}
				
				for ( uint32_t I = 0; I < 4; I ++ )
				{
					
					Current = Source.at ( StringLength + Offset );
					StringLength ++;
					
					switch ( Current )
					{
						
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case 'a':
						case 'b':
						case 'c':
						case 'd':
						case 'e':
						case 'f':
						case 'A':
						case 'B':
						case 'C':
						case 'D':
						case 'E':
						case 'F':
						break;
						
						default:
						{
							
							Result.Accepted = false;
							Result.PossibleError = true;
							Result.SuggestedError = "Invalid hex digit in unicode charachter literal";
							
							return;
							
						}
						
					}
					
				}
				
				Current = Source.at ( StringLength + Offset );
				StringLength ++;
				
				if ( Current != U'\'' )
				{
					
					Result.Accepted = false;
					Result.PossibleError = true;
					Result.SuggestedError = "Invalid end of charachter literal";
					
					return;
					
				}
				
				Result.Accepted = true;
				Result.Tag = OakTokenTags :: kTokenTag_CharLiteral;
				Result.SplitLength = StringLength;
				
				return;
				
			}
			break;
			
			case U'U':
			{
				
				if ( StringLength + 9 >= Source.size () - Offset )
				{
					
					Result.Accepted = false;
					Result.PossibleError = true;
					Result.SuggestedError = "Invalid end of charachter literal";
					
					return;
					
				}
				
				for ( uint32_t I = 0; I < 8; I ++ )
				{
					
					Current = Source.at ( StringLength + Offset );
					StringLength ++;
					
					switch ( Current )
					{
						
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case 'a':
						case 'b':
						case 'c':
						case 'd':
						case 'e':
						case 'f':
						case 'A':
						case 'B':
						case 'C':
						case 'D':
						case 'E':
						case 'F':
						break;
						
						default:
						{
							
							Result.Accepted = false;
							Result.PossibleError = true;
							Result.SuggestedError = "Invalid hex digit in unicode charachter literal";
							
							return;
							
						}
						
					}
					
				}
				
				Current = Source.at ( StringLength + Offset );
				StringLength ++;
				
				if ( Current != U'\'' )
				{
					
					Result.Accepted = false;
					Result.PossibleError = true;
					Result.SuggestedError = "Invalid end of charachter literal";
					
					return;
					
				}
				
				Result.Accepted = true;
				Result.Tag = OakTokenTags :: kTokenTag_CharLiteral;
				Result.SplitLength = StringLength;
				
				return;
				
			}
			break;
			
			case U'x':
			{
				
				while ( StringLength < Source.size () - Offset )
				{
					
					Current = Source.at ( StringLength + Offset );
					StringLength ++;
					
					switch ( Current )
					{
						
						case '0':
						case '1':
						case '2':
						case '3':
						case '4':
						case '5':
						case '6':
						case '7':
						case '8':
						case '9':
						case 'a':
						case 'b':
						case 'c':
						case 'd':
						case 'e':
						case 'f':
						case 'A':
						case 'B':
						case 'C':
						case 'D':
						case 'E':
						case 'F':
						break;
						
						case '\'':
						{
							
							Result.Accepted = true;
							Result.Tag = OakTokenTags :: kTokenTag_CharLiteral;
							Result.SplitLength = StringLength;
							
							return;
							
						}
						
					}
					
				}
				
				Result.Accepted = false;
				Result.PossibleError = true;
				Result.SuggestedError = "Invalid end of charachter literal";
				
				return;
				
			}
			break;
			
			case U'n':
			case U't':
			case U'v':
			case U'b':
			case U'r':
			case U'f':
			case U'a':
			case U'0':
			case U'\\':
			case U'\'':
			case U'\"':
			{
				
				if ( StringLength + 1 >= Source.size () - Offset )
				{
					
					Result.Accepted = false;
					Result.PossibleError = true;
					Result.SuggestedError = "Invalid end of charachter literal";
					
					return;
					
				}
				
				Current = Source.at ( StringLength + Offset );
				StringLength ++;
				
				if ( Current != '\'' )
				{
					
					Result.Accepted = false;
					Result.PossibleError = true;
					Result.SuggestedError = "Invalid end of charachter literal";
					
					return;
					
				}
				
				Result.Accepted = true;
				Result.Tag = OakTokenTags :: kTokenTag_CharLiteral;
				Result.SplitLength = StringLength;
				
				return;
				
			}
			
			default:
			{
				
				Result.Accepted = false;
				Result.PossibleError = true;
				Result.SuggestedError = "Invalid escape code in charachter literal";
				
				return;
				
			}
			break;
			
		}
		
	}
	
	Current = Source.at ( StringLength + Offset );
	StringLength ++;
	
	if ( Current != U'\'' )
	{
			
		Result.Accepted = false;
		Result.PossibleError = true;
		Result.SuggestedError = "Invalid end of charachter literal";
		
		return;
		
	}
	
	Result.Accepted = true;
	Result.Tag = OakTokenTags :: kTokenTag_CharLiteral;
	Result.SplitLength = StringLength;
	
}
	
