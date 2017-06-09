#ifndef PARSING_LANGUAGE_OAKENUMBRANCHCONSTRUCTOR
#define PARSING_LANGUAGE_OAKENUMBRANCHCONSTRUCTOR

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

#include <string>

class OakEnumBranchConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool HasData;
		
	} ElementData;
	
	OakEnumBranchConstructor ();
	~OakEnumBranchConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakEnumBranchConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	
};

#endif