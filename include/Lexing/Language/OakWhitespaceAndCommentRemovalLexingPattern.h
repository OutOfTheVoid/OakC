#ifndef LEXING_LANGUAGE_OAKWHITESPACEANDCOMMENTREMOVALLEXINGPATTERN_H
#define LEXING_LANGUAGE_OAKWHITESPACEANDCOMMENTREMOVALLEXINGPATTERN_H

#include <Lexing/ILexingPattern.h>

class OakWhitespaceAndCommentRemovalLexingPattern : public virtual ILexingPattern
{
public:
	
	OakWhitespaceAndCommentRemovalLexingPattern ();
	~OakWhitespaceAndCommentRemovalLexingPattern ();
	
	void TryPattern ( ILexingInput & Input, ILexingResult & Result );
	
};

#endif
