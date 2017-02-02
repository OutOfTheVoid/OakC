#ifndef PARSING_LANGUAGE_OAKNAMESPACEDTYPENAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKNAMESPACEDTYPENAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakNamespacedTraitNameConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		std :: u32string * IdentList;
		uint32_t IdentListLength;
		
		std :: u32string Name;
		
	} ElementData;
	
	OakNamespacedTraitNameConstructor ();
	~OakNamespacedTraitNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
