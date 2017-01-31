#ifndef PARSING_LANGUAGE_OAKBARETYPENAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKBARETYPENAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

#include <Utils/TestSet.h>

class OakBareTypeNameConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string TypeName;
		uint64_t TypeTag;
		
	} ElementData;
	
	OakBareTypeNameConstructor ();
	~OakBareTypeNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	static TestSet <uint64_t> AllowedKeywordTags;
	
};

#endif
