#ifndef PARSING_LANGUAGE_OAKPARENTHESIZEDEXPRESSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKPARENTHESIZEDEXPRESSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakParenthesizedExpressionConstructor : public virtual IASTConstructor
{
public:
	
	OakParenthesizedExpressionConstructor ();
	~OakParenthesizedExpressionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup ExpressionGroup;
	
};

#endif
