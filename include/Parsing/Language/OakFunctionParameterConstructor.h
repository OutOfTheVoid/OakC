#ifndef PARSING_LANGUAGE_OAKFUNCTIONPARAMETERCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKFUNCTIONPARAMETERCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakFunctionParameterConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Mut;
		
	} ElementData;
	
	OakFunctionParameterConstructor ();
	~OakFunctionParameterConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakFunctionParameterConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	
};

#endif
