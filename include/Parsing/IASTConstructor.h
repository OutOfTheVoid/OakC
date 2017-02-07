#ifndef PARSING_IASTCONSTRUCTOR_H
#define PARSING_IASTCONSTRUCTOR_H

#include <Tokenization/Token.h>

#include <stdint.h>
#include <string>

#include <Parsing/ASTElement.h>

class IASTConstructor
{
public:
	
	typedef struct
	{
		
		const Token ** Tokens;
		uint64_t AvailableTokenCount;
		
		const ASTElement * ParentElement;
		
	} ASTConstructionInput;
	
	typedef struct
	{
		
		bool Accepted;
		uint64_t TokensConsumed;
		
		ASTElement * ConstructedElement;
		
		bool Error;
		std :: string ErrorSuggestion;
		const Token * ErrorProvokingToken;
		
	} ASTConstructionOutput;
	
	virtual inline ~IASTConstructor () {};
	
	virtual void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const = 0;
	
};

#endif
