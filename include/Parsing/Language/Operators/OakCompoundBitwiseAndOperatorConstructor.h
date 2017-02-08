#ifndef PARSING_LANGUAGE_OAKCOMPOUNDBITWISEANDOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDBITWISEANDOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundBitwiseAndOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundBitwiseAndOperatorConstructor ();
	~OakCompoundBitwiseAndOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
