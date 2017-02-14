#ifndef PARSING_LANGUAGE_OAKBINDINGALLUSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKBINDINGALLUSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakBindingAllusionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		
		bool Templated;
		ASTElement * TemplateSpecificationElement;
		
	} AllusionName;
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		AllusionName * IdentList;
		uint32_t IdentListLength;
		
	} ElementData;
	
	OakBindingAllusionConstructor ();
	~OakBindingAllusionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakBindingAllusionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateSpecificationGroup;
	
};

#endif
