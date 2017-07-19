#ifndef PARSING_LANGUAGE_OAKSTRUCTLITERALMEMBERVALUECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKSTRUCTLITERALMEMBERVALUECONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakStructLiteralMemberValueConstructor : public virtual IASTConstructor
{
public:
	
	typedef struct
	{
		
		std :: u32string MemberName;
		
	} ElementData;
	
	OakStructLiteralMemberValueConstructor ();
	~OakStructLiteralMemberValueConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakStructLiteralMemberValueConstructor & Instance ();
	
private:
	
	static void ElementDataDestructor ( void * Data );
	
	ASTConstructionGroup ExpressionGroup;
	
};

#endif
