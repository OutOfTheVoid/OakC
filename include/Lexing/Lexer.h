#ifndef LEXING_LEXER_H
#define LEXING_LEXER_H

#include <string>
#include <vector>

#include <Lexing/ILexingPattern.h>

#include <Tokenization/Token.h>

class Lexer
{
public:
	
	Lexer ();
	~Lexer ();
	
	void AddPattern ( ILexingPattern * Pattern );
	
	bool LexTokens ( std :: vector <const Token *> & TokensIn, std :: vector <const Token *> & TokensOut ) const;
	
private:
	
	std :: vector <ILexingPattern *> Patterns;
	
};

#endif
