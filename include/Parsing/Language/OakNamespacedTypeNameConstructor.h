#ifndef PARSING_LANGUAGE_OAKNAMESPACEDTYPENAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKNAMESPACEDTYPENAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakNamespacedTypeNameConstructor : public IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		std :: u32string * IdentList;
		uint32_t IdentListLength;
		
		std :: u32string Name;
		
	} ElementData;
	
	OakNamespacedTypeNameConstructor ();
	~OakNamespacedTypeNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
