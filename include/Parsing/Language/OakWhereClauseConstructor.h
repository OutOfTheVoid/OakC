#ifndef PARSING_LANGUAGE_OAKWHERECLAUSECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKWHERECLAUSECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakWhereClauseConstructor : public virtual IASTConstructor
{
public:
	
	OakWhereClauseConstructor ();
	~OakWhereClauseConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakWhereClauseConstructor Instance;
	
private:
	
	ASTConstructionGroup TemplateGroup;
	
};

#endif
