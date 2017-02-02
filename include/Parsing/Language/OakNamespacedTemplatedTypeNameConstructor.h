#ifndef PARSING_LANGUAGE_OAKNAMESPACEDTEMPLATEDTYPENAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKNAMESPACEDTEMPLATEDTYPENAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakNamespacedTemplatedTypeNameConstructor : public IASTConstructor
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
	
	OakNamespacedTemplatedTypeNameConstructor ();
	~OakNamespacedTemplatedTypeNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	
};

#endif
