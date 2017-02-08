#ifndef PARSING_LANGUAGE_OAKUNRESTRICTEDTEMPLATEPARAMETERCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKUNRESTRICTEDTEMPLATEPARAMETERCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakUnrestrictedTemplateParameterConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		
	} ElementData;
	
	OakUnrestrictedTemplateParameterConstructor ();
	~OakUnrestrictedTemplateParameterConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakUnrestrictedTemplateParameterConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
