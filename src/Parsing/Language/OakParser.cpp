#include <Parsing/Language/OakParser.h>

#ifndef NULL
	#define NULL nullptr
#endif

#include <Parsing/Language/OakImportStatementConstructor.h>
#include <Parsing/Language/OakStructDefinitionConstructor.h>
#include <Parsing/Language/OakNamespaceDefinitionConstructor.h>
#include <Parsing/Language/OakImplementDefinitionConstructor.h>
#include <Parsing/Language/OakFunctionDefinitionConstructor.h>

const ASTConstructionGroup * OakParser :: Instance = NULL;

OakImportStatementConstructor _OakParser_OakImportStatementConstructorInstance;
OakStructDefinitionConstructor _OakParser_OakStructDefinitionConstructorInstance;
OakNamespaceDefinitionConstructor _OakParser_OakNamespaceDefinitionConstructorInstance;
OakImplementDefinitionConstructor _OakParser_OakImplementDefinitionConstructorInstance;
OakFunctionDefinitionConstructor _OakParser_OakFunctionDefinitionConstructorInstance;


const ASTConstructionGroup & OakParser :: GetOakParser ()
{
	
	if ( Instance != NULL )
		return * Instance;
	
	ASTConstructionGroup * NewParser = new ASTConstructionGroup ();
	
	// TODO: Setup parser
	NewParser -> AddConstructorCantidate ( & _OakParser_OakImportStatementConstructorInstance, 0 );
	NewParser -> AddConstructorCantidate ( & _OakParser_OakStructDefinitionConstructorInstance, 0 );
	NewParser -> AddConstructorCantidate ( & _OakParser_OakNamespaceDefinitionConstructorInstance, 0 );
	NewParser -> AddConstructorCantidate ( & _OakParser_OakImplementDefinitionConstructorInstance, 0 );
	NewParser -> AddConstructorCantidate ( & _OakParser_OakFunctionDefinitionConstructorInstance, 0 );
	
	Instance = NewParser;
	return * NewParser;
	
}
