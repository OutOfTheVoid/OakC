#ifndef PARSING_LANGUAGE_OAKSELFALLUSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSELFALLUSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakSelfAllusionConstructor : public virtual IASTConstructor
{
public:
	
	OakSelfAllusionConstructor ();
	~OakSelfAllusionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakSelfAllusionConstructor Instance;
	
};

#endif
