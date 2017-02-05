#ifndef PARSING_LANGUAGE_OAKFUNCTIONPARAMETERLISTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKFUNCTIONPARAMETERLISTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakFunctionParameterListConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		
	} ElementData;
	
	OakFunctionParameterListConstructor ();
	~OakFunctionParameterListConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup ParameterConstructionGroup;
	
};

#endif
