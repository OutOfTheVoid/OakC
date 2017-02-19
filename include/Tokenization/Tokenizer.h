#ifndef TOKENIZATION_TOKENIZER_H
#define TOKENIZATION_TOKENIZER_H

#include <Tokenization/Token.h>
#include <Tokenization/ITokenSplitRule.h>

#include <string>
#include <vector>

class Tokenizer
{
public:
	
	/// Constructor.
	Tokenizer ();
	
	/// Destructor. Deallocates all split rules
	~Tokenizer ();
	
	/**
	 * @brief Adds a token splitting rule.
	 * @details Adds a rule at the specified precedence level, where 0 is highest priority (and the first checked ruleset).
	 * 
	 * @param Rule The rule to be added
	 * @param Precedence The precedence of the rule
	 */
	void AddSplitRule ( ITokenSplitRule * Rule, uint32_t Precedence );
	
	/**
	 * @brief Tokenize a string.
	 * @details Tokenizes a string according to the defined ruleset.
	 * 
	 * @param Source The source string to be tokenized
	 * @param TokenList The vector of tokens to fill sequentially with tokens
	 * @param ErrorFileName The name of the file to be used for reporting errors (has no effect on tokenization)
	 * 
	 * @return Whether or not the tokenization succeeded without errors
	 */
	bool TokenizeString ( const std :: u32string & Source, std :: vector <const Token *> & TokenList, const std :: string & ErrorFileName, CompilationUnit * SourceUnit ) const;
	
private:
	
	std :: vector <std :: vector <ITokenSplitRule *>> Rules;
	
};

#endif
