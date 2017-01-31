#ifndef TOKENIZATION_LANGUAGE_OAKIDENTIFIERSPLITRULE_H
#define TOKENIZATION_LANGUAGE_OAKIDENTIFIERSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

#include <StringUtils/CharTestSet.h>

class OakIdentifierSplitRule : public virtual ITokenSplitRule
{
public:
	
	OakIdentifierSplitRule ();
	~OakIdentifierSplitRule ();
	
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
private:
	
	CharTestSet StartSet;
	CharTestSet ContinueSet;
	
	std :: u32string StartChars;
	std :: u32string ContinueChars;
	
};

#endif
