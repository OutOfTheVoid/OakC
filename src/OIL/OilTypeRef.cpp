#include <OIL/OilTypeRef.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTemplateSpecification.h>

OilTypeRef :: OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	SubType ( NULL ),
	Flags ( Flags ),
	ResolvedAsTrait ( false ),
	ResolvedAsTemplateParam ( false ),
	ResolvedType ( NULL ),
	Ref ( Ref )
{
}

OilTypeRef :: OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameCount ( NamespaceNameCount ),
	TemplateSpecification ( NULL ),
	SubType ( NULL ),
	Flags ( Flags ),
	ResolvedAsTrait ( false ),
	ResolvedAsTemplateParam ( false ),
	ResolvedType ( NULL ),
	Ref ( Ref )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilTypeRef :: OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, OilTemplateSpecification * TemplateSpecification, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( TemplateSpecification ),
	SubType ( NULL ),
	Flags ( Flags ),
	ResolvedAsTrait ( false ),
	ResolvedAsTemplateParam ( false ),
	ResolvedType ( NULL ),
	Ref ( Ref )
{
}

OilTypeRef :: OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * TemplateSpecification, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameCount ( NamespaceNameCount ),
	TemplateSpecification ( TemplateSpecification ),
	SubType ( NULL ),
	Flags ( Flags ),
	ResolvedAsTrait ( false ),
	ResolvedAsTemplateParam ( false ),
	ResolvedType ( NULL ),
	Ref ( Ref )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilTypeRef :: OilTypeRef ( const SourceRef & Ref, ReferenceMarkerType RMType, OilTypeRef * SubType, RefFlag Flags ):
	Mode ( kTypeMode_Reference ),
	Name ( U"" ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	SubType ( SubType ),
	Flags ( Flags ),
	ResolvedAsTrait ( false ),
	ResolvedAsTemplateParam ( false ),
	ResolvedType ( NULL ),
	Ref ( Ref )
{
	
	(void) RMType;
	
}

OilTypeRef :: OilTypeRef ( const SourceRef & Ref, VoidMarkerType VType ):
	Mode ( kTypeMode_Void ),
	Name ( U"" ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	SubType ( NULL ),
	Flags ( 0 ),
	ResolvedAsTrait ( false ),
	ResolvedAsTemplateParam ( false ),
	ResolvedType ( NULL ),
	Ref ( Ref )
{
	
	(void) VType;
	
}

OilTypeRef :: ~OilTypeRef ()
{
	
	if ( NamespaceNameList != NULL )
		delete [] NamespaceNameList;
	
	if ( Mode != kTypeMode_Direct )
		delete SubType;
	
}

bool OilTypeRef :: IsDirectType () const
{
	
	return Mode == kTypeMode_Direct;
	
}

bool OilTypeRef :: IsVoid () const
{
	
	return Mode == kTypeMode_Void;
	
}

bool OilTypeRef :: IsNamespaced () const
{
	
	return NamespaceNameCount != 0;
	
}

bool OilTypeRef :: IsTemplated () const
{
	
	return TemplateSpecification != NULL;
	
}

const std :: u32string & OilTypeRef :: GetName () const
{
	
	return Name;
	
}

uint32_t OilTypeRef :: GetNamespaceNameCount () const
{
	
	return NamespaceNameCount;
	
}

const std :: u32string _OilTypeRef_EmptyNSName;

const std :: u32string & OilTypeRef :: GetNamespaceName ( uint32_t Index ) const
{
	
	if ( Index < NamespaceNameCount )
		return NamespaceNameList [ Index ];
	
	return _OilTypeRef_EmptyNSName;
	
}

OilTemplateSpecification * OilTypeRef :: GetTemplateSpecification ()
{
	
	return TemplateSpecification;
	
}

const OilTemplateSpecification * OilTypeRef :: GetTemplateSpecification () const
{
	
	return TemplateSpecification;
	
}

OilTypeRef :: RefFlag OilTypeRef :: GetFlags () const
{
	
	return Flags;
	
}

OilTypeRef * OilTypeRef :: GetSubType ()
{
	
	return SubType;
	
}

const OilTypeRef * OilTypeRef :: GetSubType () const
{
	
	return SubType;
	
}

bool OilTypeRef :: IsResolved () const
{
	
	if ( Mode != kTypeMode_Direct )
	{
		
		if ( Mode == kTypeMode_Void )
			return true;
		
		return SubType -> IsResolved ();
		
	}
	
	if ( ResolvedAsTrait )
		return ResolvedTrait != NULL;
	else
	{
		
		if ( ResolvedAsTemplateParam )
			return true;
		
		return ResolvedType != NULL;
		
	}
	
}

void OilTypeRef :: SetResolvedTypeDefinition ( OilTypeDefinition * TypeDefinition )
{
	
	ResolvedType = TypeDefinition;
	ResolvedAsTrait = false;
	ResolvedAsTemplateParam = false;
	
}


void OilTypeRef :: SetResolvedTraitDefinition ( OilTraitDefinition * TraitDefinition )
{
	
	ResolvedTrait = TraitDefinition;
	ResolvedAsTrait = true;
	ResolvedAsTemplateParam = false;
	
}

void OilTypeRef :: SetResolvedTemplateParamName ()
{
	
	ResolvedAsTrait = false;
	ResolvedAsTemplateParam = true;
	
}

bool OilTypeRef :: IsResolvedAsTrait () const
{
	
	return ResolvedAsTrait;
	
}

bool OilTypeRef :: IsResolvedAsTemplateParam () const
{
	
	return ( ! ResolvedAsTrait ) && ResolvedAsTemplateParam;
	
}

OilTypeDefinition * OilTypeRef :: GetResolvedTypeDefinition () const
{
	
	return ResolvedAsTrait ? NULL : ResolvedAsTemplateParam ? NULL :ResolvedType;
	
}

OilTypeDefinition * OilTypeRef :: GetResolvedTypeDefinition ()
{
	
	return ResolvedAsTrait ? NULL : ResolvedAsTemplateParam ? NULL : ResolvedType;
	
}

OilTraitDefinition * OilTypeRef :: GetResolvedTraitDefinition () const
{
	
	return ResolvedAsTrait ? ResolvedTrait : NULL;
	
}

OilTraitDefinition * OilTypeRef :: GetResolvedTraitDefinition ()
{
	
	return ResolvedAsTrait ? ResolvedTrait : NULL;
	
}

const SourceRef & OilTypeRef :: GetSourceRef () const
{
	
	return Ref;
	
}
