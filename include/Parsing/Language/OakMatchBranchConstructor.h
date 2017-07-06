#ifndef PARSING_LANGUAGE_OAKMATCHBRANCHCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKMATCHBRANCHCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OilLiteralExpression;
class OilArrayLiteral;
class OilStructLiteral;
class OilStatementBlock;

class OakMatchBranchConstructor : public virtual IASTConstructor
{
public:
	
	enum BranchType
	{
		
		kBranchType_LiteralMatch,
		kBranchType_BasicAllusionMatch,
		kBranchType_ValueAllusionMatch,
		kBranchType_DestructureMatch
		
	};
	
	typedef struct
	{
		
		BranchType Type;
		
		std :: u32string BindingName;
		
	} ElementData;
	
	OakMatchBranchConstructor ();
	~OakMatchBranchConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakMatchBranchConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup LiteralGroup;
	ASTConstructionGroup DestructureGroup;
	ASTConstructionGroup AllusionGroup;
	ASTConstructionGroup StatementBlockGroup; // macpeers
	
};

#endif
