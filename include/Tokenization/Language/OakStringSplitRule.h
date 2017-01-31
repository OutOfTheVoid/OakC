#ifndef TOKENIZER_LANGUAGE_OAKSTRINGSPLITRULE_H
#define TOKENIZER_LANGUAGE_OAKSTRINGSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class OakStringSplitRule : public virtual ITokenSplitRule
{
public:
	
	/// Constructor. (no-op)
	OakStringSplitRule ();
	
	/// Destructor. (no-op)
	~OakStringSplitRule ();
	
	/// Implements ITokenSplitRule :: TrySplit.
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
};

#endif
