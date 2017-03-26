#include <Parsing/Language/OakParsingUtils.h>

#include <Tokenization/Language/OakTokenTags.h>
#include <Lexing/Language/OakKeywordTokenTags.h>

bool OakParsingUtils :: KeywordCheck ( const Token * ToCheck, uint64_t KeywordAuxTag )
{
	
	if ( ToCheck -> GetTag () != OakTokenTags :: kTokenTag_Identifier )
		return false;
	
	if ( ( ToCheck -> GetAuxTag () & OakKeywordTokenTags :: kKeywordAuxTags_Mask_Meaning ) != KeywordAuxTag )
		return false;
	
	return true;
	
}
