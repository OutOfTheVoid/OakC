#ifndef PARSING_LANGUAGE_OAKCOMPOUNDADDITIONOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDADDITIONOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundAdditionOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundAdditionOperatorConstructor ();
	~OakCompoundAdditionOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
