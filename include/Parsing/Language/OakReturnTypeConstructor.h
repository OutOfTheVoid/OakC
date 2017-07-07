#ifndef PARSING_LANGUAGE_OAKRETURNTYPECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKRETURNTYPECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakReturnTypeConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool Mutable;
		
	} ElementData;
	
	OakReturnTypeConstructor ();
	~OakReturnTypeConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakReturnTypeConstructor Instance;
	
public:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	
};

#endif
