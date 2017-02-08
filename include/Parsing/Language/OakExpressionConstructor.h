#ifndef PARSING_LANGUAGE_OAKEXPRESSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKEXPRESSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakExpressionConstructor : public virtual IASTConstructor
{
public:
	
	OakExpressionConstructor ();
	~OakExpressionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakExpressionConstructor Instance;
	
private:
	
	ASTConstructionGroup SubExpressionGroup;
	
};

#endif
