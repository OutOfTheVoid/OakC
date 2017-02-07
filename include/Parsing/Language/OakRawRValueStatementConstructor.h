#ifndef PARSING_LANGUAGE_OAKRAWRVALUESTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKRAWRVALUESTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakRawRValueStatementConstructor : public virtual IASTConstructor
{
public:
	
	OakRawRValueStatementConstructor ();
	~OakRawRValueStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RValueGroup;
	
};

#endif
