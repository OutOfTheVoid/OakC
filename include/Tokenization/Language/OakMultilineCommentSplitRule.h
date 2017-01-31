#ifndef TOKENIZATION_LANGUAGE_OAKMULTILINECOMMENTSPLITRULE_H
#define TOKENIZATION_LANGUAGE_OAKMULTILINECOMMENTSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class OakMultilineCommentSplitRule : public virtual ITokenSplitRule
{
public:
	
	/// Constructor. (no-op)
	OakMultilineCommentSplitRule ();
	
	/// Destructor. (no-op)
	~OakMultilineCommentSplitRule ();
	
	/// Implements ITokenSplitRule :: TrySplit.
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
};

#endif
