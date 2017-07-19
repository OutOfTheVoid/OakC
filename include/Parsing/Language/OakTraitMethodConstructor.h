#ifndef PARSING_LANGUAGE_OAKTRAITMETHODCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTRAITMETHODCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakTraitMethodConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Templated;
		bool ReturnTyped;
		
	} ElementData;
	
	OakTraitMethodConstructor ();
	~OakTraitMethodConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakTraitMethodConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateConstructionGroup;
	ASTConstructionGroup ParameterListConstructionGroup;
	ASTConstructionGroup ReturnTypeConstructionGroup;
	
};

#endif
