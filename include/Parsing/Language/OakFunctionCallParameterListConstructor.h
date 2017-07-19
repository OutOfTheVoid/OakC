#ifndef PARSING_LANGUAGE_OAKFUNCTIONCALLPARAMETERLISTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKFUNCTIONCALLPARAMETERLISTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakFunctionCallParameterListConstructor : public virtual IASTConstructor
{
public:
	
	OakFunctionCallParameterListConstructor ();
	~OakFunctionCallParameterListConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakFunctionCallParameterListConstructor & Instance ();
	
private:
	
	ASTConstructionGroup ParameterGroup;
	
};

#endif
