#ifndef PARSING_LANGUAGE_OAKTRAITFUNCTIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTRAITFUNCTIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakTraitFunctionConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Templated;
		bool ReturnTyped;
		
	} ElementData;
	
	OakTraitFunctionConstructor ();
	~OakTraitFunctionConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakTraitFunctionConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateConstructionGroup;
	ASTConstructionGroup ParameterListConstructionGroup;
	ASTConstructionGroup ReturnTypeConstructionGroup;
	
};

#endif
