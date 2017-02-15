#ifndef PARSING_LANGUAGE_OAKLOOPSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKLOOPSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakLoopStatementConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool Labeled;
		
	} ElementData;
	
	OakLoopStatementConstructor ();
	~OakLoopStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakLoopStatementConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup LoopLabelGroup;
	ASTConstructionGroup StatementBodyGroup;
	
};

#endif
