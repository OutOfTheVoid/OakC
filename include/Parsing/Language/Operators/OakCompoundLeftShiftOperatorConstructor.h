#ifndef PARSING_LANGUAGE_OAKCOMPOUNDLEFTSHIFTOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDLEFTSHIFTOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundLeftShiftOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundLeftShiftOperatorConstructor ();
	~OakCompoundLeftShiftOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
