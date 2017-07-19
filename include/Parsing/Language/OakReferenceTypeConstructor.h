#ifndef PARSING_LANGUAGE_OAKREFERENCETYPECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKREFERENCETYPECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakReferenceTypeConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool Templated;
		bool DoubleTemplateClose;
		bool TripleTemplateClose;
		
	} ElementData;
	
	OakReferenceTypeConstructor ();
	~OakReferenceTypeConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakReferenceTypeConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	
};

#endif
