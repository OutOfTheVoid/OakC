#ifndef PARSING_LANGUAGE_OAKSELFPARAMETERPOINTERCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSELFPARAMETERPOINTERCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakSelfParameterReferenceConstructor : public virtual IASTConstructor
{
public:
	
	OakSelfParameterReferenceConstructor ();
	~OakSelfParameterReferenceConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakSelfParameterReferenceConstructor & Instance ();
	
private:
	
	ASTConstructionGroup SelfParamGroup;
	
};

#endif
