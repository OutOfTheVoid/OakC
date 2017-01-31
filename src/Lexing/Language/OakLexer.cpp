#include <Lexing/Language/OakLexer.h>

#include <Lexing/Language/OakKeywordLexingPattern.h>
#include <Lexing/Language/OakWhitespaceAndCommentRemovalLexingPattern.h>

const Lexer * OakLexer :: Instance = NULL;

const Lexer & OakLexer :: GetOakLexer ()
{
	
	if ( Instance != NULL )
		return * Instance;
		
	Lexer * NewLexer = new Lexer ();
	
	NewLexer -> AddPattern ( new OakKeywordLexingPattern () );
	NewLexer -> AddPattern ( new OakWhitespaceAndCommentRemovalLexingPattern () );
		
	Instance = NewLexer;
	return * Instance;
	
}
