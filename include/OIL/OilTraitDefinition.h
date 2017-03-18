#ifndef OIL_OILTRAITDEFINITION_H
#define OIL_OILTRAITDEFINITION_H

#include <string>

class OilTraitFunction;
class OilTraitMethod;
class OilTemplateDefinition;

class OilTraitDefinition
{
public:
	
	OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount );
	OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount, OilTemplateDefinition * TemplateDefinition );
	~OilTraitDefinition ();
	
	uint32_t GetFunctionCount () const;
	
	const OilTraitFunction * GetTraitFunction ( uint32_t Index ) const;
	OilTraitFunction * GetTraitFunction ( uint32_t Index );
	
	uint32_t GetMethodCount () const;
	
	const OilTraitMethod * GetTraitMethod ( uint32_t Index ) const;
	OilTraitMethod * GetTraitMethod ( uint32_t Index );
	
	bool IsTemplated () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	const std :: u32string & GetName () const;
	
private:
	
	const std :: u32string Name;
	
	OilTraitFunction ** TraitFunctions;
	uint32_t FunctionCount;
	
	OilTraitMethod ** TraitMethods;
	uint32_t MethodCount;
	
	OilTemplateDefinition * TemplateDefinition;
	
};

#endif
