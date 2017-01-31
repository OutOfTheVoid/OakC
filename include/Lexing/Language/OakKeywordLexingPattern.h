#ifndef LEXING_LANGUAGE_OAKKEYWORDLEXINGPATTERN_H
#define LEXING_LANGUAGE_OAKKEYWORDLEXINGPATTERN_H

#include <Lexing/ILexingPattern.h>

#include <string>

#include <Utils/Trie.h>

class OakKeywordLexingPattern : public virtual ILexingPattern
{
public:
	
	OakKeywordLexingPattern ();
	~OakKeywordLexingPattern ();
	
	void TryPattern ( ILexingInput & Input, ILexingResult & Result );
	
private:
	
	UTF8Trie <uint64_t> KeywordAuxTags;
	
};

#endif
