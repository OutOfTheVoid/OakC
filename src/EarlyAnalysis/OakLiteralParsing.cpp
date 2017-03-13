#include <EarlyAnalysis/OakLiteralParsing.h>
#include <Math/BigInteger.h>
#include <Math/BigFloat.h>

#include <Logging/Logging.h>

uint32_t HexCodeToValue ( char32_t Code )
{
	
	if ( ( Code >= U'0' ) && ( Code <= U'9' ) )
		return static_cast <uint32_t> ( Code ) - static_cast <uint32_t> ( U'0' );
	
	if ( ( Code >= U'A' ) && ( Code <= U'F' ) )
		return 10 + static_cast <uint32_t> ( Code ) - static_cast <uint32_t> ( U'A' );
	
	if ( ( Code >= U'a' ) && ( Code <= U'f' ) )
		return 10 + static_cast <uint32_t> ( Code ) - static_cast <uint32_t> ( U'a' );
	
	return 0xFFFFFFFF;
	
}

bool OakParseStringLiteral ( const std :: u32string & Source, std :: u32string & Out, std :: string & Error )
{
	
	if ( Source.size () == 0 )
		return false;
	
	Out.clear ();
	
	uint64_t Index = 1;
	
	while ( Index < Source.size () )
	{
		
		char32_t Char = Source.at ( Index );
		
		switch ( Char )
		{
			
			case U'\\':
			{
				
				if ( Index + 2 >= Source.size () )
				{
					
					Error = "Expected escape code after slash in string literal";
					
					return false;
					
				}
				
				Index ++;
				
				char32_t EscapeChar = Source.at ( Index );
				
				switch ( EscapeChar )
				{
					
					case U'n':
					{
						
						Out += U'\n';
						
						Index ++;
						
					}
					break;
					
					case U't':
					{
						
						Out += U'\t';
						
						Index ++;
						
					}
					break;
					
					case U'v':
					{
						
						Out += U'\v';
						
						Index ++;
						
					}
					break;
					
					case U'b':
					{
						
						Out += U'\b';
						
						Index ++;
						
					}
					break;
					
					case U'r':
					{
						
						Out += U'\r';
						
						Index ++;
						
					}
					break;
					
					case U'f':
					{
						
						Out += U'\f';
						
						Index ++;
						
					}
					break;
					
					case U'a':
					{
						
						Out += U'\a';
						
						Index ++;
						
					}
					break;
					
					case U'0':
					{
						
						Out += U'\0';
						
						Index ++;
						
					}
					break;
					
					case U'\\':
					{
						
						Out += U'\\';
						
						Index ++;
						
					}
					break;
					
					case U'\'':
					{
						
						Out += U'\'';
						
						Index ++;
						
					}
					break;
					
					case U'\"':
					{
						
						Out += U'\"';
						
						Index ++;
						
					}
					break;
					
					case U'u':
					{
						
						Index ++;
						
						if ( Index + 4 >= Source.size () )
						{
							
							Error = "Expected 4 hex digits after unicode 16-bit escape in string literal";
							
							return false;
							
						}
						
						uint32_t Sum = 0;
						
						for ( uint64_t I = 0; I < 4; ++ I )
						{
							
							Sum <<= 4;
							
							uint32_t HexVal = HexCodeToValue ( Source.at ( Index + I ) );
							
							if ( HexVal == 0xFFFFFFFF )
							{
								
								Error = "Unexpected non-hex code in unicode escape in string literal!";
								
								return false;
								
							}
							
							Sum |= HexVal;
							
						}
						
						Index += 4;
						
						Out += static_cast <char32_t> ( Sum );
						
					}
					break;
					
					case U'U':
					{
						
						Index ++;
						
						if ( Index + 8 >= Source.size () )
						{
							
							Error = "Expected 4 hex digits after unicode 16-bit escape in string literal";
							
							return false;
							
						}
						
						uint32_t Sum = 0;
						
						for ( uint64_t I = 0; I < 8; ++ I )
						{
							
							Sum <<= 4;
							
							uint32_t HexVal = HexCodeToValue ( Source.at ( Index + I ) );
							
							if ( HexVal == 0xFFFFFFFF )
							{
								
								Error = "Unexpected non-hex code in unicode escape in string literal";
								
								return false;
								
							}
							
							Sum |= HexVal;
							
						}
						
						Index += 8;
						
						Out += static_cast <char32_t> ( Sum );
						
					}
					break;
					
					case U'x':
					{
						
						Index ++;
						
						if ( Index + 2 > Source.size () )
						{
							
							Error = "Expected s hex digits after unicode 16-bit escape in string literal";
							
							return false;
							
						}
						
						Char = Source.at ( Index );
						
						if ( Char != U'{' )
						{
							
							uint32_t HexVal = HexCodeToValue ( Source.at ( Index ) );
							
							if ( HexVal == 0xFFFFFFFF )
							{
								
								Error = "Expected hexadecimal digit after hexadecimal escape code in string literal";
								
								return false;
								
							}
							
							HexVal <<= 4;
							
							HexVal |= HexCodeToValue ( Source.at ( Index + 1 ) );
							
							if ( HexVal == 0xFFFFFFFF )
							{
								
								Error = "Expected hexadecimal digit after hexadecimal escape code in string literal";
								
								return false;
								
							}
							
							Out += static_cast <char32_t> ( HexVal );
							
							Index += 2;
							
						}
						else
						{
							
							Index ++;
							
							uint32_t Count = 0;
							uint32_t Sum = 0;
							
							while ( Index < Source.size () )
							{
								
								Char = Source.at ( Index );
								uint32_t HexVal = HexCodeToValue ( Char );
								
								if ( HexVal == 0xFFFFFFFF )
								{
									
									if ( Count == 0 )
									{
										
										Error = "Expected hexadecimal value after opening curly bracket in unicode escape in string literal";
										
										return false;
										
									}
									
									if ( Char != U'}' )
									{
										
										Error = "Expected closing curly bracket in unicode escape in string literal";
										
										return false;
										
									}
									
									Index ++;
									Out += static_cast <char32_t> ( Sum );
									break;
									
								}
								
								if ( Count == 8 )
								{
									
									Error = "Expected no more than 8 hex digits in unicode escape in string literal";
									
									return false;
									
								}
								
								Sum <<= 4;
								Sum |= HexVal;
								
								Count ++;
								Index ++;
								
							}
							
							if ( Index >= Source.size () )
							{
								
								Error = "Expected closing curly bracket in unicode escape in string literal";
								
								return false;
								
							}
							
						}
						
					}
					break;
					
					default:
					{
						
						Error = "Invalid escape charachter in string literal: \'" + std :: to_string ( EscapeChar ) + "\'";
						
						return false;
						
					}
					
				}
				
			}
			break;
			
			case U'\"':
			return true;
			
			default:
			{
				
				Out += Char;
				
				Index ++;
				
			}
			break;
			
		}
		
	}
	
	Error = "Expected closing quotation mark at end of string literal";
	
	return false;
	
}

bool OakParseCharLiteral ( const std :: u32string & Source, char32_t & Out, std :: string & Error )
{
	
	if ( Source.size () < 3 )
	{
		
		Error = "Invalid char literal";
		
		return false;
		
	}
	
	uint32_t Index = 1;
	
	char32_t Char = Source.at ( Index );
	
	if ( Char == U'\\' )
	{
		
		Index ++;
		
		Char = Source.at ( Index );
		
		switch ( Char )
		{
			
			case U'n':
			{
				
				Out = U'\n';
				
				Index ++;
				
			}
			break;
			
			case U't':
			{
				
				Out = U'\t';
				
				Index ++;
				
			}
			break;
			
			case U'v':
			{
				
				Out = U'\v';
				
				Index ++;
				
			}
			break;
			
			case U'b':
			{
				
				Out = U'\b';
				
				Index ++;
				
			}
			break;
			
			case U'r':
			{
				
				Out = U'\r';
				
				Index ++;
				
			}
			break;
			
			case U'f':
			{
				
				Out = U'\f';
				
				Index ++;
				
			}
			break;
			
			case U'a':
			{
				
				Out = U'\a';
				
				Index ++;
				
			}
			break;
			
			case U'0':
			{
				
				Out = U'\0';
				
				Index ++;
				
			}
			break;
			
			case U'\\':
			{
				
				Out = U'\\';
				
				Index ++;
				
			}
			break;
			
			case U'\'':
			{
				
				Error = "";
				
			}
			break;
			
			case U'\"':
			{
				
				Out = U'\"';
				
				Index ++;
				
			}
			break;
			
			case U'u':
			{
				
				Index ++;
				
				if ( Index + 4 >= Source.size () )
				{
					
					Error = "Expected 4 hexadecimal digits after unicode escape specifier in char literal";
					
					return false;
					
				}
				
				uint32_t Sum = 0;
				
				for ( uint32_t I = 0; I < 4; I ++ )
				{
					
					Char = Source.at ( Index );
					uint32_t HexVal = HexCodeToValue ( Char );
					
					if ( HexVal == 0xFFFFFFFF )
					{
						
						Error = "Expected 4 hexadecimal digits after unicode escape specifier in char literal";
						
						return false;
						
					}
					
					Sum <<= 4;
					Sum |= HexVal;
					
					Index ++;
					
				}
				
				Out = Sum;
				
			}
			break;
			
			case U'U':
			{
				
				Index ++;
				
				if ( Index + 8 >= Source.size () )
				{
					
					Error = "Expected 8 hexadecimal digits after unicode escape specifier in char literal";
					
					return false;
					
				}
				
				uint32_t Sum = 0;
				
				for ( uint32_t I = 0; I < 8; I ++ )
				{
					
					Char = Source.at ( Index );
					uint32_t HexVal = HexCodeToValue ( Char );
					
					if ( HexVal == 0xFFFFFFFF )
					{
						
						Error = "Expected 8 hexadecimal digits after unicode escape specifier in char literal";
						
						return false;
						
					}
					
					Sum <<= 4;
					Sum |= HexVal;
					
					Index ++;
					
				}
				
				Out = Sum;
				
			}
			break;
			
			case U'x':
			{
				
				Index ++;
				
				if ( Index + 2 >= Source.size () )
				{
					
					Error = "Expected two-digid hexadecimal number after escape code in charachter literal";
					
					return false;
					
				}
				
				Char = Source.at ( Index );
				
				if ( Char == U'{' )
				{
					
					Index ++;
					
					bool Resolved = false;
					uint32_t Count = 0;
					uint32_t Sum = 0;
					
					while ( Index < Source.size () )
					{
						
						Char = Source.at ( Index );
						
						uint32_t HexVal = HexCodeToValue ( Char );
						
						if ( HexVal == 0xFFFFFFFF )
						{
							
							if ( Char == U'}' )
							{
								
								if ( Count == 0 )
								{
									
									Error = "Expected hexadecimal number after curly brace after escape code in charachter literal";
									
									return false;
									
								}
								
								Out = static_cast <char32_t> ( Sum );
								Resolved = true;
								
								break;
								
							}
							else
							{
								
								if ( Count == 0 )
									Error = "Expected hexadecimal number after curly brace after escape code in charachter literal";
								else
									Error = "Expected closing curly bracket at end of hexadecimal escape code in charachter literal";
								
								return false;
								
							}
							
						}
						
						if ( ( Sum & 0xF0000000 ) != 0 )
						{
							
							Error = "Escape code in charachter literal overflows 32-bit char";
							
							return false;
							
						}
						
						Sum <<= 4;
						Sum |= HexVal;
						
						Count ++;
						
						Index ++;
						
					}
					
					if ( Count == 0 )
					{
						
						Error = "Expected hexadecimal value after hex escape code in charachter literal";
						
						return false;
						
					}
					
					if ( ! Resolved )
					{
						
						Error = "Expected closing curly bracket at end of hexadecimal escape code in charachter literal";
						
						return false;
						
					}
					
					Index ++;
					
				}
				else
				{
					
					uint32_t HexVal = HexCodeToValue ( Char );
					
					if ( HexVal == 0xFFFFFFFF )
					{
						
						Error = "Expected two-digid hexadecimal number after escape code in charachter literal";
						
						return false;
						
					}
					
					Index ++;
					Char = Source.at ( Index );
					
					HexVal <<= 4;
					HexVal |= HexCodeToValue ( Char );
					
					if ( HexVal == 0xFFFFFFFF )
					{
						
						Error = "Expected two-digid hexadecimal number after escape code in charachter literal";
						
						return false;
						
					}
					
					Out = static_cast <char32_t> ( HexVal );
					
					Index ++;
					
				}
				
			}
			break;
			
		}
		
	}
	else
	{
		
		Out = Char;
		Index ++;
		
	}
	
	Char = Source.at ( Index );
	
	if ( Index >= Source.size () || ( Char != U'\'' ) )
	{
		
		Error = "Expected closing single quotation at end of charachter literal";
		
		return false;
		
	}
	
	return true;
	
}

void OakParseIntegerLiteral ( const std :: u32string & Source, uint64_t & Value, bool & Overflow64 )
{
	
	uint64_t Index = 0;
	char32_t Char = Source.at ( Index );
	
	bool PotentialOverflow64 = false;
	Overflow64 = false;
	
	if ( Char != U'0' )
	{
		
		uint64_t Temp = 0;
		
		do
		{
			
			Char = Source.at ( Index );
			
			if ( Char != U'_' )
			{
				
				int64_t COffset = static_cast <int64_t> ( Char ) - static_cast <int64_t> ( U'0' );
				
				if ( ( COffset < 0 ) || ( COffset > 9 ) )
				{
					
					Value = Temp;
					return;
					
				}
				
				uint64_t Check = Temp;
				
				Temp *= 10ULL;
				Temp += static_cast <uint64_t> ( COffset );
				
				if ( Temp / 10ULL != Check )
					Overflow64 = true;
				
			}
			
			Index ++;
			
		}
		while ( Index < Source.size () );
		
		Value = Temp;
		return;
		
	}
	else
	{
		
		Index ++;
		
		if ( Index >= Source.size () )
		{
			
			Value = 0;
			return;
			
		}
		
		Char = Source.at ( Index );
		
		switch ( Char )
		{
			
			case 'X':
			case 'x':
			case 'H':
			case 'h':
			{
				
				Index ++;
				
				uint64_t Temp = 0;
				
				do
				{
					
					Char = Source.at ( Index );
					
					if ( Char != U'_' )
					{
						
						int64_t COffsetDec = static_cast <int64_t> ( Char ) - static_cast <int64_t> ( U'0' );
						int64_t COffsetAlphLow = static_cast <int64_t> ( Char ) - static_cast <int64_t> ( U'a' );
						int64_t COffsetAlphUp = static_cast <int64_t> ( Char ) - static_cast <int64_t> ( U'A' );
						
						if ( ( COffsetDec >= 0 ) && ( COffsetDec <= 9 ) )
						{
							
							Temp <<= 4;
							Temp |= COffsetDec;
							
						}
						else if ( ( COffsetAlphLow >= 0 ) && ( COffsetAlphLow <= 5 ) )
						{
							
							Temp <<= 4;
							Temp |= ( COffsetAlphLow + 10 );
							
						}
						else if ( ( COffsetAlphUp >= 0 ) && ( COffsetAlphUp <= 5 ) )
						{
							
							Temp <<= 4;
							Temp |= ( COffsetAlphUp + 10 );
							
						}
						else
						{
							
							Value = Temp;
							return;
							
						}
						
						if ( PotentialOverflow64 )
							Overflow64 = true;
						
						if ( ( Temp & 0xF000000000000000 ) != 0 )
							PotentialOverflow64 = true;
						
					}
					
					Index ++;
					
				}
				while ( Index < Source.size () );
				
				Value = Temp;
				return;
				
			}
			break;
			
			case 'b':
			case 'B':
			{
				
				Index ++;
				
				uint64_t Temp = 0;
				
				do
				{
					
					Char = Source.at ( Index );
					
					if ( Char != U'_' )
					{
						
						uint64_t COffset = static_cast <uint64_t> ( Char ) - static_cast <uint64_t> ( U'0' );
						
						if ( COffset < 2 )
						{
							
							Temp <<= 1;
							Temp |= COffset;
							
							if ( PotentialOverflow64 )
								Overflow64 = true;
							
							if ( Temp & 0x8000000000000000 )
								PotentialOverflow64 = true;
							
						}
						else
						{
							
							Value = Temp;
							return;
							
						}
						
					}
					
					Index ++;
					
				}
				while ( Index < Source.size () );
				
				Value = Temp;
				return;
				
			}
			break;
			
			case 'o':
			case 'O':
			{
				
				Index ++;
				
				if ( Index >= Source.size () )
				{
					
					Value = 0;
					return;
					
				}
				
				uint64_t Temp = 0;
				
				do
				{
					
					Char = Source.at ( Index );
					
					if ( Char != U'_' )
					{
						
						int64_t COffset = static_cast <int64_t> ( Char ) - static_cast <int64_t> ( U'0' );
						
						if ( ( COffset >= 0 ) && ( COffset < 8 ) )
						{
							
							Temp <<= 3;
							Temp |= COffset;
							
							if ( PotentialOverflow64 )
								Overflow64 = true;
							
							if ( ( Temp & 0xE000000000000000ULL ) != 0 )
								PotentialOverflow64 = true;
							
						}
						else
						{
							
							Value = Temp;
							return;
							
						}
						
					}
					
					Index ++;
					
				}
				while ( Index < Source.size () );
				
				Value = Temp;
				return;
				
			}
			break;
			
			default:
			Value = 0;
			return;
			
		}
		
	}
	
}

bool OakParseFloatLiteral ( const std :: u32string Source, BigFloat & Value )
{
	
	if ( Source.size () < 2 )
	{
		
		Value = 0LL;
		
		return false;
		
	}
	
	uint32_t Index = 0;
	char32_t Char = Source.at ( Index );
	
	if ( Char != U'0' )
	{
		
		uint32_t SigDigitCount = 0;
		
		BigInteger Significand ( 0LL );
		
		do
		{
			
			Char = Source.at ( Index );
			
			uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
			
			if ( Diff >= 10 )
			{
				
				if ( Char == U'_' )
				{
					
					if ( SigDigitCount != 0 )
					{
						
						Index ++;
						
						continue;
						
					}
					
					return false;
					
				}
				
				if ( Char == 'f' )
				{
					
					if ( SigDigitCount == 0 )
						return false;
					
					Value.Set ( Significand );
					
					return true;
					
				}
				
				if ( Char == U'.' )
				{
					
					Index ++;
					
					if ( Index >= Source.size () )
						return false;
					
					int32_t FractionalDigits = 0;
					
					do
					{
						
						Char = Source.at ( Index );
						Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
						
						if ( Diff >= 10 )
						{
							
							if ( Char == U'_' )
							{
								
								if ( FractionalDigits != 0 )
								{
									
									Index ++;
									
									continue;
									
								}
								
								return false;
								
							}
							
							if ( Char == U'f' )
								break;
							
							if ( Char == 'e' )
							{
								
								Index ++;
								
								if ( Index >= Source.size () )
									return false;
								
								Char = Source.at ( Index );
								
								bool NegativeExponent = false;
								
								switch ( Char )
								{
									
									case U'+':
									{
										
										Index ++;
										
										if ( Index >= Source.size () )
											return false;
										
										Char = Source.at ( Index );
										
									}
									break;
									
									case U'-':
									{
										
										Index ++;
										
										if ( Index >= Source.size () )
											return false;
										
										NegativeExponent = true;
										
										Char = Source.at ( Index );
										
									}
									break;
									
									default:
									break;
									
								}
								
								int32_t ExponentValue = 0;
								uint32_t ExponentDigits = 0;
								
								do
								{
									
									Char = Source.at ( Index );
									
									uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
									
									if ( Diff >= 10 )
									{
										
										if ( Char != U'f' )
											return false;
										
										if ( ExponentDigits == 0 )
											return false;
										
										Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
										
										return true;
										
									}
									
									ExponentValue *= 10;
									ExponentValue += Diff;
									
									ExponentDigits ++;
									
									Index ++;
									
								}
								while ( Index < Source.size () );
								
								if ( ExponentDigits == 0 )
									return false;
								
								Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
								
								return true;
								
							}
							
						}
						
						Significand *= 10LL;
						Significand += Diff;
						
						FractionalDigits ++;
						
						Index ++;
						
					}
					while ( Index < Source.size () );
					
					if ( FractionalDigits == 0 )
						return false;
					
					Value.Set ( Significand, 0, - FractionalDigits );
					
					return true;
					
				}
				
				if ( Char == 'e' )
				{
					
					Index ++;
					
					if ( Index >= Source.size () )
						return false;
					
					Char = Source.at ( Index );
					
					bool NegativeExponent = false;
					
					switch ( Char )
					{
						
						case U'+':
						{
							
							Index ++;
							
							if ( Index >= Source.size () )
								return false;
							
							Char = Source.at ( Index );
							
						}
						break;
						
						case U'-':
						{
							
							Index ++;
							
							if ( Index >= Source.size () )
								return false;
							
							NegativeExponent = true;
							
							Char = Source.at ( Index );
							
						}
						break;
						
						default:
						break;
						
					}
					
					int32_t ExponentValue = 0;
					uint32_t ExponentDigits = 0;
					
					do
					{
						
						Char = Source.at ( Index );
						
						uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
						
						if ( Diff >= 10 )
						{
							
							if ( Char != U'f' )
								return false;
							
							if ( ExponentDigits == 0 )
								return false;
							
							Value.Set ( Significand, 0, - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
							
							return true;
							
						}
						
						ExponentValue *= 10;
						ExponentValue += Diff;
						
						ExponentDigits ++;
						
						Index ++;
						
					}
					while ( Index < Source.size () );
					
					if ( ExponentDigits == 0 )
						return false;
					
					Value.Set ( Significand, 0, - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
					
					return true;
					
				}
				
			}
			
			Significand *= 10LL;
			Significand += Diff;
			
			SigDigitCount ++;
			
			Index ++;
			
		}
		while ( Index < Source.size () );
		
		return false;
		
	}
	else
	{
		
		Index ++;
		
		if ( Index >= Source.size () )
		{
			
			Value = 0LL;
			
			return true;
			
		}
		
		Char = Source.at ( Index );
		
		switch ( Char )
		{
			
			case U'x':
			case U'X':
			{
				
				BigInteger Significand ( 0LL );
				
				Index ++;
				
				if ( Index >= Source.size () )
					return false;
				
				uint32_t HexDigitCount = 0;
				
				do
				{
					
					Char = Source.at ( Index );
					
					uint32_t HexVal = HexCodeToValue ( Char );
					
					if ( HexVal >= 16 )
					{
						
						if ( HexDigitCount == 0 )
							return false;
						
						if ( Char == U'_' )
						{
							
							Index ++;
							
							continue;
							
						}
						
						if ( Char != U'p' )
							return false;
						
						Index ++;
						
						if ( Index >= Source.size () )
							return false;
						
						bool NegativeExponent = false;
						
						Char = Source.at ( Index );
						
						if ( Char == U'+' )
						{
							
							Index ++;
							
							if ( Index >= Source.size () )
								return false;
							
						}
						else if ( Char == U'-' )
						{
							
							Index ++;
							
							if ( Index >= Source.size () )
								return false;
							
							NegativeExponent = true;
							
						}
						
						uint32_t ExponentDigits = 0;
						int32_t ExponentValue = 0;
						
						do
						{
							
							Char = Source.at ( Index );
							
							uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
							
							if ( Diff >= 10 )
							{
								
								if ( ExponentDigits == 0 )
									return false;
								
								Value.Set ( Significand, NegativeExponent ? - ExponentValue : ExponentValue );
								
								return true;
								
							}
							
							ExponentValue *= 10;
							ExponentValue += Diff;
							
							ExponentDigits ++;
							
							Index ++;
							
						}
						while ( Index < Source.size () );
						
						if ( ExponentDigits != 0 )
						{
							
							Value.Set ( Significand, NegativeExponent ? - ExponentValue : ExponentValue );
							
							return true;
							
						}
						
						return false;
						
					}
					
					Significand <<= 4;
					Significand |= static_cast <int64_t> ( HexVal );
					
					HexDigitCount ++;
					
					Index ++;
					
				}
				while ( Index < Source.size () );
				
				return false;
				
			}
			
			case U'.':
			{
				
				Index ++;
				
				if ( Index >= Source.size () )
					return false;
				
				BigInteger Significand ( 0LL );
				int32_t FractionalDigits = 0;
				
				do
				{
					
					Char = Source.at ( Index );
					
					uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( U'0' );
					
					if ( Diff >= 10 )
					{
						
						if ( FractionalDigits == 0 )
							return false;
						
						switch ( Char )
						{
							
							case 'e':
							{
								
								Index ++;
								
								if ( Index >= Source.size () )
									return false;
								
								Char = Source.at ( Index );
								
								bool NegativeExponent = false;
								
								switch ( Char )
								{
									
									case U'+':
									{
										
										Index ++;
										
										if ( Index >= Source.size () )
											return false;
										
										Char = Source.at ( Index );
										
									}
									break;
									
									case U'-':
									{
										
										Index ++;
										
										if ( Index >= Source.size () )
											return false;
										
										NegativeExponent = true;
										
										Char = Source.at ( Index );
										
									}
									break;
									
									default:
									break;
									
								}
								
								int32_t ExponentValue = 0;
								uint32_t ExponentDigits = 0;
								
								// NOTE: ERROR IF EPONENT OVERFLOWS 32 BITS
								
								do
								{
									
									Char = Source.at ( Index );
									
									uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
									
									if ( Diff >= 10 )
									{
										
										if ( Char != U'f' )
											return false;
										
										if ( ExponentDigits == 0 )
											return false;
										
										Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
										
										return true;
										
									}
									
									ExponentValue *= 10;
									ExponentValue += Diff;
									
									ExponentDigits ++;
									
								}
								while ( Index < Source.size () );
								
								if ( ExponentDigits == 0 )
									return false;
								
								Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
								
								return true;
								
							}
							
							case 'f':
							{
								
								Value.Set ( Significand, 0, - FractionalDigits );
								
								return true;
								
							}
							
						}
						
						return false;
						
					}
					
					Significand *= 10LL;
					Significand += Diff;
					
					FractionalDigits ++;
					
					Index ++;
					
				}
				while ( Index < Source.size () );
				
				if ( FractionalDigits == 0 )
					return false;
				
				Value.Set ( Significand, 0, - FractionalDigits );
				
				return true;
				
			}
			
			case U'0':
			case U'1':
			case U'2':
			case U'3':
			case U'4':
			case U'5':
			case U'6':
			case U'7':
			case U'8':
			case U'9':
			case U'_':
			{
				
				BigInteger Significand ( 0LL );
				int32_t FractionalDigits = 0;
				
				do
				{
					
					Char = Source.at ( Index );
					
					if ( Char == '_' )
						Index ++;
					else
					{
						
						uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
						
						if ( Diff >= 10 )
						{
							
							switch ( Char )
							{
								
								case U'e':
								{
									
									Index ++;
									
									if ( Index >= Source.size () )
										return false;
									
									Char = Source.at ( Index );
									
									bool NegativeExponent = false;
									
									switch ( Char )
									{
										
										case U'+':
										{
											
											Index ++;
											
											if ( Index >= Source.size () )
												return false;
											
											Char = Source.at ( Index );
											
										}
										break;
										
										case U'-':
										{
											
											Index ++;
											
											if ( Index >= Source.size () )
												return false;
											
											NegativeExponent = true;
											
											Char = Source.at ( Index );
											
										}
										break;
										
										default:
										break;
										
									}
									
									int32_t ExponentValue = 0;
									uint32_t ExponentDigits = 0;
									
									// NOTE: ERROR IF EPONENT OVERFLOWS 32 BITS
									
									do
									{
										
										Char = Source.at ( Index );
										
										uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
										
										if ( Diff >= 10 )
										{
											
											if ( Char != U'f' )
												return false;
											
											if ( ExponentDigits == 0 )
												return false;
											
											Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
											
											return true;
											
										}
										
										ExponentValue *= 10;
										ExponentValue += Diff;
										
										ExponentDigits ++;
										
									}
									while ( Index < Source.size () );
									
									if ( ExponentDigits == 0 )
										return false;
									
									Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
									
									return true;
									
								}
								
								case U'f':
								{
									
									Value.Set ( Significand );
									
									return true;
									
								}
								
								case U'.':
								{
									
									Index ++;
									
									if ( Index >= Source.size () )
										return false;
									
									do
									{
										
										Char = Source.at ( Index );
										
										uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( '0' );
										
										if ( Diff >= 10 )
										{
											
											if ( FractionalDigits == 0 )
												return false;
											
											switch ( Char )
											{
												
												case U'f':
												{
													
													Value.Set ( Significand, 0, - FractionalDigits );
													
													return true;
													
												}
												
												case U'e':
												{
													
													Index ++;
													
													if ( Index >= Source.size () )
														return false;
													
													Char = Source.at ( Index );
													
													bool NegativeExponent = false;
													
													switch ( Char )
													{
														
														case U'+':
														{
															
															Index ++;
															
															if ( Index >= Source.size () )
																return false;
															
															Char = Source.at ( Index );
															
														}
														break;
														
														case U'-':
														{
															
															Index ++;
															
															if ( Index >= Source.size () )
																return false;
															
															NegativeExponent = true;
															
															Char = Source.at ( Index );
															
														}
														break;
														
														default:
														break;
														
													}
													
													int32_t ExponentValue = 0;
													uint32_t ExponentDigits = 0;
													
													// NOTE: ERROR IF EPONENT OVERFLOWS 32 BITS
													
													do
													{
														
														Char = Source.at ( Index );
														
														uint32_t Diff = static_cast <uint32_t> ( Char ) - static_cast <uint32_t> ( U'0' );
														
														if ( Diff >= 10 )
														{
															
															if ( Char != U'f' )
																return false;
															
															if ( ExponentDigits == 0 )
																return false;
															
															Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
															
															return true;
															
														}
														
														ExponentValue *= 10;
														ExponentValue += Diff;
														
														ExponentDigits ++;
														
													}
													while ( Index < Source.size () );
													
													if ( ExponentDigits == 0 )
														return false;
													
													Value.Set ( Significand, 0, - FractionalDigits - ( NegativeExponent ? - ExponentValue : ExponentValue ) );
													
													return true;
													
												}
												
												default:
												return false;
												
											}
											
										}
										
									}
									while ( Index < Source.size () );
									
								}
								break;
								
							}
							
						}
						
						Significand *= 10LL;
						Significand += Diff;
						
					}
					
				}
				while ( Index < Source.size () );
				
				Value.Set ( Significand );
				
				return true;
				
			}
			break;
			
			default:
			return false;
			
		}
		
	}
	
	return false;
	
}
