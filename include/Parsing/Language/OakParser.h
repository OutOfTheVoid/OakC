#ifndef PARSING_LANGUAGE_OAKPARSER_H
#define PARSING_LANGUAGE_OAKPARSER_H

#include <Parsing/ASTConstructionGroup.h>

class OakParser
{
public:
	
	static const ASTConstructionGroup & GetOakParser ();
	
private:
	
	static const ASTConstructionGroup * Instance;
	
};

#endif
