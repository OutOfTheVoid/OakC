#ifndef PARSING_LANGUAGE_OAKSTRUCTDEFINITIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSTRUCTDEFINITIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakStructDefinitionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Templated;
		
	} ElementData;
	
	OakStructDefinitionConstructor ();
	~OakStructDefinitionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakStructDefinitionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateConstructionGroup;
	ASTConstructionGroup StructBodyConstructionGroup;
	
};

#endif
