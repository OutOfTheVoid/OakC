#ifndef PARSING_LANGUAGE_OAKFUNCTIONBODYCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKFUNCTIONBODYCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakStatementBlockConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool IsBlock;
		
	} ElementData;
	
	OakStatementBlockConstructor ();
	~OakStatementBlockConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakStatementBlockConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup StatementGroup;
	
};

#endif
