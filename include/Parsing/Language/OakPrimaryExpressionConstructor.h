#ifndef PARSING_LANGUAGE_OAKPRIMARYEXPRESSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKPRIMARYEXPRESSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakPrimaryExpressionConstructor : public virtual IASTConstructor
{
public:
	
	OakPrimaryExpressionConstructor ();
	~OakPrimaryExpressionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakPrimaryExpressionConstructor & Instance ();
	
private:
	
	ASTConstructionGroup PrimaryGroup;
	
};

#endif
