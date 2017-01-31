#ifndef TOKENIZATION_LANGUAGE_OAKTOKENIZER_H
#define TOKENIZATION_LANGUAGE_OAKTOKENIZER_H

#include <Tokenization/Tokenizer.h>

class OakTokenizer
{
public:
	
	/**
	 * @brief Gets the singleton instance of the oak language tokenizer.
	 * 
	 * @details Gets the singleton instance of the oak language tokenizer with associated rules. If it hasn't been constructed yet, this method will construct it.
	 * 
	 * @return A constant reference to the Tokenizer instance
	 */
	static const Tokenizer & GetOakTokenizer ();
	
private:
	
	static const Tokenizer * OakTokenizerInstance;
	
};

#endif
