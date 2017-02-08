#ifndef PARSING_LANGUAGE_OAKLONESEMICOLONCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKLONESEMICOLONCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakLoneSemicolonConstructor : public virtual IASTConstructor
{
public:
	
	OakLoneSemicolonConstructor ();
	~OakLoneSemicolonConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakLoneSemicolonConstructor Instance;
	
};

#endif
