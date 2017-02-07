#ifndef PARSING_LANGUAGE_OAKLITERALRVALUECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKLITERALRVALUECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakLiteralExpressionConstructor : public virtual IASTConstructor
{
public:
	
	OakLiteralExpressionConstructor ();
	~OakLiteralExpressionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
};

#endif
