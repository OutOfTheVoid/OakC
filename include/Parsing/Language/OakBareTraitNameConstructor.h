#ifndef PARSING_LANGUAGE_OAKBARETRAITNAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKBARETRAITNAMECONSTRUCTOR_H

#include <parsing/IASTConstructor.h>

class OakBareTraitNameConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		
	} ElementData;
	
	OakBareTraitNameConstructor ();
	~OakBareTraitNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
