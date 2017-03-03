#ifndef EARLYANALYSIS_OAKLITERALPARSING_H
#define EARLYANALYSIS_OAKLITERALPARSING_H

#include <string>

bool OakParseStringLiteral ( const std :: u32string & Source, std :: u32string & Out, std :: string & Error );
bool OakParseCharLiteral ( const std :: u32string & Source, char32_t & Out, std :: string & Error );
void OakParseIntegerLiteral ( const std :: u32string & Source, uint64_t & Value, bool & Overflow64 );

#endif
