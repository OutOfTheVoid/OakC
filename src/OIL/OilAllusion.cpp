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

void OilAllusion :: SetTargetAsTemplatedFunction ( OilFunctionDefinition * Function )
{
	
	Target = kAllusionTarget_Function_Templated;
	FunctionTarget = Function;
	
}

const OilFunctionDefinition * OilAllusion :: GetFunctionTarget () const
{
	
	return ( Target == kAllusionTarget_Function ) ? FunctionTarget : NULL;
	
}

OilFunctionDefinition * OilAllusion :: GetFunctionTarget ()
{
	
	return ( Target == kAllusionTarget_Function ) ? FunctionTarget : NULL;
	
}

void OilAllusion :: SetTargetAsBinding ( OilBindingStatement * Binding )
{
	
	Target = kAllusionTarget_Binding;
	BindingTarget = Binding;
	
}

const OilBindingStatement * OilAllusion :: GetBindingTarget () const
{
	
	return ( Target == kAllusionTarget_Binding ) ? BindingTarget : NULL;
	
}

OilBindingStatement * OilAllusion :: GetBindingTarget ()
{
	
	return ( Target == kAllusionTarget_Binding ) ? BindingTarget : NULL;
	
}

void OilAllusion :: SetTargetAsConstant ( OilConstStatement * Constant )
{
	
	Target = kAllusionTarget_Constant;
	ConstTarget = Constant;
	
}

const OilConstStatement * OilAllusion :: GetConstTarget () const
{
	
	return ( Target == kAllusionTarget_Constant ) ? ConstTarget : NULL;
	
}

OilConstStatement * OilAllusion :: GetConstTarget ()
{
	
	return ( Target == kAllusionTarget_Constant ) ? ConstTarget : NULL;
	
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

bool OilAllusion :: IsDirectlyTemplated ()
{
	
	return DirectTemplateSpecification != NULL;
	
}

bool OilAllusion :: IsIndirectlyTemplated ()
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
