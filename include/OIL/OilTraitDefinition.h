#ifndef OIL_OILTRAITDEFINITION_H
#define OIL_OILTRAITDEFINITION_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilTraitFunction;
class OilTraitMethod;
class OilTemplateDefinition;
class OilTypeRef;
class OilNamespaceDefinition;

class OilTraitDefinition
{
public:
	
	OilTraitDefinition ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef ** RequiredTraits, uint32_t RequiredTraitCount, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount, bool Builtin = false );
	OilTraitDefinition ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef ** RequiredTraits, uint32_t RequiredTraitCount, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount, OilTemplateDefinition * TemplateDefinition, bool Builtin = false );
	~OilTraitDefinition ();
	
	uint32_t GetRequiredTraitCount () const;
	
	const OilTypeRef * GetRequiredTrait ( uint32_t Index ) const;
	OilTypeRef * GetRequiredTrait ( uint32_t Index );
	
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
	
	bool IsBuiltin () const;
	
	const OilNamespaceDefinition * GetParentNamespace () const;
	OilNamespaceDefinition * GetParentNamespace ();
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	friend class OilNamespaceDefinition;
	
	const std :: u32string Name;
	
	OilTypeRef ** RequiredTraits;
	uint32_t RequiredTraitCount;
	
	OilTraitFunction ** TraitFunctions;
	uint32_t FunctionCount;
	
	OilTraitMethod ** TraitMethods;
	uint32_t MethodCount;
	
	OilTemplateDefinition * TemplateDefinition;
	
	bool Builtin;
	
	OilNamespaceDefinition * ParentNamespace;
	
	SourceRef Ref;
	
};

#endif
