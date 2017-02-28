#include <Tokenization/Language/OakIntegerSplitRule.h>

#include <StringUtils/CharTestSet.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakIntegerSplitRule :: OakIntegerSplitRule ()
{
}

OakIntegerSplitRule :: ~OakIntegerSplitRule ()
{
}

void OakIntegerSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Offset >= Source.size () )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	uint64_t Length = 0;
	
	char32_t Char = Source.at ( Offset + Length );
	
	if ( CharTestSet :: NonZeroDigits.Contains ( Char ) )
	{
		
		Length ++;
		
		while ( ( Offset + Length ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length );
			
			if ( ! CharTestSet :: DigitsUnderscore.Contains ( Char ) )
			{
				
				if ( TestTypeSpecifier ( Source, Offset, Length, Result ) )
					return;
				
				Result.Accepted = true;
				Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
				Result.SplitLength = Length;
				
				return;
				
			}
			
			Length ++;
			
		}
		
	}
	else if ( Char == U'0' )
	{
		
		Length ++;
		
		if ( ( Offset + Length ) >= Source.size () )
		{
			
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
			Result.SplitLength = 1;
			
			return;
			
		}
		
		Char = Source.at ( Offset + Length );
		
		if ( CharTestSet :: DigitsUnderscore.Contains ( Char ) )
		{
			
			Length ++;
			
			while ( ( Offset + Length ) < Source.size () )
			{
				
				Char = Source.at ( Offset + Length );
				
				if ( ! CharTestSet :: DigitsUnderscore.Contains ( Char ) )
				{
					
					if ( TestTypeSpecifier ( Source, Offset, Length, Result ) )
						return;
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
					Result.SplitLength = Length;
					
					return;
					
				}
				
				Length ++;
				
			}
			
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
			Result.SplitLength = Length - 1;
			
			return;
			
		}
		else if ( ( Char == U'X' ) || ( Char == U'x' ) || ( Char == U'H' ) || ( Char == U'h' ) )
		{
			Length ++;
			
			while ( ( Offset + Length ) < Source.size () )
			{
				
				Char = Source.at ( Offset + Length );
				
				if ( ! CharTestSet :: HexDigitsUnderscore.Contains ( Char ) )
				{
					
					if ( TestTypeSpecifier ( Source, Offset, Length, Result ) )
						return;
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
					Result.SplitLength = Length;
					
					return;
					
				}
				
				Length ++;
				
			}
			
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
			Result.SplitLength = Length - 1;
			
			return;
			
		}
		else if ( ( Char == U'b' ) || ( Char == U'B' ) )
		{
			
			Length ++;
			
			while ( ( Offset + Length ) < Source.size () )
			{
				
				Char = Source.at ( Offset + Length );
				
				if ( ! CharTestSet :: BinaryDigitsUnderscore.Contains ( Char ) )
				{
					
					if ( TestTypeSpecifier ( Source, Offset, Length, Result ) )
						return;
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
					Result.SplitLength = Length;
					
					return;
					
				}
				
				Length ++;
				
			}
			
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
			Result.SplitLength = Length - 1;
			
			return;
			
		}
		else if ( ( Char == U'o' ) || ( Char == U'O' ) )
		{
			
			Length ++;
			
			while ( ( Offset + Length ) < Source.size () )
			{
				
				Char = Source.at ( Offset + Length );
				
				if ( ! CharTestSet :: OctalDigitsUnderscore.Contains ( Char ) )
				{
					
					if ( TestTypeSpecifier ( Source, Offset, Length, Result ) )
						return;
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
					Result.SplitLength = Length;
					
					return;
					
				}
				
				Length ++;
				
			}
			
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
			Result.SplitLength = Length - 1;
			
			return;
			
		}
		else
		{
			
			Result.Accepted = true;
			Result.Tag = OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral;
			Result.SplitLength = 1;
			
			return;
			
		}
		
	}
	
	Result.Accepted = false;
	
}

bool OakIntegerSplitRule :: TestTypeSpecifier ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result )
{
	
	if ( ( Offset + Length ) >= Source.size () )
		return false;
	
	char32_t Char = Source.at ( Offset + Length );
	
	if ( Char == U'u' )
	{
		
		if ( ( Offset + Length + 1 ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length + 1 );
			
			if ( Char == U'8' )
			{
				
				Result.Accepted = true;
				Result.Tag = OakTokenTags :: kTokenTag_UnsignedIntegerLiteral8;
				Result.SplitLength = Length + 2;
				
				return true;
				
			}
			
			if ( ( Offset + Length + 2 ) < Source.size () )
			{
				
				char32_t Char2 = Source.at ( Offset + Length + 2 );
				
				if ( ( Char == U'1' ) && ( Char2 == U'6' ) )
				{
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_UnsignedIntegerLiteral16;
					Result.SplitLength = Length + 3;
					
					return true;
					
				}
				else if ( ( Char == U'3' ) && ( Char2 == U'2' ) )
				{
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_UnsignedIntegerLiteral32;
					Result.SplitLength = Length + 3;
					
					return true;
					
				}
				else if ( ( Char == U'6' ) && ( Char2 == U'4' ) )
				{
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_UnsignedIntegerLiteral64;
					Result.SplitLength = Length + 3;
					
					return true;
					
				}
				
			}
			
		}
		
		Result.Accepted = true;
		Result.Tag = OakTokenTags :: kTokenTag_UnsignedIntegerLiteralDefault;
		Result.SplitLength = Length + 1;
		
		return true;
		
	}
	
	if ( Char == U'i' )
	{
		
		if ( ( Offset + Length + 1 ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length + 1 );
			
			if ( Char == U'8' )
			{
				
				Result.Accepted = true;
				Result.Tag = OakTokenTags :: kTokenTag_SignedIntegerLiteral8;
				Result.SplitLength = Length + 2;
				
				return true;
				
			}
			
			if ( ( Offset + Length + 2 ) < Source.size () )
			{
				
				char32_t Char2 = Source.at ( Offset + Length + 2 );
				
				if ( ( Char == U'1' ) && ( Char2 == U'6' ) )
				{
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_SignedIntegerLiteral16;
					Result.SplitLength = Length + 3;
					
					return true;
					
				}
				else if ( ( Char == U'3' ) && ( Char2 == U'2' ) )
				{
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_SignedIntegerLiteral32;
					Result.SplitLength = Length + 3;
					
					return true;
					
				}
				else if ( ( Char == U'6' ) && ( Char2 == U'4' ) )
				{
					
					Result.Accepted = true;
					Result.Tag = OakTokenTags :: kTokenTag_SignedIntegerLiteral64;
					Result.SplitLength = Length + 3;
					
					return true;
					
				}
				
			}
			
		}
		
		Result.Accepted = true;
		Result.Tag = OakTokenTags :: kTokenTag_SignedIntegerLiteralDefault;
		Result.SplitLength = Length + 1;
		
		return true;
		
	}
	
	return false;
	
}
