#ifndef TOKENIZATION_LANGUAGE_FLOATINGPOINTSPLITRULE_H
#define TOKENIZATION_LANGUAGE_FLOATINGPOINTSPLITRULE_H

#include <Tokenization/ITokenSplitRule.h>

#include <string>
#include <string.h>

class OakFloatingPointSplitRule : public virtual ITokenSplitRule
{
public:
	
	/// Constructor. (no-op)
	OakFloatingPointSplitRule ();
	
	/// Destructor. (no-op)
	~OakFloatingPointSplitRule ();
	
	/// Implements ITokenSplitRule :: TrySplit.
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
private:
	
	bool TestExponent ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result );
	bool TestFloatTypeSpecifier ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result );
	
	bool TestExponentHex ( const std :: u32string & Source, uint64_t Offset, uint64_t Length, TokenSplitResult & Result );
	
};

#endif
