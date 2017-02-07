#ifndef PARSING_LANGUAGE_OAKRETURNSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKRETURNSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakReturnStatementConstructor : public virtual IASTConstructor
{
public:
	
	OakReturnStatementConstructor ();
	~OakReturnStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup ExpressionGroup;
	
};

#endif
