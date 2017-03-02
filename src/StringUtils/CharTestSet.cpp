#include <StringUtils/CharTestSet.h>

#ifndef NULL
	#define NULL 0
#endif

const CharTestSet CharTestSet :: NonZeroDigits ( U"123456789", 9, false );
const CharTestSet CharTestSet :: Digits ( U"0123456789", 10, false );
const CharTestSet CharTestSet :: DigitsUnderscore ( U"_0123456789", 11, false );

const CharTestSet CharTestSet :: HexDigits ( U"0123456789ABCDEFabcdef", 22, false );
const CharTestSet CharTestSet :: HexDigitsUnderscore ( U"_0123456789ABCDEFabcdef", 23, false );

const CharTestSet CharTestSet :: BinaryDigits ( U"01", 2, false );
const CharTestSet CharTestSet :: BinaryDigitsUnderscore ( U"_01", 3, false );

const CharTestSet CharTestSet :: OctalDigits ( U"01234567", 8, false );
const CharTestSet CharTestSet :: OctalDigitsUnderscore ( U"_01234567", 9, false );

// TODO: optimize for sets which are mostly linear, or otherwise exist within a sufficiently small range, using a simple bool [] corresponding to charachters.

CharTestSet :: CharTestSet ( const char32_t * CharSet, uint32_t SetSize, bool DeleteOnDestruct ):
	CharSet ( CharSet ),
	SetSize ( SetSize ),
	DeleteOnDestruct ( DeleteOnDestruct ),
	SubSet ( NULL )
{
}

CharTestSet :: CharTestSet ( const CharTestSet * SubSet, const char32_t * CharSet, uint32_t SetSize, bool DeleteOnDestruct ):
	CharSet ( CharSet ),
	SetSize ( SetSize ),
	DeleteOnDestruct ( DeleteOnDestruct ),
	SubSet ( SubSet )
{
}

CharTestSet :: ~CharTestSet ()
{
	
	if ( DeleteOnDestruct )
		delete[] CharSet; 
	
}

void CharTestSet :: SetChars ( const char32_t * CharSet, uint32_t SetSize, bool DeleteOnDestruct )
{
	
	this -> SetSize = SetSize;
	
	if ( CharSet == this -> CharSet )
	{
		
		this -> DeleteOnDestruct = DeleteOnDestruct;
		
		return;
		
	}
	
	if ( this -> DeleteOnDestruct )
		delete [] this -> CharSet;
	
	this -> CharSet = CharSet;
	this -> DeleteOnDestruct = DeleteOnDestruct;
	
}

void CharTestSet :: SetSubSet ( CharTestSet * SubSet )
{
	
	this -> SubSet = SubSet;
	
}

const char32_t * CharTestSet :: GetChars () const
{
	
	return CharSet;
	
}

uint32_t CharTestSet :: GetCharCount () const
{
	
	return SetSize;
	
}

const CharTestSet * CharTestSet :: GetSubSet () const
{
	
	return SubSet;
	
}

bool CharTestSet :: Contains ( char32_t TestChar ) const
{
	
	for ( uint32_t I = 0; I < SetSize; I ++ )
	{
		
		if ( CharSet [ I ] == TestChar )
			return true;
		
	}
	
	if ( SubSet != NULL )
		return SubSet -> Contains ( TestChar );
	
	return false;
	
}
