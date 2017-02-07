#ifndef PARSING_LANGUAGE_OAKIMPORTSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKIMPORTSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakIgnoreStatementConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string IgnoredName;
		
	} ElementData;
	
	OakIgnoreStatementConstructor ();
	~OakIgnoreStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
