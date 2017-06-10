#ifndef PARSING_LANGUAGE_OAKSTRUCTDESTRUCTURECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSTRUCTDESTRUCTURECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakStructDestructureConstructor : public virtual IASTConstructor
{
public:
	
	OakStructDestructureConstructor ();
	~OakStructDestructureConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakStructDestructureConstructor Instance;
	
private:
	
	ASTConstructionGroup MemberDestructGroup;
	
};

#endif
