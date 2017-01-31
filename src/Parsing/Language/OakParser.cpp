#include <Parsing/Language/OakParser.h>

#ifndef NULL
	#define NULL nullptr
#endif

#include <Parsing/Language/OakImportStatementConstructor.h>
#include <Parsing/Language/OakStructDefinitionConstructor.h>

const ASTConstructionGroup * OakParser :: Instance = NULL;

const ASTConstructionGroup & OakParser :: GetOakParser ()
{
	
	if ( Instance != NULL )
		return * Instance;
	
	ASTConstructionGroup * NewParser = new ASTConstructionGroup ();
	
	// TODO: Setup parser
	NewParser -> AddConstructorCantidate ( new OakImportStatementConstructor (), 0 );
	NewParser -> AddConstructorCantidate ( new OakStructDefinitionConstructor (), 0 );
	
	
	Instance = NewParser;
	return * NewParser;
	
}
