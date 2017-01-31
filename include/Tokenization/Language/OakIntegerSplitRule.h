#ifndef TOKENIZATION_LANGUAGE_OAKINTEGERLITERALSPLITRULE_H
#define TOKENIZATION_LANGUAGE_OAKINTEGERLITERALSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

class OakIntegerSplitRule : public virtual ITokenSplitRule
{
public:
	
	OakIntegerSplitRule ();
	~OakIntegerSplitRule ();
	
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
private:
	
	bool TestTypeSpecifier ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result );
	
};

#endif
