#ifndef LEXING_LANGUAGE_OAKKEYWORDLEXINGPATTERN_H
#define LEXING_LANGUAGE_OAKKEYWORDLEXINGPATTERN_H

#include <Lexing/ILexingPattern.h>
#include <Lexing/Language/OakKeywords.h>

#include <string>

#include <Utils/Trie.h>

/// The keyword lexing pattern assigns an auxiliary tag to tokens to identify them as keywords or identifiers, as specified in the OakKeywordTokenTags namespace
class OakKeywordLexingPattern : public virtual ILexingPattern
{
public:
	
	OakKeywordLexingPattern ();
	~OakKeywordLexingPattern ();
	
	void TryPattern ( ILexingInput & Input, ILexingResult & Result );
	
private:
	
	void AddLocalization ( const OakKeywords :: KeywordLocalization & Localization, uint64_t LocalizationIndex, bool Overwrite );
	
	UTF8Trie <uint64_t> KeywordAuxTags;
	
};

#endif
