#ifndef TOKENIZATION_CHARMATCHRUNSPLITRULE_H
#define TOKENIZATION_CHARMATCHRUNSPLITRULE_H

#include <string>
#include <stdint.h>

#include <Tokenization/ITokenSplitRule.h>

#include <StringUtils/CharTestSet.h>

class CharMatchRunSplitRule : public virtual ITokenSplitRule
{
public:
	
	/**
	 * @brief Constructs a CharMatchRunSplitRule
	 * @details Constructs a CharMatchRunSplitRule with the specified character set.
	 * 
	 * @param CharList The UTF32 char array containing all valid chars
	 * @param CharCount The number of chars in the array
	 * @param FreeOnDestruct Whether or not the passed array should be freed with delete[] when the CharMatchRunSplitRule constructor is called
	 */
	CharMatchRunSplitRule ( const char32_t CharList [], uint32_t CharCount, bool FreeOnDestruct, uint64_t Tag );
	
	/// Destructor
	~CharMatchRunSplitRule ();
	
	/// Implementation of ITokenSplitRule :: TrySplit
	void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result );
	
private:
	
	CharTestSet CharList;
	
	uint64_t Tag;
	
};

#endif
