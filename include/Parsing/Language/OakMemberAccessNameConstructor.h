#ifndef PARSING_LANGUAGE_OAKMEMBERACCESSNAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKMEMBERACCESSNAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakMemberAccessNameConstructor : public virtual IASTConstructor
{
public:
	
	OakMemberAccessNameConstructor ();
	~OakMemberAccessNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakMemberAccessNameConstructor Instance;
	
};

#endif
