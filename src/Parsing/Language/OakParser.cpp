#include <Parsing/Language/OakParser.h>

#ifndef NULL
	#define NULL nullptr
#endif

#include <Parsing/Language/OakImportStatementConstructor.h>
#include <Parsing/Language/OakStructDefinitionConstructor.h>
#include <Parsing/Language/OakTraitDefinitionConstructor.h>
#include <Parsing/Language/OakNamespaceDefinitionConstructor.h>
#include <Parsing/Language/OakImplementDefinitionConstructor.h>
#include <Parsing/Language/OakFunctionDefinitionConstructor.h>
#include <Parsing/Language/OakLoneSemicolonConstructor.h>
#include <Parsing/Language/OakBindingStatementConstructor.h>

const ASTConstructionGroup * OakParser :: Instance = NULL;

OakImportStatementConstructor _OakParser_OakImportStatementConstructorInstance;
OakStructDefinitionConstructor _OakParser_OakStructDefinitionConstructorInstance;
OakTraitDefinitionConstructor _OakParser_OakTraitDefinitionConstructorInstance;
OakNamespaceDefinitionConstructor _OakParser_OakNamespaceDefinitionConstructorInstance;
OakImplementDefinitionConstructor _OakParser_OakImplementDefinitionConstructorInstance;
OakFunctionDefinitionConstructor _OakParser_OakFunctionDefinitionConstructorInstance;
OakLoneSemicolonConstructor _OakParser_OakLoneSemicolonConstructorInstance;


const ASTConstructionGroup & OakParser :: GetOakParser ()
{
	
	if ( Instance != NULL )
		return * Instance;
	
	ASTConstructionGroup * NewParser = new ASTConstructionGroup ();
	
	NewParser -> AddConstructorCantidate ( & OakImportStatementConstructor :: Instance, 0 );
	NewParser -> AddConstructorCantidate ( & OakStructDefinitionConstructor :: Instance, 0 );
	NewParser -> AddConstructorCantidate ( & OakTraitDefinitionConstructor :: Instance, 0 );
	NewParser -> AddConstructorCantidate ( & OakNamespaceDefinitionConstructor :: Instance, 0 );
	NewParser -> AddConstructorCantidate ( & OakImplementDefinitionConstructor :: Instance, 0 );
	NewParser -> AddConstructorCantidate ( & OakFunctionDefinitionConstructor :: Instance, 0 );
	NewParser -> AddConstructorCantidate ( & OakBindingStatementConstructor :: Instance, 0 );
	
	// Just in case
	NewParser -> AddConstructorCantidate ( & OakLoneSemicolonConstructor :: Instance, 1 );
	
	Instance = NewParser;
	return * NewParser;
	
}
