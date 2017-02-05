#ifndef PARSING_LANGUAGE_OAKFUNCTIONDEFINITIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKFUNCTIONDEFINITIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakFunctionDefinitionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Templated;
		
	} ElementData;
	
	OakFunctionDefinitionConstructor ();
	~OakFunctionDefinitionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateConstructionGroup;
	ASTConstructionGroup ParameterListConstructionGroup;
	ASTConstructionGroup FunctionBodyConstructionGroup;
	
};

#endif
