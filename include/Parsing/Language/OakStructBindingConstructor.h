#ifndef PARSING_LANGUAGE_OAKSTRUCTBINDINGCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSTRUCTBINDINGCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakStructBindingConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		
		bool Public;
		
	} ElementData;
	
	OakStructBindingConstructor ();
	~OakStructBindingConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakStructBindingConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	
};

#endif
