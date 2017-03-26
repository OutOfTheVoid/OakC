#ifndef PARSING_LANGUAGE_OAKVOIDTYPECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKVOIDTYPECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakVoidTypeConstructor : public virtual IASTConstructor
{
public:
	
	OakVoidTypeConstructor ();
	~OakVoidTypeConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakVoidTypeConstructor Instance;
	
};

#endif
