#ifndef PARSING_LANGUAGE_OAKIMPLEMENTDEFINITIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKIMPLEMENTDEFINITIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakImplementDefinitionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		std :: u32string * IdentList;
		uint32_t IdentListLength;
		
		std :: u32string Name;
		
	} ElementData;
	
	OakImplementDefinitionConstructor ();
	~OakImplementDefinitionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakImplementDefinitionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup ImplementChildrenConstructionGroup;
	
};

#endif
