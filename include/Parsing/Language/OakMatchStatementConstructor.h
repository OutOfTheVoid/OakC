#ifndef PARSING_LANGUAGE_OAKMATCHSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKMATCHSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakMatchStatementConstructor : public virtual IASTConstructor
{
public:
	
	OakMatchStatementConstructor ();
	~OakMatchStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakMatchStatementConstructor & Instance ();
	
private:
	
	ASTConstructionGroup ExpressionGroup;
	ASTConstructionGroup MatchesGroup;
	
};

#endif
