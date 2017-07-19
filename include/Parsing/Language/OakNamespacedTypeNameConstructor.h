#ifndef PARSING_LANGUAGE_OAKNAMESPACEDTYPENAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKNAMESPACEDTYPENAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

#include <Utils/TestSet.h>

class OakNamespacedTypeNameConstructor : public IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		std :: u32string * IdentList;
		uint32_t IdentListLength;
		
		std :: u32string TypeName;
		
	} ElementData;
	
	OakNamespacedTypeNameConstructor ();
	~OakNamespacedTypeNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakNamespacedTypeNameConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	static TestSet <uint64_t> AllowedKeywordTags;
	
};

#endif
