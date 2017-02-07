#ifndef PARSING_LANGUAGE_OAKLITERALRVALUECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKLITERALRVALUECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakLiteralRValueConstructor : public virtual IASTConstructor
{
public:
	
	OakLiteralRValueConstructor ();
	~OakLiteralRValueConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
};

#endif
