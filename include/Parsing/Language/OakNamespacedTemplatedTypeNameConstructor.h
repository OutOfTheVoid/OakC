#ifndef PARSING_LANGUAGE_OAKNAMESPACEDTEMPLATEDTYPENAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKNAMESPACEDTEMPLATEDTYPENAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

#include <Utils/TestSet.h>

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
		bool TripleTemplateClose;
		
	} ElementData;
	
	OakNamespacedTemplatedTypeNameConstructor ();
	~OakNamespacedTemplatedTypeNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakNamespacedTemplatedTypeNameConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	
	static TestSet <uint64_t> AllowedKeywordTags;
	
};

#endif
