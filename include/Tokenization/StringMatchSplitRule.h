#ifndef TOKENIZATION_STRINGMATCHSPLITRULE_H
#define TOKENIZATION_STRINGMATCHSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class StringMatchSplitRule : public virtual ITokenSplitRule
{
public:
	
	StringMatchSplitRule ( const std :: u32string & String, uint64_t Tag );
	~StringMatchSplitRule ();
	
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
private:
	
	const std :: u32string String;
	
	uint64_t Tag;
	
};

#endif
