#ifndef PARSING_LANGUAGE_OAKBINDINGALLUSIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKBINDINGALLUSIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakBindingAllusionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DirectGlobalReference;
		
		std :: u32string * IdentList;
		uint32_t IdentListLength;
		
		std :: u32string Name;
		
	} ElementData;
	
	OakBindingAllusionConstructor ();
	~OakBindingAllusionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakBindingAllusionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
