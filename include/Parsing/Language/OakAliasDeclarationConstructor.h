#ifndef PARSING_LANGUAGE_OAKALIASDECLARATIONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKALIASDECLARATIONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakAliasDeclarationConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string NewName;
		
		bool Templated;
		
	} ElementData;
	
	OakAliasDeclarationConstructor ();
	~OakAliasDeclarationConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakAliasDeclarationConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	ASTConstructionGroup TypeGroup;
	
};

#endif
