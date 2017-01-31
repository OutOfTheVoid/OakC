#ifndef TOKENIZATION_ITOKENSPLITRULE_H
#define TOKENIZATION_ITOKENSPLITRULE_H

#include <stdint.h>

#include <string>

class ITokenSplitRule
{
public:
	
	typedef struct
	{
		
		uint64_t Tag;
		uint64_t AuxTag;
		
		uint32_t SplitLength;
		
		bool Accepted;
		
		bool PossibleError;
		std :: string SuggestedError;
		
	} TokenSplitResult;
	
	static const uint64_t kTag_Default = 0;
	static const uint64_t kAuxTag_Default = 0;
	
	virtual inline ~ITokenSplitRule () {};
	
	/**
	 * @brief Checks the rule agains the source string. (pure virtual)
	 * 
	 * @details Checks to see whether the source follows the rule for forming a token. (Splitting the source.) If the rule matches, "Accepted" is set to true and "SplitLength" is set to the token length in [Result]. Additionally, Tag may optionally be assigned away from it's default value for later usage in the lexer. If the rule did not match, but came close, "PossibleError" may be set to indicate a possible code error, and "SuggestedError" may be set to suggest the cause of the error.
	 * 
	 * @param Source The source text to be checked by the rule
	 * @param Offset The offset to begin the rule check (NOTE: the rule must begin here, source charachters may not be skipped for any reason)
	 * @param Result The result out parameter to be set indicating the result of the test
	 */
	virtual void TrySplit ( const std :: u32string & Source, uint64_t Offset, TokenSplitResult & Result ) = 0;
	
};

#endif
