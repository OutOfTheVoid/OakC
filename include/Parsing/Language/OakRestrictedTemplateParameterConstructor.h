#ifndef PARSING_LANGUAGE_OAKRESTRICTEDTEMPLATEPARAMETERCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKRESTRICTEDTEMPLATEPARAMETERCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakRestrictedTemplateParameterConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool DoubleTemplateClose;
		
	} ElementData;
	
	OakRestrictedTemplateParameterConstructor ();
	~OakRestrictedTemplateParameterConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup RestrictionTraitGroup;
	
};

#endif
