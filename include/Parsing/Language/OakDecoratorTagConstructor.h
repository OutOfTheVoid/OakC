#ifndef PARSING_LANGUAGE_OAKDECORATORTAGCONSTRUCTOR
#define PARSING_LANGUAGE_OAKDECORATORTAGCONSTRUCTOR

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakDecoratorTagConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string ID;
		
	} ElementData;
	
	OakDecoratorTagConstructor ();
	~OakDecoratorTagConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakDecoratorTagConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
