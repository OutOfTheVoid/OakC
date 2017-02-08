#ifndef TOKENIZATION_LANGUAGE_OAKCHARLITERALSPLITRULE_H
#define TOKENIZATION_LANGUAGE_OAKCHARLITERALSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class OakCharSplitRule : public virtual ITokenSplitRule
{
public:
	
	/// Constructor. (no-op)
	OakCharSplitRule ();
	
	/// Destructor. (no-op)
	~OakCharSplitRule ();
	
	/// Implements ITokenSplitRule :: TrySplit.
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
};

#endif
