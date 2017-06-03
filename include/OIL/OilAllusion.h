#ifndef OIL_OILALLUSION_H
#define OIL_OILALLUSION_H

#include <string>

#include <OIL/IOilPrimary.h>

#include <Tokenization/SourceRef.h>

class OilTemplateSpecification;

class OilFunctionParameter;
class OilBindingStatement;
class OilTypeRef;
class OilFunctionDefinition;
class OilConstStatement;

class OilAllusion : public virtual IOilPrimary
{
public:
	
	typedef enum
	{
		
		
		kAllusionTarget_Namespaced,
		kAllusionTarget_Namespaced_Absolue,
		kAllusionTarget_Namespaced_Templated,
		kAllusionTarget_Namespaced_Absolue_Templated,
		kAllusionTarget_Self_Unchecked,
		
		kAllusionTarget_Indeterminate,
		kAllusionTarget_Indeterminate_Templated,
		
		kAllusionTarget_Parameter,
		kAllusionTarget_Function,
		kAllusionTarget_LocalBinding,
		kAllusionTarget_Binding,
		kAllusionTarget_Constant,
		kAllusionTarget_Self,
		
		kAllusionTarget_Function_Templated,
		
	} AllusionTarget;
	
	typedef enum
	{
		
		SELF_ALLUSION
		
	} SelfType;
	
	OilAllusion ( const SourceRef & Ref, SelfType SELF_ALLUSION );
	OilAllusion ( const SourceRef & Ref, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name );
	OilAllusion ( const SourceRef & Ref, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification );
	OilAllusion ( const SourceRef & Ref, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification, OilTemplateSpecification * IndirectTemplateSpecification );
	OilAllusion ( const SourceRef & Ref, const std :: u32string & Name );
	OilAllusion ( const SourceRef & Ref, const std :: u32string & Name, OilTemplateSpecification * TemplateSpecification );
	~OilAllusion ();
	
	AllusionTarget GetTarget () const;
	
	bool IsResolved () const;
	
	void SetTargetAsSelf ();
	void SetTargetAsParameter ( OilFunctionParameter * Parameter );
	void SetTargetAsLocalBinding ( OilBindingStatement * Binding );
	void SetTargetAsFunction ( OilFunctionDefinition * Function );
	void SetTargetAsBinding ( OilBindingStatement * Binding );
	void SetTargetAsConstant ( OilConstStatement * Constant );
	
	void SetTargetAsTemplatedFunction ( OilFunctionDefinition * Function );
	
	const OilFunctionParameter * GetFunctionParameterTarget () const;
	OilFunctionParameter * GetFunctionParameterTarget ();
	
	const OilBindingStatement * GetLocalBindingTarget () const;
	OilBindingStatement * GetLocalBindingTarget ();
	
	const OilFunctionDefinition * GetFunctionTarget () const;
	OilFunctionDefinition * GetFunctionTarget ();
	
	const OilBindingStatement * GetBindingTarget () const;
	OilBindingStatement * GetBindingTarget ();
	
	const OilConstStatement * GetConstTarget () const;
	OilConstStatement * GetConstTarget ();
	
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
	PrimaryType GetPrimaryType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	uint32_t NamespaceNameCount;
	std :: u32string * NamespaceNameList;
	const std :: u32string Name;
	
	OilTemplateSpecification * DirectTemplateSpecification;
	OilTemplateSpecification * IndirectTemplateSpecification;
	
	AllusionTarget Target;
	
	union
	{
		
		OilFunctionParameter * ParameterTarget;
		OilBindingStatement * BindingTarget;
		OilFunctionDefinition * FunctionTarget;
		OilConstStatement * ConstTarget;
		
	};
	
	SourceRef Ref;
	
};

#endif
