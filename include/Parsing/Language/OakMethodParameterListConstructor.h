#ifndef PARSING_LANGUAGE_OAKMETHODPARAMETERLISTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKMETHODPARAMETERLISTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakMethodParameterListConstructor : public virtual IASTConstructor
{
public:
	
	OakMethodParameterListConstructor ();
	~OakMethodParameterListConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakMethodParameterListConstructor Instance;
	
private:
	
	ASTConstructionGroup SelfParameterConstructionGroup;
	ASTConstructionGroup ParameterConstructionGroup;
	
};

#endif
