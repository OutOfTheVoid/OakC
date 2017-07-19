#ifndef PARSING_LANGUAGE_OAKDOWHILESTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKDOWHILESTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakDoWhileStatementConstructor : public virtual IASTConstructor
{
public:
	
	OakDoWhileStatementConstructor ();
	~OakDoWhileStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakDoWhileStatementConstructor & Instance ();
	
private:
	
	ASTConstructionGroup ExpressionGroup;
	ASTConstructionGroup StatementBodyGroup;
	ASTConstructionGroup LoopLabelGroup;
	
};

#endif
