#ifndef PARSING_LANGUAGE_OAKFUNCTIONPARAMETERLISTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKFUNCTIONPARAMETERLISTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakFunctionParameterListConstructor : public virtual IASTConstructor
{
public:
	
	OakFunctionParameterListConstructor ();
	~OakFunctionParameterListConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakFunctionParameterListConstructor Instance;
	
private:
	
	ASTConstructionGroup ParameterConstructionGroup;
	
};

#endif
