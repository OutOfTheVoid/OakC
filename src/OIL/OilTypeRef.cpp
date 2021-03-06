#include <OIL/OilTypeRef.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTemplateSpecification.h>

OilTypeRef :: OilTypeRef ( const SourceRef & Ref, const OilTypeRef & CopyFrom ):
	Mode ( CopyFrom.Mode ),
	Name ( CopyFrom.Name ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	SubType ( ( CopyFrom.SubType != NULL ) ? new OilTypeRef ( CopyFrom.SubType -> GetSourceRef (), * CopyFrom.SubType ) : NULL ),
	Flags ( CopyFrom.Flags ),
	ResolvedAsTrait ( CopyFrom.ResolvedAsTrait ),
	ResolvedAsTemplateParam ( CopyFrom.ResolvedAsTemplateParam ),
	ResolvedAsSelf ( CopyFrom.ResolvedAsSelf ),
	ResolvedType ( CopyFrom.ResolvedType ),
	Ref ( Ref )
{
}

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
	ResolvedAsSelf ( false ),
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
	ResolvedAsSelf ( false ),
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
	ResolvedAsSelf ( false ),
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
	ResolvedAsSelf ( false ),
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
	ResolvedAsSelf ( false ),
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
	ResolvedAsSelf ( false ),
	ResolvedType ( NULL ),
	Ref ( Ref )
{
	
	(void) VType;
	
}

OilTypeRef :: ~OilTypeRef ()
{
	
	if ( NamespaceNameList != NULL )
		delete [] NamespaceNameList;
	
	if ( ( Mode != kTypeMode_Direct ) && ( SubType != NULL ) )
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

void OilTypeRef :: SetTemplateSpecification ( OilTemplateSpecification * TemplateSpecification )
{
	
	if ( this -> TemplateSpecification != NULL )
		delete this -> TemplateSpecification;
	
	this -> TemplateSpecification = TemplateSpecification;
	
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
	else if ( ResolvedAsTemplateParam )
		return true;
	else if ( ResolvedAsSelf )
		return true;
		
	return ResolvedType != NULL;
	
}

void OilTypeRef :: SetResolvedTypeDefinition ( OilTypeDefinition * TypeDefinition )
{
	
	ResolvedType = TypeDefinition;
	ResolvedAsTrait = false;
	ResolvedAsTemplateParam = false;
	ResolvedAsSelf = false;
	
}


void OilTypeRef :: SetResolvedTraitDefinition ( OilTraitDefinition * TraitDefinition )
{
	
	ResolvedTrait = TraitDefinition;
	ResolvedAsTrait = true;
	ResolvedAsTemplateParam = false;
	ResolvedAsSelf = false;
	
}

void OilTypeRef :: SetResolvedTemplateParamName ()
{
	
	ResolvedAsTrait = false;
	ResolvedAsTemplateParam = true;
	ResolvedAsSelf = false;
	
}

void OilTypeRef :: SetResolvedAsSelf ( OilTypeDefinition * SelfType )
{
	
	ResolvedType = SelfType;
	
	ResolvedAsTrait = false;
	ResolvedAsTemplateParam = false;
	ResolvedAsSelf = true;
	
}

void OilTypeRef ::  SetResolvedAsSelfAbstract ()
{
	
	ResolvedAsTrait = false;
	ResolvedAsTemplateParam = false;
	ResolvedAsSelf = true;
	
}

void OilTypeRef :: SetResolvedTypeWithTemplateSpec ( OilTypeDefinition * Type, OilTemplateSpecification * Spec )
{
	
	SetTemplateSpecification ( Spec );
	
	ResolvedType = Type;
	ResolvedAsTrait = false;
	ResolvedAsTemplateParam = false;
	ResolvedAsSelf = false;
	
}

bool OilTypeRef :: IsResolvedAsType () const
{
	
	return ( ! ( ResolvedAsTrait || ResolvedAsTemplateParam || ResolvedAsSelf ) ) && ( ResolvedType != NULL );
	
}

bool OilTypeRef :: IsResolvedAsTrait () const
{
	
	return ResolvedAsTrait && ( ResolvedTrait != NULL );
	
}

bool OilTypeRef :: IsResolvedAsSelf () const
{
	
	return ResolvedAsSelf && ( ResolvedType != NULL );
	
}

bool OilTypeRef :: IsResolvedAsSelfAbstract () const
{
	
	return ResolvedAsSelf && ( ResolvedType == NULL );
	
}

bool OilTypeRef :: IsResolvedAsTemplateParam () const
{
	
	return ResolvedAsTemplateParam;
	
}

const OilTypeDefinition * OilTypeRef :: GetResolvedTypeDefinition () const
{
	
	return ( IsResolvedAsType () || IsResolvedAsSelf () ) ? ResolvedType : NULL;
	
}

OilTypeDefinition * OilTypeRef :: GetResolvedTypeDefinition ()
{
	
	return ( IsResolvedAsType () || IsResolvedAsSelf () ) ? ResolvedType : NULL;
	
}

const OilTraitDefinition * OilTypeRef :: GetResolvedTraitDefinition () const
{
	
	return IsResolvedAsTrait () ? ResolvedTrait : NULL;
	
}

OilTraitDefinition * OilTypeRef :: GetResolvedTraitDefinition ()
{
	
	return IsResolvedAsTrait () ? ResolvedTrait : NULL;
	
}

void OilTypeRef :: SetResolvedVoid ()
{
	
	Mode = kTypeMode_Void;
	
}

const SourceRef & OilTypeRef :: GetSourceRef () const
{
	
	return Ref;
	
}
