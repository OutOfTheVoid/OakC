#ifndef TOKENIZATION_MULTISTRINGMATCHSPLITRULE_H
#define TOKENIZATION_MULTISTRINGMATCHSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class MultiStringMatchSplitRule : public virtual ITokenSplitRule
{
public:
	
	MultiStringMatchSplitRule ( const char32_t * Strings [], uint32_t StringCount, uint64_t Tag );
	~MultiStringMatchSplitRule ();
	
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
private:
	
	std :: u32string * Strings;
	uint32_t StringCount;
	
	uint64_t Tag;
	
};

#endif
