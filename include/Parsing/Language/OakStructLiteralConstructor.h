#ifndef PARSING_LANGUAGE_OAKSTRUCTLITERALCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSTRUCTLITERALCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakStructLiteralConstructor : public virtual IASTConstructor
{
public:
	
	OakStructLiteralConstructor ();
	~OakStructLiteralConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakStructLiteralConstructor Instance;
	
private:
	
	ASTConstructionGroup StructTypeGroup;
	ASTConstructionGroup MemberValueGroup;
	
};

#endif
