#ifndef OIL_OILALLUSION_H
#define OIL_OILALLUSION_H

#include <string>

#include <OIL/IOilPrimary.h>

class OilTemplateSpecification;

class OilAllusion : public virtual IOilPrimary
{
public:
	
	typedef enum
	{
		
		kAllusionTarget_Indeterminate,
		kAllusionTarget_Contextual,
		kAllusionTarget_Contextual_Templated,
		kAllusionTarget_Scoped,
		kAllusionTarget_Parameter,
		kAllusionTarget_Namespaced,
		kAllusionTarget_Namespaced_Absolue,
		kAllusionTarget_Namespaced_Templated,
		kAllusionTarget_Namespaced_Absolue_Templated,
		kAllusionTarget_Self
		
	} AllusionTarget;
	
	typedef enum
	{
		
		SELF_ALLUSION
		
	} SelfType;
	
	OilAllusion ( SelfType SELF_ALLUSION );
	OilAllusion ( const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name );
	OilAllusion ( const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification );
	OilAllusion ( const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification, OilTemplateSpecification * IndirectTemplateSpecification );
	OilAllusion ( const std :: u32string & Name );
	OilAllusion ( const std :: u32string & Name, OilTemplateSpecification * TemplateSpecification );
	~OilAllusion ();
	
	AllusionTarget GetTarget () const;
	void SetTarget ( AllusionTarget Target );
	
	const std :: u32string & GetName () const;
	
	uint32_t GetNamespaceNameCount () const;
	const std :: u32string & GetNamespaceName ( uint32_t Index ) const;
	
	bool IsDirectlyTemplated ();
	bool IsIndirectlyTemplated ();
	
	const OilTemplateSpecification * GetIndirectTemplateSpecification () const;
	OilTemplateSpecification * GetIndirectTemplateSpecification ();
	
	const OilTemplateSpecification * GetDirectTemplateSpecification () const;
	OilTemplateSpecification * GetDirectTemplateSpecification ();
	
	bool IsConstant () const;
	
private:
	
	uint32_t NamespaceNameCount;
	std :: u32string * NamespaceNameList;
	const std :: u32string Name;
	
	OilTemplateSpecification * DirectTemplateSpecification;
	OilTemplateSpecification * IndirectTemplateSpecification;
	
	AllusionTarget Target;
	
};

#endif
