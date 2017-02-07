#ifndef PARSING_LANGUAGE_OAKEXPRESSIONSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKEXPRESSIONSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakExpressionStatementConstructor : public virtual IASTConstructor
{
public:
	
	OakExpressionStatementConstructor ();
	~OakExpressionStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RValueGroup;
	
};

#endif
