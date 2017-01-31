#ifndef LEXING_ILEXINGPATTERN_H
#define LEXING_ILEXINGPATTERN_H

#include <string>
#include <vector>

#include <Tokenization/Token.h>

class ILexingPattern
{
public:
	
	typedef struct ILexingInput_Struct
	{
		
		const Token ** Tokens;
		uint64_t AvailableTokens;
		
	} ILexingInput;
	
	typedef struct ILexingResult_Struct
	{
		
		ILexingResult_Struct ( std :: vector <const Token *> & TokenOutput ):
			TokenOutput ( TokenOutput )
		{
		}
		
		bool Accepted;
		uint64_t TokensConsumed;
		
		std :: vector <const Token *> & TokenOutput;
		
		bool PossibleError;
		std :: string SuggestedError;
		
	} ILexingResult;
	
	virtual inline ~ILexingPattern () {};
	
	virtual void TryPattern ( ILexingInput & Input, ILexingResult & Result ) = 0;
	
};

#endif
