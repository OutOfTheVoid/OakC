#ifndef PARSING_LANGUAGE_OAKENUMCONSTRUCTOR
#define PARSING_LANGUAGE_OAKENUMCONSTRUCTOR

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

#include <string>

class OakEnumConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Templated;
		
	} ElementData;
	
	OakEnumConstructor ();
	~OakEnumConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakEnumConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TemplateGroup;
	ASTConstructionGroup EnumBodyGroup;
	
};

#endif
