#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateSpecification.h>

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	SubType ( NULL ),
	Flags ( Flags )
{
}

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameCount ( NamespaceNameCount ),
	TemplateSpecification ( NULL ),
	SubType ( NULL ),
	Flags ( Flags )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, OilTemplateSpecification * TemplateSpecification, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( TemplateSpecification ),
	SubType ( NULL ),
	Flags ( Flags )
{
}

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * TemplateSpecification, RefFlag Flags ):
	Mode ( kTypeMode_Direct ),
	Name ( Name ),
	NamespaceNameCount ( NamespaceNameCount ),
	TemplateSpecification ( TemplateSpecification ),
	SubType ( NULL ),
	Flags ( Flags )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilTypeRef :: OilTypeRef ( ReferenceMarkerType RMType, OilTypeRef * SubType, RefFlag Flags ):
	Mode ( kTypeMode_Reference ),
	Name ( U"" ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	SubType ( SubType ),
	Flags ( Flags )
{
	
	(void) RMType;
	
}

OilTypeRef :: OilTypeRef ( PointerMarkerType PMType, OilTypeRef * SubType, RefFlag Flags ):
	Mode ( kTypeMode_Pointer ),
	Name ( U"" ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	SubType ( SubType ),
	Flags ( Flags )
{
	
	(void) PMType;
	
}

OilTypeRef :: OilTypeRef ( VoidMarkerType VType ):
	Mode ( kTypeMode_Void ),
	Name ( U"" ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	SubType ( NULL ),
	Flags ( 0 )
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

bool OilTypeRef :: IsReference () const
{
	
	return Mode == kTypeMode_Reference;
	
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
