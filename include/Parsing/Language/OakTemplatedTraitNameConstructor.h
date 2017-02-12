#ifndef PARSING_LANGUAGE_OAKTEMPLATEDTRAITNAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTEMPLATEDTRAITNAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakTemplatedTraitNameConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		
		bool DoubleTemplateClose;
		bool TripleTemplateClose;
		
	} ElementData;
	
	OakTemplatedTraitNameConstructor ();
	~OakTemplatedTraitNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakTemplatedTraitNameConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	
};

#endif
