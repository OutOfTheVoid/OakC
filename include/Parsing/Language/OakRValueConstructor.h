#ifndef PARSING_LANGUAGE_OAKRVALUECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKRVALUECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakRValueConstructor : public virtual IASTConstructor
{
public:
	
	OakRValueConstructor ();
	~OakRValueConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	ASTConstructionGroup ValueGroup;
	
};

#endif
