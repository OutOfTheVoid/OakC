#include <Encoding/CodeConversion.h>

#include <locale>
#include <iostream>

std :: u32string CodeConversion :: ConvertUTF8ToUTF32 ( std :: string UTF8String )
{
	
	std :: u32string OutBuff ( UTF8String.size (), U'\0' );
	
	uint64_t OutIndex = 0;
	
	for ( uint64_t Index = 0; Index < UTF8String.size (); Index ++ )
	{
		
		uint32_t CharachterCode = static_cast <uint32_t> ( UTF8String.at ( Index ) );
		
		if ( CharachterCode < 0x00000080 )
		{
			
			OutBuff [ OutIndex ] = static_cast <char32_t> ( CharachterCode );
			OutIndex ++;
			
			continue;
			
		}
		
		if ( CharachterCode < 0xE0 )
		{
			
			uint32_t Total = ( static_cast <uint32_t> ( UTF8String.at ( Index ) ) & 0x1F ) << 6;
			Total |= ( static_cast <uint32_t> ( UTF8String.at ( Index + 1 ) ) & 0x3F );
			
			Index ++;
			
			OutBuff [ OutIndex ] = static_cast <char32_t> ( Total );
			OutIndex ++;
			
			continue;
			
		}
		
		if ( CharachterCode < 0xF0 )
		{
			
			uint32_t Total = ( static_cast <uint32_t> ( UTF8String.at ( Index ) ) & 0x0F ) << 12;
			Total |= ( ( static_cast <uint32_t> ( UTF8String.at ( Index + 1 ) ) & 0x3F ) << 6 );
			Total |= ( static_cast <uint32_t> ( UTF8String.at ( Index + 2 ) ) & 0x3F );
			
			Index += 2;
			
			OutBuff [ OutIndex ] = static_cast <char32_t> ( Total );
			OutIndex ++;
			
			continue;
			
		}
		
		// else
		{
			
			uint32_t Total = ( static_cast <uint32_t> ( UTF8String.at ( Index ) ) & 0x07 ) << 18;
			Total |= ( ( static_cast <uint32_t> ( UTF8String.at ( Index + 1 ) ) & 0x3F ) << 12 );
			Total |= ( ( static_cast <uint32_t> ( UTF8String.at ( Index + 2 ) ) & 0x3F ) << 6 );
			Total |= ( static_cast <uint32_t> ( UTF8String.at ( Index + 3 ) ) & 0x3F );
			
			Index += 3;
			
			OutBuff [ OutIndex ] = static_cast <char32_t> ( Total );
			OutIndex ++;
			
		}
		
	}
	
	OutBuff.resize ( OutIndex );
	
	return OutBuff;
	
}

std :: string CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string UTF32String )
{
	
	std :: string OutBuff ( (size_t) UTF32String.size () * 4, '\0' );
	
	uint64_t OutIndex = 0;
	
	for ( uint64_t Index = 0; Index < UTF32String.size (); Index ++ )
	{
		
		uint32_t CharachterCode = static_cast <uint32_t> ( UTF32String.at ( Index ) );
		
		if ( CharachterCode < 0x80 )
		{
			
			OutBuff [ OutIndex ] = static_cast <char> ( CharachterCode );
			OutIndex ++;
			
		}
		else if ( CharachterCode < 0x800 )
		{
			
			OutBuff [ OutIndex ] = static_cast <char> ( ( ( CharachterCode >> 6 ) & 0x1F ) | 0xC0 );
			OutBuff [ OutIndex + 1 ] = static_cast <char> ( ( CharachterCode & 0x3F ) | 0x80 );
			
			OutIndex += 2;
			
		}
		else if ( CharachterCode < 0x10000 )
		{
			
			OutBuff [ OutIndex ] = static_cast <char> ( ( ( CharachterCode >> 12 ) & 0x0F ) | 0xE0 );
			OutBuff [ OutIndex + 1 ] = static_cast <char> ( ( ( CharachterCode >> 6 ) & 0x3F ) | 0x80 );
			OutBuff [ OutIndex + 2 ] = static_cast <char> ( ( CharachterCode & 0x3F ) | 0x80 );
			
			OutIndex += 3;
			
		}
		else
		{
			
			OutBuff [ OutIndex ] = static_cast <char> ( ( ( CharachterCode >> 18 ) & 0x07 ) | 0xF0 );
			OutBuff [ OutIndex + 1 ] = static_cast <char> ( ( ( CharachterCode >> 12 ) & 0x3F ) | 0x80 );
			OutBuff [ OutIndex + 2 ] = static_cast <char> ( ( ( CharachterCode >> 6 ) & 0x3F ) | 0x80 );
			OutBuff [ OutIndex + 3 ] = static_cast <char> ( ( CharachterCode & 0x3F ) | 0x80 );
			
			OutIndex += 4;
			
		}
		
	}
	
	OutBuff.resize ( OutIndex );
	
	return OutBuff;
	
}