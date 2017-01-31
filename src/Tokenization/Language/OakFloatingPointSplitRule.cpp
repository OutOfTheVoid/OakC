#include <Tokenization/Language/OakFloatingPointSplitRule.h>

#include <StringUtils/CharTestSet.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakFloatingPointSplitRule :: OakFloatingPointSplitRule ()
{
}

OakFloatingPointSplitRule :: ~OakFloatingPointSplitRule ()
{
}

void OakFloatingPointSplitRule :: TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result )
{
	
	if ( Source.size () <= ( Offset + 2 ) )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	uint64_t Length = 0;
	
	char32_t Char = Source.at ( Offset + Length );
	
	//[NON_ZERO_DIGIT] | [[0] ([!x])]??
	if ( CharTestSet :: NonZeroDigits.Contains ( Char ) || ( ( Char == U'0' ) && ( Source.at ( Offset + 1 ) != U'x' ) ) )
	{
		
		Length ++;
		
		//[NON_ZERO_DIGIT] [DIGIT]??
		while ( ( Offset + Length ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length );
			
			if ( ! CharTestSet :: DigitsUnderscore.Contains ( Char ) )
			{
				
				// [NON_ZERO_DIGIT] [DIGIT]* [PERIOD]
				if ( Char == U'.' )
				{
					
					
					
					Length ++;
					
					if ( ( Offset + Length ) >= Source.size () )
					{
						
						Result.Accepted = false;
						Result.PossibleError = true;
						Result.SuggestedError = "Expected end of numeric constant";
						
						return;
						
					}
					
					Char = Source.at ( Offset + Length );
					
					if ( ! CharTestSet :: Digits.Contains ( Char ) )
					{
						
						Result.Accepted = false;
						
						return;
						
					}
					
					Length ++;
					
					while ( ( Offset + Length ) < Source.size () )
					{
						
						Char = Source.at ( Offset + Length );
						
						// [NON_ZERO_DIGIT] [DIGIT]* [PERIOD] [NON_ZERO_DIGIT] [DIGIT]??
						if ( ! CharTestSet :: DigitsUnderscore.Contains ( Char ) )
						{
							
							// [NON_ZERO_DIGIT] [DIGIT]* [PERIOD] [NON_ZERO_DIGIT] [DIGIT]* [e]??
							if ( TestExponent ( Source, Offset, Length, Result ) )
								return;
							
							// [NON_ZERO_DIGIT] [DIGIT]* [PERIOD] [NON_ZERO_DIGIT] [DIGIT]* [f]??
							if ( TestFloatTypeSpecifier ( Source, Offset, Length, Result ) )
								return;
							
							Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
							Result.SplitLength = Length + 1;
							Result.Accepted = true;
							
							return;
							
						}
						
						Length ++;
						
					}
					
				}
				else if ( TestExponent ( Source, Offset, Length, Result ) )
					return;
				else if ( TestFloatTypeSpecifier ( Source, Offset, Length, Result ) )
					return;
				else
				{
					
					Result.Accepted = false;
					
					return;
					
				}
				
			}
			
			Length ++;
			
		}
		
	}
	else if ( Char == U'.' )
	{
		
		Length ++;
		Char = Source.at ( Offset + Length );
		
		if ( ! CharTestSet :: Digits.Contains ( Char ) )
		{
			
			Result.Accepted = false;
			
			return;
			
		}
		
		Length ++;
		
		// [.] [DIGIT]+ ??
		while ( ( Offset + Length ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length );
			
			if ( ! CharTestSet :: DigitsUnderscore.Contains ( Char ) )
			{
				
				// [.] [DIGIT]+ [e [+|-]? [NON_ZERO_DIGIT] [DIGIT]* [f [32|64]? ]?]??
				if ( TestExponent ( Source, Offset, Length, Result ) )
					return;
				
				// [.] [DIGIT]+ [f [32|64]?]??
				if ( TestFloatTypeSpecifier ( Source, Offset, Length, Result ) )
					return;
					
				Result.Accepted = true;
				Result.SplitLength = Length;
				Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
				
				return;
				
			}
			
			Length ++;
			
		}
		
		Result.Accepted = true;
		Result.SplitLength = Length;
		Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
		
	}
	else if ( Char == U'0' ) // 2nd Char = U'x'
	{
		
		Result.AuxTag = OakTokenTags :: kTokenAuxTax_FloatLiteral_HexFloat;
		
		Length += 2;
		
		if ( ( Offset + Length ) >= Source.size () )
		{
			
			Result.Accepted = false;
			
			return;
			
		}
		
		Char = Source.at ( Offset + Length );
		
		if ( ! CharTestSet :: HexDigits.Contains ( Char ) )
		{
			
			Result.Accepted = false;
			Result.PossibleError = true;
			Result.SuggestedError = "Expected value for exadecimal numeric literal";
			
			return;
			
		}
		
		Length ++;
		
		while ( ( Offset + Length ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length );
			
			if ( ! CharTestSet :: HexDigitsUnderscore.Contains ( Char ) )
			{
				
				if ( TestExponentHex ( Source, Offset, Length, Result ) )
					return;
				
			}
			
			Length ++;
			
		}
		
	}
	
	Result.Accepted = false;
	
}

bool OakFloatingPointSplitRule :: TestExponent ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result )
{
	
	if ( Offset + Length >= Source.size () )
		return false;
	
	char32_t Char = Source.at ( Offset + Length );
	
	// [e]??
	if ( Char == U'e' )
	{
		
		Length ++;
		
		Char = Source.at ( Offset + Length );
		
		// [e] [+|-]??
		if ( ( Char == U'-' ) || ( Char == U'+' ) )
		{
			
			Length ++;
			
			if ( Offset + Length >= Source.size () )
			{
				
				Result.Accepted = false;
				Result.PossibleError = true;
				Result.SuggestedError = "Expected exponent value after \"e\" in floating point literal";
				
				return true;
				
			}
			
			Char = Source.at ( Offset + Length );
			
		}
		
		// [e] [+|-]? [NON_ZERO_DIGIT]??
		if ( ! CharTestSet :: NonZeroDigits.Contains ( Char ) )
		{
			
			Result.Accepted = false;
			Result.PossibleError = true;
			Result.SuggestedError = "Expected exponent value after \"e\" in floating point literal";
			
			return true;
			
		}
		
		Length ++;
		
		// [e] [+|-]? [NON_ZERO_DIGIT] [DIGIT]??
		while ( ( Offset + Length ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length );
			
			if ( ! CharTestSet :: DigitsUnderscore.Contains ( Char ) )
			{
				
				// [e] [+|-]? [NON_ZERO_DIGIT] [DIGIT]* [f [32|64]?]??
				if ( TestFloatTypeSpecifier ( Source, Offset, Length, Result ) )
					return true;
				
				Result.Accepted = true;
				Result.SplitLength = Length;
				Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
				
				return true;
				
			}
			
			Length ++;
			
		}
		
		Result.Accepted = true;
		Result.SplitLength = Length - 1;
		Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
		
		return true;
		
	}
	
	return false;
	
}

bool OakFloatingPointSplitRule :: TestExponentHex ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result )
{
	
	if ( Offset + Length >= Source.size () )
		return false;
	
	char32_t Char = Source.at ( Offset + Length );
	
	// [e]??
	if ( Char == U'p' )
	{
		
		Length ++;
		
		Char = Source.at ( Offset + Length );
		
		// [p] [+|-]??
		if ( ( Char == U'-' ) || ( Char == U'+' ) )
		{
			
			Length ++;
			
			if ( Offset + Length >= Source.size () )
			{
				
				Result.Accepted = false;
				Result.PossibleError = true;
				Result.SuggestedError = "Expected exponent value after \"e\" in floating point literal";
				
				return true;
				
			}
			
			Char = Source.at ( Offset + Length );
			
		}
		
		// [p] [+|-]? [DIGIT]??
		if ( ! CharTestSet :: Digits.Contains ( Char ) )
		{
			
			Result.Accepted = false;
			Result.PossibleError = true;
			Result.SuggestedError = "Expected exponent value after \"e\" in floating point literal";
			
			return true;
			
		}
		
		Length ++;
		
		// [p] [+|-]? [NON_ZERO_DIGIT] [DIGIT]??
		while ( ( Offset + Length ) < Source.size () )
		{
			
			Char = Source.at ( Offset + Length );
			
			if ( ! CharTestSet :: DigitsUnderscore.Contains ( Char ) )
			{
				
				// [p] [+|-]? [NON_ZERO_DIGIT] [DIGIT]* [f [32|64]?]??
				if ( TestFloatTypeSpecifier ( Source, Offset, Length, Result ) )
					return true;
				
				Result.Accepted = true;
				Result.SplitLength = Length;
				Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
				
				return true;
				
			}
			
			Length ++;
			
		}
		
		Result.Accepted = true;
		Result.SplitLength = Length - 1;
		Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
		
		return true;
		
	}
	
	return false;
	
}

bool OakFloatingPointSplitRule :: TestFloatTypeSpecifier ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result )
{
	
	if ( Offset + Length >= Source.size () )
		return false;
	
	// [f]??
	if ( Source.at ( Offset + Length ) == U'f' )
	{
		
		if ( Offset + Length + 2 < Source.size () )
		{
			
			// [f] [32]??
			if ( ( Source.at ( Offset + Length + 1 ) == U'3' ) && ( Source.at ( Offset + Length + 2 ) == U'2' ) )
			{
				
				Result.Accepted = true;
				Result.SplitLength = Length + 3;
				Result.Tag = OakTokenTags :: kTokenTag_FloatLiteral32;
				
				return true;
				
			}
			// [f] [64]??
			else if ( ( Source.at ( Offset + Length + 1 ) == U'6' ) && ( Source.at ( Offset + Length + 2 ) == U'4' ) )
			{
				
				Result.Accepted = true;
				Result.SplitLength = Length + 3;
				Result.Tag = OakTokenTags :: kTokenTag_FloatLiteral64;
				
				return true;
				
			}
			
		}
		
		Result.Accepted = true;
		Result.SplitLength = Length + 1;
		Result.Tag = OakTokenTags :: kTokenTag_FloatLiteralDefaultSize;
		
		return true;
		
	}
	else
		return false;
	
}
