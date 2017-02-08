#ifndef PARSING_LANGUAGE_OAKCOMPOUNDDIVISIONOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDDIVISIONOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundDivisionOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundDivisionOperatorConstructor ();
	~OakCompoundDivisionOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
