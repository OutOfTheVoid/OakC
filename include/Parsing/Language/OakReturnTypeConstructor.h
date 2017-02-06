#ifndef PARSING_LANGUAGE_OAKRETURNTYPECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKRETURNTYPECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakReturnTypeConstructor : public virtual IASTConstructor
{
public:
	
	OakReturnTypeConstructor ();
	~OakReturnTypeConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
public:
	
	ASTConstructionGroup TypeGroup;
	
};

#endif
