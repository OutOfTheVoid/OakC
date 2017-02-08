#ifndef PARSING_LANGUAGE_OAKASSIGNMENTOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKASSIGNMENTOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakAssignmentOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakAssignmentOperatorConstructor ();
	~OakAssignmentOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
