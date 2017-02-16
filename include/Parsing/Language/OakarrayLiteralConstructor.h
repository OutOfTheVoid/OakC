#ifndef PARSING_LANGUAGE_OAKARRAYLITERALCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKARRAYLITERALCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

// TODO: Implement

class OakArrayLiteralConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		bool ExplicitType;
		bool ExplicitCount;
		uint32_t ElementCount;
		
	} ElementData;
	
	OakArrayLiteralConstructor ();
	~OakArrayLiteralConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakArrayLiteralConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	ASTConstructionGroup ExpressionGroup;
	
};

#endif
