#ifndef PARSING_LANGUAGE_OAKTEMPLATESPECIFICATIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTEMPLATESPECIFICATIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakTemplateSpecificationConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool DoubleTemplateClose;
		
	} ElementData;
	
	OakTemplateSpecificationConstructor ();
	~OakTemplateSpecificationConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup ParameterGroup;
	
};

#endif
