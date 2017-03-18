#ifndef PARSING_LANGUAGE_OAKIMPLEMENTDEFINITIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKIMPLEMENTDEFINITIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakImplementDefinitionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool ImplementsTrait;
		
	} ElementData;
	
	OakImplementDefinitionConstructor ();
	~OakImplementDefinitionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakImplementDefinitionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup ImplementChildrenConstructionGroup;
	ASTConstructionGroup TypeNameGroup;
	ASTConstructionGroup TraitNameGroup;
	
};

#endif
