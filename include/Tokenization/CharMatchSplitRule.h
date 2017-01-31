#ifndef TOKENIZATION_CHARMATCHSPLITRULE_H
#define TOKENIZATION_CHARMATCHSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class CharMatchSplitRule : public virtual ITokenSplitRule
{
public:
	
	/// Constructor.
	CharMatchSplitRule ( char32_t MatchChar, uint64_t Tag );
	/// Destructor (no-op)
	~CharMatchSplitRule ();
	
	/// Implementation of ITokenSplitRule :: TrySplit
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
private:
	
	const char32_t MatchChar;
	const uint64_t Tag;
	
};

#endif
