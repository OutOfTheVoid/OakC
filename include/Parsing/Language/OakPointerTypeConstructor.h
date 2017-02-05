#ifndef PARSING_LANGUAGE_OAKPOINTERTYPECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKPOINTERTYPECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakPointerTypeConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool Templated;
		
	} ElementData;
	
	OakPointerTypeConstructor ();
	~OakPointerTypeConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	
};

#endif
