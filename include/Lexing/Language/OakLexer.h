#ifndef LEXER_LANGUAGE_OAKLEXER_H
#define LEXER_LANGUAGE_OAKLEXER_H

#include <Lexing/Lexer.h>

#ifndef NULL
	#define NULL 0
#endif

class OakLexer
{
public:
	
	static const Lexer & GetOakLexer ();
	
private:
	
	static const Lexer * Instance;
	
};

#endif
