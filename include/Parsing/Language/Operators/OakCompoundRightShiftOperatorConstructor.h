#ifndef PARSING_LANGUAGE_OAKCOMPOUNDRIGHTSHIFTOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDRIGHTSHIFTOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundRightShiftOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundRightShiftOperatorConstructor ();
	~OakCompoundRightShiftOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
