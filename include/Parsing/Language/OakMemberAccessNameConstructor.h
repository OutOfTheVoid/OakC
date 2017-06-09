#ifndef PARSING_LANGUAGE_OAKMEMBERACCESSNAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKMEMBERACCESSNAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakMemberAccessNameConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Templated;
		
	} ElementData;
	
	OakMemberAccessNameConstructor ();
	~OakMemberAccessNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakMemberAccessNameConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	
};

#endif
