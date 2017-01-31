#ifndef STRINGUTILS_CHARTESTSET_H
#define STRINGUTILS_CHARTESTSET_H

#include <stdint.h>

class CharTestSet
{
public:
	
	static const CharTestSet NonZeroDigits; // 1 - 9
	static const CharTestSet Digits; // 0 - 9
	static const CharTestSet DigitsUnderscore; // 0 - 9, _
	
	static const CharTestSet HexDigits; // 0 - 9, a - f, A - F
	static const CharTestSet HexDigitsUnderscore; // 0 - 9, a - f, A - F, _
	
	static const CharTestSet BinaryDigits; // 0, 1
	static const CharTestSet BinaryDigitsUnderscore; // 0, 1, _
	
	static const CharTestSet OctalDigits; // 0 - 7
	static const CharTestSet OctalDigitsUnderscore; // 0 - 7, _
	
	CharTestSet ( const char32_t * CharSet, uint32_t SetSize, bool DeleteOnDestruct );
	CharTestSet ( const CharTestSet * SubSet, const char32_t * CharSet, uint32_t SetSize, bool DeleteOnDestruct );
	
	~CharTestSet ();
	
	void SetChars ( const char32_t * CharSet, uint32_t SetSize, bool DeleteOnDestruct );
	void SetSubSet ( CharTestSet * SubSet );
	
	const char32_t * GetChars () const;
	uint32_t GetCharCount () const;
	
	const CharTestSet * GetSubSet () const;
	
	bool Contains ( char32_t TestChar ) const;
	
private:
	
	const char32_t * CharSet;
	uint32_t SetSize;
	
	bool DeleteOnDestruct;
	
	const CharTestSet * SubSet;
	
};

#endif
