#ifndef PARSING_LANGUAGE_OAKALLUSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKALLUSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakAllusionConstructor : public virtual IASTConstructor
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
	
	OakAllusionConstructor ();
	~OakAllusionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakAllusionConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateSpecificationGroup;
	
};

#endif
