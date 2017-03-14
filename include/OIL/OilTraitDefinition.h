#ifndef OIL_OILTRAITDEFINITION_H
#define OIL_OILTRAITDEFINITION_H

#include <string>

class OilTraitFunction;
class OilTemplateDefinition;

class OilTraitDefinition
{
public:
	
	OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount );
	OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTemplateDefinition * TemplateDefinition );
	~OilTraitDefinition ();
	
	uint32_t GetFunctionCount () const;
	
	const OilTraitFunction * GetTraitFunction ( uint32_t Index ) const;
	OilTraitFunction * GetTraitFunction ( uint32_t Index );
	
	bool IsTemplated () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	const std :: u32string & GetName () const;
	
private:
	
	const std :: u32string Name;
	
	OilTraitFunction ** TraitFunctions;
	uint32_t FunctionCount;
	
	OilTemplateDefinition * TemplateDefinition;
	
};

#endif
