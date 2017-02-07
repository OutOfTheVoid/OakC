#ifndef PARSING_LANGUAGE_OAKPRIMARYEXPRESSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKPRIMARYEXPRESSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakPrimaryExpressionParser : public virtual IASTConstructor
{
public:
	
	OakPrimaryExpressionParser ();
	~OakPrimaryExpressionParser ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup PrimaryGroup;
	
};

#endif
