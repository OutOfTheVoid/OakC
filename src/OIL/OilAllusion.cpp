#include <OIL/OilAllusion.h>
#include <OIL/OilTemplateSpecification.h>

#include <vector>

OilAllusion :: OilAllusion ( const SourceRef & Ref, SelfType SELF_ALLUSION ):
	NamespaceNameCount ( 0 ),
	NamespaceNameList ( NULL ),
	Name ( U"" ),
	DirectTemplateSpecification ( NULL ),
	IndirectTemplateSpecification ( NULL ),
	Target ( kAllusionTarget_Self_Unchecked ),
	ParameterTarget ( NULL ),
	Ref ( Ref )
{
	
	(void) SELF_ALLUSION;
	
}

OilAllusion :: OilAllusion ( const SourceRef & Ref, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name ):
	NamespaceNameCount ( NamespaceNameCount ),
	Name ( Name ),
	DirectTemplateSpecification ( NULL ),
	IndirectTemplateSpecification ( NULL ),
	Target ( Absolute ? kAllusionTarget_Namespaced_Absolue : kAllusionTarget_Namespaced ),
	ParameterTarget ( NULL ),
	Ref ( Ref )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilAllusion :: OilAllusion ( const SourceRef & Ref, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification ):
	NamespaceNameCount ( NamespaceNameCount ),
	Name ( Name ),
	DirectTemplateSpecification ( DirectTemplateSpecification ),
	IndirectTemplateSpecification ( NULL ),
	Target ( Absolute ? kAllusionTarget_Namespaced_Absolue_Templated : kAllusionTarget_Namespaced_Templated ),
	ParameterTarget ( NULL ),
	Ref ( Ref )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilAllusion :: OilAllusion ( const SourceRef & Ref, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification, OilTemplateSpecification * IndirectTemplateSpecification ):
	NamespaceNameCount ( NamespaceNameCount ),
	Name ( Name ),
	DirectTemplateSpecification ( DirectTemplateSpecification ),
	IndirectTemplateSpecification ( IndirectTemplateSpecification ),
	Target ( Absolute ? kAllusionTarget_Namespaced_Absolue_Templated : kAllusionTarget_Namespaced_Templated ),
	ParameterTarget ( NULL ),
	Ref ( Ref )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilAllusion :: OilAllusion ( const SourceRef & Ref, const std :: u32string & Name ):
	NamespaceNameCount ( 0 ),
	NamespaceNameList ( NULL ),
	Name ( Name ),
	DirectTemplateSpecification ( NULL ),
	IndirectTemplateSpecification ( NULL ),
	Target ( kAllusionTarget_Indeterminate ),
	ParameterTarget ( NULL ),
	Ref ( Ref )
{
}

OilAllusion :: OilAllusion ( const SourceRef & Ref, const std :: u32string & Name, OilTemplateSpecification * TemplateSpecification ):
	NamespaceNameCount ( 0 ),
	NamespaceNameList ( NULL ),
	Name ( Name ),
	DirectTemplateSpecification ( TemplateSpecification ),
	IndirectTemplateSpecification ( NULL ),
	Target ( kAllusionTarget_Indeterminate_Templated ),
	ParameterTarget ( NULL ),
	Ref ( Ref )
{
}

OilAllusion :: ~OilAllusion ()
{
	
	if ( DirectTemplateSpecification != NULL )
		delete DirectTemplateSpecification;
	
	if ( IndirectTemplateSpecification != NULL )
		delete IndirectTemplateSpecification;
	
	if ( NamespaceNameList != NULL )
		delete [] NamespaceNameList;
	
}

OilAllusion :: AllusionTarget OilAllusion :: GetTarget () const
{
	
	return Target;
	
}

bool OilAllusion :: IsResolved () const
{
	
	switch ( Target )
	{
		
		case kAllusionTarget_Namespaced:
		case kAllusionTarget_Namespaced_Absolue:
		case kAllusionTarget_Namespaced_Templated:
		case kAllusionTarget_Namespaced_Absolue_Templated:
		case kAllusionTarget_Indeterminate:
		case kAllusionTarget_Indeterminate_Templated:
		case kAllusionTarget_Self_Unchecked:
		return false;
			
		default:
		break;
		
	}
	
	return true;
	
}

void OilAllusion :: SetTargetAsSelf ()
{
	
	Target = kAllusionTarget_Self;
	
}

void OilAllusion :: SetTargetAsParameter ( OilFunctionParameter * Parameter )
{
	
	Target = kAllusionTarget_Parameter;
	ParameterTarget = Parameter;
	
}

const OilFunctionParameter * OilAllusion :: GetFunctionParameterTarget () const
{
	
	return ( Target == kAllusionTarget_Parameter ) ? ParameterTarget : NULL;
	
}

OilFunctionParameter * OilAllusion :: GetFunctionParameterTarget ()
{
	
	return ( Target == kAllusionTarget_Parameter ) ? ParameterTarget : NULL;
	
}

void OilAllusion :: SetTargetAsLocalBinding ( OilBindingStatement * Binding )
{
	
	Target = kAllusionTarget_LocalBinding;
	BindingTarget = Binding;
	
}

const OilBindingStatement * OilAllusion :: GetLocalBindingTarget () const
{
	
	return ( Target == kAllusionTarget_LocalBinding ) ? BindingTarget : NULL;
	
}

OilBindingStatement * OilAllusion :: GetLocalBindingTarget ()
{
	
	return ( Target == kAllusionTarget_LocalBinding ) ? BindingTarget : NULL;
	
}

void OilAllusion :: SetTargetAsFunction ( OilFunctionDefinition * Function )
{
	
	Target = kAllusionTarget_Function;
	FunctionTarget = Function;
	
}

void OilAllusion :: SetTargetAsNamespacedMethod ( OilMethodDefinition * Method )
{
	
	Target = kAllusionTarget_Method_Namespaced;
	MethodTarget = Method;
	
}

const OilFunctionDefinition * OilAllusion :: GetFunctionTarget () const
{
	
	return ( ( Target == kAllusionTarget_Function ) || ( Target == kAllusionTarget_Function_Namespaced ) ) ? FunctionTarget : NULL;
	
}

OilFunctionDefinition * OilAllusion :: GetFunctionTarget ()
{
	
	return ( ( Target == kAllusionTarget_Function ) || ( Target == kAllusionTarget_Function_Namespaced ) ) ? FunctionTarget : NULL;
	
}

const OilMethodDefinition * OilAllusion :: GetMethodTarget () const
{
	
	return ( ( Target == kAllusionTarget_Method ) || ( Target == kAllusionTarget_Method_Namespaced ) ) ? MethodTarget : NULL;
	
}

OilMethodDefinition * OilAllusion :: GetMethodTarget ()
{
	
	return ( ( Target == kAllusionTarget_Method ) || ( Target == kAllusionTarget_Method_Namespaced ) ) ? MethodTarget : NULL;
	
}

void OilAllusion :: SetTargetAsBinding ( OilBindingStatement * Binding )
{
	
	Target = kAllusionTarget_Binding;
	BindingTarget = Binding;
	
}

void OilAllusion :: SetTargetAsNamespacedBinding ( OilBindingStatement * Binding )
{
	
	Target = kAllusionTarget_Binding_Namespaced;
	BindingTarget = Binding;
	
}

const OilBindingStatement * OilAllusion :: GetBindingTarget () const
{
	
	return ( ( Target == kAllusionTarget_Binding ) || ( Target == kAllusionTarget_Binding_Namespaced ) ) ? BindingTarget : NULL;
	
}

OilBindingStatement * OilAllusion :: GetBindingTarget ()
{
	
	return ( ( Target == kAllusionTarget_Binding ) || ( Target == kAllusionTarget_Binding_Namespaced ) ) ? BindingTarget : NULL;
	
}

void OilAllusion :: SetTargetAsConstant ( OilConstStatement * Constant )
{
	
	Target = kAllusionTarget_Constant;
	ConstTarget = Constant;
	
}

void OilAllusion :: SetTargetAsNamespacedConst ( OilConstStatement * Constant )
{
	
	Target = kAllusionTarget_Constant_Namespaced;
	ConstTarget = Constant;
	
}

const OilConstStatement * OilAllusion :: GetConstTarget () const
{
	
	return ( ( Target == kAllusionTarget_Constant ) || ( Target == kAllusionTarget_Constant_Namespaced ) ) ? ConstTarget : NULL;
	
}

OilConstStatement * OilAllusion :: GetConstTarget ()
{
	
	return ( ( Target == kAllusionTarget_Constant ) || ( Target == kAllusionTarget_Constant_Namespaced ) ) ? ConstTarget : NULL;
	
}

void OilAllusion :: SetTargetAsEnumBranch ( OilEnum * Enum )
{
	
	Target = kAllusionTarget_EnumBranch;
	EnumTarget = Enum;
	
}

void OilAllusion :: SetTargetAsNamespacedEnumBranch ( OilEnum * Enum )
{
	
	Target = kAllusionTarget_EnumBranch_Namespaced;
	EnumTarget = Enum;
	
}

const OilEnum * OilAllusion :: GetEnumTarget () const
{
	
	return ( ( Target == kAllusionTarget_EnumBranch ) || ( Target == kAllusionTarget_EnumBranch_Namespaced ) ) ? EnumTarget : NULL;
	
}

OilEnum * OilAllusion :: GetEnumTarget ()
{
	
	return ( ( Target == kAllusionTarget_EnumBranch ) || ( Target == kAllusionTarget_EnumBranch_Namespaced ) ) ? EnumTarget : NULL;
	
}

void OilAllusion :: SetTargetAsMatchBranchValue ( OilMatchBranch * Branch )
{
	
	Target = kAllusionTarget_MatchBranchValue;
	MatchBranchTarget = Branch;
	
}

const OilMatchBranch * OilAllusion :: GetMatchBranchTarget () const
{
	
	return ( Target == kAllusionTarget_MatchBranchValue ) ? MatchBranchTarget : NULL;
	
}

OilMatchBranch * OilAllusion :: GetMatchBranchTarget ()
{
	
	return ( Target == kAllusionTarget_MatchBranchValue ) ? MatchBranchTarget : NULL;
	
}

const std :: u32string & OilAllusion :: GetName () const
{
	
	return Name;
	
}

uint32_t OilAllusion :: GetNamespaceNameCount () const
{
	
	return NamespaceNameCount;
	
}

const std :: u32string _OilAllusion_EmptyString ( U"" );

const std :: u32string & OilAllusion :: GetNamespaceName ( uint32_t Index ) const
{
	
	if ( Index >= NamespaceNameCount )
		return _OilAllusion_EmptyString;
	
	return NamespaceNameList [ Index ];
	
}

bool OilAllusion :: IsDirectlyTemplated () const
{
	
	return DirectTemplateSpecification != NULL;
	
}

bool OilAllusion :: IsIndirectlyTemplated () const
{
	
	return IndirectTemplateSpecification != NULL;
	
}

const OilTemplateSpecification * OilAllusion :: GetIndirectTemplateSpecification () const
{
	
	return IndirectTemplateSpecification;
	
}

OilTemplateSpecification * OilAllusion :: GetIndirectTemplateSpecification ()
{
	
	return IndirectTemplateSpecification;
	
}

const OilTemplateSpecification * OilAllusion :: GetDirectTemplateSpecification () const
{
	
	return DirectTemplateSpecification;
	
}

OilTemplateSpecification * OilAllusion :: GetDirectTemplateSpecification ()
{
	
	return DirectTemplateSpecification;
	
}

bool OilAllusion :: IsConstant () const
{
	
	// FOR NOW
	return false;
	
}

IOilPrimary :: PrimaryType OilAllusion :: GetPrimaryType () const
{
	
	return kPrimaryType_Allusion;
	
}

const SourceRef & OilAllusion :: GetSourceRef () const
{
	
	return Ref;
	
}
