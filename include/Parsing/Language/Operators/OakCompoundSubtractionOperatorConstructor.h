#ifndef PARSING_LANGUAGE_OAKCOMPOUNDSUBTRACTIONOPERATORCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCOMPOUNDSUBTRACTIONOPERATORCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakCompoundSubtractionOperatorConstructor : public virtual IASTConstructor
{
public:
	
	OakCompoundSubtractionOperatorConstructor ();
	~OakCompoundSubtractionOperatorConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup RightExpressionGroup;
	ASTConstructionGroup LeftExpressionGroup;
	
};

#endif
