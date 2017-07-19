#ifndef PARSING_LANGUAGE_OAKWHILESTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKWHILESTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakWhileStatementConstructor : public virtual IASTConstructor
{
public:
	
	OakWhileStatementConstructor ();
	~OakWhileStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakWhileStatementConstructor & Instance ();
	
private:
	
	ASTConstructionGroup ExpressionGroup;
	ASTConstructionGroup LoopLabelGroup;
	ASTConstructionGroup StatementBodyGroup;
	
};

#endif
