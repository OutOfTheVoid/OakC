#ifndef PARSING_LANGUAGE_OAKMEMBERDESTRUCTURECONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKMEMBERDESTRUCTURECONSTRUCTOR_H

#include <string>

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakMemberDestructureConstructor : public virtual IASTConstructor
{
public:
	
	enum DestructureType
	{
		
		kDestructureType_Ignored,
		kDestructureType_Named,
		kDestrucutreType_SubDestructure
		
	};
	
	typedef struct 
	{
		
		DestructureType Type;
		
		std :: u32string MemberName;
		std :: u32string BindingName;
		
	} ElementData;
	
	OakMemberDestructureConstructor ();
	~OakMemberDestructureConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakMemberDestructureConstructor & Instance ();
	
private:
	
	ASTConstructionGroup DestructureGroup;
	
	static void ElementDataDestructor ( void * Data );
	
};

#endif
