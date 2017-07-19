#ifndef PARSING_LANGUAGE_OAKCONSTSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKCONSTSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakConstStatementConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Public;
		
	} ElementData;
	
	OakConstStatementConstructor ();
	~OakConstStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakConstStatementConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	ASTConstructionGroup InitializerValueGroup;
	
};

#endif
