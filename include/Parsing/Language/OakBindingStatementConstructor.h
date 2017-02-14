#ifndef PARSING_LANGUAGE_OAKBINDINGSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKBINDINGSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakBindingStatementConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string Name;
		bool Initialized;
		bool Mutable;
		
	} ElementData;
	
	OakBindingStatementConstructor ();
	~OakBindingStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakBindingStatementConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup TypeGroup;
	ASTConstructionGroup InitializerValueGroup;
	
};

#endif
