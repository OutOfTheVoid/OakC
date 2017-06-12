#ifndef PARSING_LANGUAGE_OAKMATCHBRANCHCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKMATCHBRANCHCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

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
	
	OakMatchBranchConstructor ( OilLiteralExpression * LiteralMatch, OilStatementBlock * Block );
	OakMatchBranchConstructor ( OilArrayLiteral * LiteralMatch, OilStatementBlock * Block );
	OakMatchBranchConstructor ( OilStructLiteral * StructLiteralMatch, OilStatementBlock * Block );
	
	~OakMatchBranchConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakMatchBranchConstructor Instance;
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup LiteralGroup;
	ASTConstructionGroup DestructureGroup;
	ASTConstructionGroup AllusionGroup;
	ASTConstructionGroup StatementBlockGroup;
	
};

#endif
