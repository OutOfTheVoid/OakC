#ifndef PARSING_LANGUAGE_OAKSELFPARAMETERCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSELFPARAMETERCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakSelfParameterConstructor : public virtual IASTConstructor
{
public:
	
	OakSelfParameterConstructor ();
	~OakSelfParameterConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakSelfParameterConstructor Instance;
	
};

#endif
