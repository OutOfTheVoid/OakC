#ifndef PARSING_LANGUAGE_OAKTRAITREQUIREMENTCONSTRUCTOR_H
#define PARSING_LANGUAGE_OAKTRAITREQUIREMENTCONSTRUCTOR_H

#include <Parsing/IASTConstructor.h>
#include <Parsing/ASTConstructionGroup.h>

class OakTraitRequirementConstructor : public virtual IASTConstructor
{
public:
	
	OakTraitRequirementConstructor ();
	~OakTraitRequirementConstructor ();
	
	void TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const;
	
	static OakTraitRequirementConstructor Instance;
	
private:
	
	ASTConstructionGroup TraitRefGroup;
	
};

#endif
