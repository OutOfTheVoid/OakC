#ifndef PARSING_LANGUAGE_OAKIMPORTSTATEMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKIMPORTSTATEMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakImportStatementConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string ImportFilenameLiteral;
		uint64_t StringLiteralTag;
		
	} ElementData;
	
	OakImportStatementConstructor ();
	~OakImportStatementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakImportStatementConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
