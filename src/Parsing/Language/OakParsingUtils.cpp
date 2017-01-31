#include <Parsing/Language/OakParsingUtils.h>

#include <Tokenization/Language/OakTokenTags.h>

bool OakParsingUtils :: KeywordCheck ( const Token * ToCheck, uint64_t KeywordAuxTag )
{
	
	if ( ToCheck -> GetTag () != OakTokenTags :: kTokenTag_Identifier )
		return false;
	
	if ( ToCheck -> GetAuxTag () != KeywordAuxTag )
		return false;
	
	return true;
	
}
