#ifndef PARSING_LANGUAGE_OAKNAMESPACEDEFINITIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKNAMESPACEDEFINITIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakNamespaceDefinitionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		std :: u32string * IdentList;
		uint32_t IdentListLength;
		
		std :: u32string Name;
		
	} ElementData;
	
	OakNamespaceDefinitionConstructor ();
	~OakNamespaceDefinitionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakNamespaceDefinitionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup NamespaceChildrenGroup;
	
};

#endif
