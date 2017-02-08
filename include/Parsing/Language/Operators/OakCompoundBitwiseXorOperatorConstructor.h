#ifndef PARSING_LANGUAGE_OAKCOMPOUNDBITWISEXOROPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDBITWISEXOROPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundBitwiseXorOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundBitwiseXorOperatorConstructor ();
	~OakCompoundBitwiseXorOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
