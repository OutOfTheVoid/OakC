#include <StringUtils/RangeStringCompositor.h>

RangeStringCompositor :: RangeStringCompositor ():
	Ranges (),
	Individuals ()
{
}

RangeStringCompositor :: ~RangeStringCompositor ()
{
	
	Clear ();
	
}

void RangeStringCompositor :: AddRange ( char32_t LowChar, char32_t HighChar )
{
	
	CharRange Range;
	
	Range.Low = LowChar;
	Range.High = HighChar;
	
	Ranges.push_back ( Range );
	
}

void RangeStringCompositor :: AddIndividual ( char32_t Char )
{
	
	Individuals.push_back ( Char );
	
}

void RangeStringCompositor :: AddInherited ( RangeStringCompositor & Parent )
{
	
	for ( uint32_t I = 0; I < Parent.Ranges.size (); I ++ )
		Ranges.push_back ( Parent.Ranges [ I ] );
	
	for ( uint32_t I = 0; I < Parent.Individuals.size (); I ++ )
		Individuals.push_back ( Parent.Individuals [ I ] );
	
}

void RangeStringCompositor :: Clear ()
{
	
	Ranges.clear ();
	Individuals.clear ();
	
}

std :: u32string RangeStringCompositor :: CompositeString ()
{
	
	uint32_t Count = Individuals.size ();
	
	for ( uint32_t I = 0; I < Ranges.size (); I ++ )
		Count += static_cast <uint32_t> ( Ranges [ I ].High - static_cast <uint32_t> ( Ranges [ I ].Low ) );
	
	std :: u32string OutString ( Count, U'\0' );
	
	uint32_t Index = 0;
	
	for ( uint32_t I = 0; I < Ranges.size (); I ++ )
	{
		
		uint32_t RangeSize = static_cast <uint32_t> ( Ranges [ I ].High - static_cast <uint32_t> ( Ranges [ I ].Low ) );
		
		for ( uint32_t J = 0; J < RangeSize; J ++ )
			OutString [ Index + J ] = static_cast <char32_t> (  static_cast <uint32_t> ( Ranges [ I ].Low ) + J );
		
		Index += RangeSize;
		
	}
	
	for ( uint32_t I = 0; I < Individuals.size (); I ++ )
		OutString [ Index + I ] = Individuals [ I ];
	
	return OutString;
	
}
