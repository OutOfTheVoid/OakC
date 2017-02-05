#ifndef PARSING_LANGUAGE_OAKSELFPARAMETERPOINTERCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSELFPARAMETERPOINTERCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakSelfParameterPointerConstructor : public virtual IASTConstructor
{
public:
	
	OakSelfParameterPointerConstructor ();
	~OakSelfParameterPointerConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup SelfParamGroup;
	
};

#endif
