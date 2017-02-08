#ifndef PARSING_LANGUAGE_OAKCOMPOUNDMODULUSOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDMODULUSOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundModulusOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundModulusOperatorConstructor ();
	~OakCompoundModulusOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
