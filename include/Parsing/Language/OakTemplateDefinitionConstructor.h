#ifndef PARSING_LANGUAGE_OAKTEMPLATEDEFINITIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTEMPLATEDEFINITIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakTemplateDefinitionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DoubleTemplateClose;
		
	} ElementData;
	
	OakTemplateDefinitionConstructor ();
	~OakTemplateDefinitionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakTemplateDefinitionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup ParameterGroup;
	
};

#endif
