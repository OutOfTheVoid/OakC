#ifndef LANGUAGE_PARSING_OAKOPERATOREXPRESSIONCONSTRUCTOR_H
#define LANGUAGE_PARSING_OAKOPERATOREXPRESSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakOperatorExpressionConstructor : public IASTConstructor
{
public:
	
	OakOperatorExpressionConstructor ();
	~OakOperatorExpressionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakOperatorExpressionConstructor & Instance ();
	
private:
	
	ASTConstructionGroup PrimaryGroup;
	ASTConstructionGroup ExpressionGroup;
	
};

#endif
