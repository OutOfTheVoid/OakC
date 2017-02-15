#ifndef PARSING_LANGUAGE_OAKBREAKSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKBREAKSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakBreakStatementConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool Labeled;
		
	} ElementData;
	
	OakBreakStatementConstructor ();
	~OakBreakStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakBreakStatementConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup LabelGroup;
	
};

#endif
