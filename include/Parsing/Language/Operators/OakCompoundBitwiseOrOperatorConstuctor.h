#ifndef PARSING_LANGUAGE_OAKCOMPOUNDBITWISEOROPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDBITWISEOROPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundBitwiseOrOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundBitwiseOrOperatorConstructor ();
	~OakCompoundBitwiseOrOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
