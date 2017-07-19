#ifndef PARSING_LANGUAGE_OAKTRAITDEFINITIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTRAITDEFINITIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakTraitDefinitionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Templated;
		bool Empty;
		
	} ElementData;
	
	OakTraitDefinitionConstructor ();
	~OakTraitDefinitionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakTraitDefinitionConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateConstructionGroup;
	ASTConstructionGroup TraitBodyConstructionGroup;
	
};

#endif
