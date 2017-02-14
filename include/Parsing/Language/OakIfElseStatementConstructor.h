#ifndef PARSING_LANGUAGE_OAKIFELSESTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKIFELSESTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakIfElseStatementConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		uint32_t ElseIfCount;
		bool Else;
		
	} ElementData;
	
	OakIfElseStatementConstructor ();
	~OakIfElseStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakIfElseStatementConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup ExpressionGroup;
	ASTConstructionGroup StatementBodyGroup;
	
};

#endif
