#ifndef PARSING_LANGUAGE_OAKCOMPOUNDMULTIPLYOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDMULTIPLYOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundMultiplyOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundMultiplyOperatorConstructor ();
	~OakCompoundMultiplyOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
