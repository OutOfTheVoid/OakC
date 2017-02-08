#ifndef PARSING_LANGUAGE_OAKNAMESPACEDTEMPLATEDTRAITNAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKNAMESPACEDTEMPLATEDTRAITNAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakNamespacedTemplatedTraitNameConstructor : public IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		std :: u32string * IdentList;
		uint32_t IdentListLength;
		
		std :: u32string Name;
		
		bool DoubleTemplateClose;
		
	} ElementData;
	
	OakNamespacedTemplatedTraitNameConstructor ();
	~OakNamespacedTemplatedTraitNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakNamespacedTemplatedTraitNameConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	
};

#endif
