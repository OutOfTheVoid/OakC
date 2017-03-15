#include <OIL/OilAllusion.h>
#include <OIL/OilTemplateSpecification.h>

#include <vector>

OilAllusion :: OilAllusion ( SelfType SELF_ALLUSION ):
	NamespaceNameCount ( 0 ),
	NamespaceNameList ( NULL ),
	Name ( U"" ),
	DirectTemplateSpecification ( NULL ),
	IndirectTemplateSpecification ( NULL ),
	Target ( kAllusionTarget_Self )
{
	
	(void) SELF_ALLUSION;
	
}

OilAllusion :: OilAllusion ( const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name ):
	NamespaceNameCount ( NamespaceNameCount ),
	Name ( Name ),
	DirectTemplateSpecification ( NULL ),
	IndirectTemplateSpecification ( NULL ),
	Target ( Absolute ? kAllusionTarget_Namespaced_Absolue : kAllusionTarget_Namespaced )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilAllusion :: OilAllusion ( const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification ):
	NamespaceNameCount ( NamespaceNameCount ),
	Name ( Name ),
	DirectTemplateSpecification ( DirectTemplateSpecification ),
	IndirectTemplateSpecification ( NULL ),
	Target ( Absolute ? kAllusionTarget_Namespaced_Absolue_Templated : kAllusionTarget_Namespaced_Templated )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilAllusion :: OilAllusion ( const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, bool Absolute, const std :: u32string Name, OilTemplateSpecification * DirectTemplateSpecification, OilTemplateSpecification * IndirectTemplateSpecification ):
	NamespaceNameCount ( NamespaceNameCount ),
	Name ( Name ),
	DirectTemplateSpecification ( DirectTemplateSpecification ),
	IndirectTemplateSpecification ( IndirectTemplateSpecification ),
	Target ( Absolute ? kAllusionTarget_Namespaced_Absolue_Templated : kAllusionTarget_Namespaced_Templated )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilAllusion :: OilAllusion ( const std :: u32string & Name ):
	NamespaceNameCount ( 0 ),
	NamespaceNameList ( NULL ),
	Name ( Name ),
	DirectTemplateSpecification ( NULL ),
	IndirectTemplateSpecification ( NULL ),
	Target ( kAllusionTarget_Indeterminate )
{
}

OilAllusion :: OilAllusion ( const std :: u32string & Name, OilTemplateSpecification * TemplateSpecification ):
	NamespaceNameCount ( 0 ),
	NamespaceNameList ( NULL ),
	Name ( Name ),
	DirectTemplateSpecification ( TemplateSpecification ),
	IndirectTemplateSpecification ( NULL ),
	Target ( kAllusionTarget_Indeterminate_Templated )
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

void OilAllusion :: SetTarget ( AllusionTarget Target )
{
	
	this -> Target = Target;
	
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
