#ifndef PARSING_LANGUAGE_OAKLOOPLABELCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKLOOPLABELCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>

class OakLoopLabelConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Label;
		
	} ElementData;
	
	OakLoopLabelConstructor ();
	~OakLoopLabelConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakLoopLabelConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
