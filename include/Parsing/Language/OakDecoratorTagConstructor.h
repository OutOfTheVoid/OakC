#ifndef PARSING_LANGUAGE_OAKDECORATORTAGCONSTRUCTOR
#define PARSING_LANGUAGE_OAKDECORATORTAGCONSTRUCTOR

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakDecoratorTagConstructor : public virtual IASTConstructor
{
public:
	
	enum TagKind
	{
		
		kTagKind_Simple,
		kTagKind_Parametric_1
		
	};
	
	typedef struct
	{
		
		std :: u32string ID;
		
		TagKind Kind;
		
		std :: u32string Param1;
		
	} ElementData;
	
	OakDecoratorTagConstructor ();
	~OakDecoratorTagConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakDecoratorTagConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
