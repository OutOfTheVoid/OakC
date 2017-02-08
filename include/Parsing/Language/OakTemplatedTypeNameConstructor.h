#ifndef PARSING_LANGUAGE_OAKTEMPLATEDTYPENAMECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTEMPLATEDTYPENAMECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

#include <Utils/TestSet.h>

class OakTemplatedTypeNameConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		
		bool DoubleTemplateClose;
		
	} ElementData;
	
	OakTemplatedTypeNameConstructor ();
	~OakTemplatedTypeNameConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakTemplatedTypeNameConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	
	static TestSet <uint64_t> AllowedKeywordTags;
	
};

#endif
