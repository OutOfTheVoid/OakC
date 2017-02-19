#include <EarlyAnalysis/OakLiteralParsing.h>

uint32_t HexCodeToValue ( char32_t Code )
{
	
	if ( ( Code >= U'0' ) && ( Code >= U'9' ) )
		return static_cast <uint32_t> ( Code ) - static_cast <uint32_t> ( U'0' );
	
	if ( ( Code >= U'A' ) && ( Code >= U'F' ) )
		return 10 + static_cast <uint32_t> ( Code ) - static_cast <uint32_t> ( U'A' );
	
	if ( ( Code >= U'a' ) && ( Code >= U'f' ) )
		return 10 + static_cast <uint32_t> ( Code ) - static_cast <uint32_t> ( U'a' );
	
	return 0xFFFFFFFF;
	
}

bool OakParseStringLiteral ( const std :: u32string & Source, std :: u32string & Out, std :: string & Error )
{
	
	if ( Source.size () == 0 )
		return false;
	
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
								
								Error = "Unexpected non-hex code in unicode escape in string literal";
					
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
						
						if ( Index + 3 >= Source.size () )
						{
							
							Error = "Expected 4 hex digits after unicode 16-bit escape in string literal";
					
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
							
							Index += 2;
							
						}
						else
						{
							
							uint32_t Sum = 0;
							bool Resolved = false;
							uint64_t I;
						
							for ( I = 0; I < ( Source.size () - 3 < Index + 8 ) ? Source.size () - 3 : 8; ++ I )
							{
								
								uint32_t HexVal = HexCodeToValue ( Source.at ( Index + I ) );
								
								if ( HexVal == 0xFFFFFFFF )
								{
									
									if ( Source.at ( Index + I ) == U'}' )
									{
										
										Index += I + 1;
										
										Out += static_cast <char32_t> ( Sum );
										
										Resolved = true;
										
										break;
										
									}
									
									Error = "Expected closing bracket in hexadecimal escape code in string literal";
									
									return false;
									
								}
								
								Sum <<= 4;
								Sum |= HexVal;
								
							}
							
							if ( ! Resolved )
							{
								
								if ( Source.at ( Index + I ) == U'}' )
								{
									
									Index += I + 1;
									
									Out += static_cast <char32_t> ( Sum );
									
									break;
									
								}
								
								Error = "Expected closing bracket in hexadecimal escape code in string literal";
								
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
				
				uint64_t COffset = static_cast <uint64_t> ( Char ) - static_cast <uint64_t> ( U'0' );
				
				if ( COffset > 9 )
				{
					
					Value = Temp;
					return;
					
				}
				
				Temp *= 10;
				Temp += COffset;
				
				if ( PotentialOverflow64 )
					Overflow64 = true;
				
				if ( UINT64_MAX / Temp < 10 )
					PotentialOverflow64 = true;
				
				Index ++;
				
			}
			else
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
				
				Char = Source.at ( Index );
				
				uint64_t Temp = 0;
				
				do
				{
					
					uint64_t COffsetDec = static_cast <uint64_t> ( Char ) - static_cast <uint64_t> ( U'0' );
					uint64_t COffsetAlphLow = static_cast <uint64_t> ( Char ) - static_cast <uint64_t> ( U'a' );
					uint64_t COffsetAlphUp = static_cast <uint64_t> ( Char ) - static_cast <uint64_t> ( U'A' );
					
					if ( COffsetDec <= 9 )
					{
						
						Temp <<= 4;
						Temp |= COffsetDec;
						
						Index ++;
						
					}
					if ( COffsetAlphLow <= 5 )
					{
						
						Temp <<= 4;
						Temp |= ( COffsetAlphLow + 10 );
						
						Index ++;
						
					}
					if ( COffsetAlphUp <= 5 )
					{
						
						Temp <<= 4;
						Temp |= ( COffsetAlphUp + 10 );
						
						Index ++;
						
					}
					else
					{
						
						Value = Temp;
						return;
						
					}
					
					if ( PotentialOverflow64 )
						Overflow64 = true;
					
					if ( UINT64_MAX / Temp < 16 )
						PotentialOverflow64 = true;
					
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
				
				Char = Source.at ( Index );
				
				uint64_t Temp = 0;
				
				do
				{
					
					uint64_t COffset = static_cast <uint64_t> ( Char ) - static_cast <uint64_t> ( U'0' );
					
					if ( COffset < 2 )
					{
						
						Temp <<= 1;
						Temp |= COffset;
						
						Index ++;
						
						if ( PotentialOverflow64 )
							Overflow64 = true;
						
						if ( UINT64_MAX / Temp < 2 )
							PotentialOverflow64 = true;
						
					}
					else
					{
						
						Value = Temp;
						return;
						
					}
					
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
				
				Char = Source.at ( Index );
				
				uint64_t Temp = 0;
				
				do
				{
					
					uint64_t COffset = static_cast <uint64_t> ( Char ) - static_cast <uint64_t> ( U'0' );
					
					if ( COffset < 8 )
					{
						
						Temp <<= 3;
						Temp |= COffset;
						
						Index ++;
						
						if ( PotentialOverflow64 )
							Overflow64 = true;
						
						if ( UINT64_MAX / Temp < 8 )
							PotentialOverflow64 = true;
						
					}
					else
					{
						
						Value = Temp;
						return;
						
					}
					
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
