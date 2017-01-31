#ifndef PARSING_LANGUAGE_PARSINGUTILS_H
#define PARSING_LANGUAGE_PARSINGUTILS_H

#include <stdint.h>

#include <Tokenization/Token.h>

namespace OakParsingUtils
{
	
	bool KeywordCheck ( const Token * ToCheck, uint64_t KeywordAuxTag );
	
}

#endif
