#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateSpecification.h>

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, RefFlag Flags ):
	Name ( Name ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( NULL ),
	Flags ( Flags )
{
}

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, RefFlag Flags ):
	Name ( Name ),
	NamespaceNameCount ( NamespaceNameCount ),
	TemplateSpecification ( NULL ),
	Flags ( Flags )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, OilTemplateSpecification * TemplateSpecification, RefFlag Flags ):
	Name ( Name ),
	NamespaceNameList ( NULL ),
	NamespaceNameCount ( 0 ),
	TemplateSpecification ( TemplateSpecification ),
	Flags ( Flags )
{
}

OilTypeRef :: OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags ):
	Name ( Name ),
	NamespaceNameCount ( NamespaceNameCount ),
	TemplateSpecification ( TemplateSpecification ),
	Flags ( Flags )
{
	
	this -> NamespaceNameList = new std :: u32string [ NamespaceNameCount ];
	
	for ( uint32_t I = 0; I < NamespaceNameCount; I ++ )
		this -> NamespaceNameList [ I ] = NamespaceNameList [ I ];
	
}

OilTypeRef :: ~OilTypeRef ()
{
	
	if ( NamespaceNameList != NULL )
		delete [] NamespaceNameList;
	
}

bool OilTypeRef :: IsNamespaced ()
{
	
	return NamespaceNameCount != 0;
	
}

bool OilTypeRef :: IsTemplated ()
{
	
	return TemplateSpecification != NULL;
	
}

const std :: u32string & OilTypeRef :: GetName ()
{
	
	return Name;
	
}

uint32_t OilTypeRef :: GetNamespaceNameCount ()
{
	
	return NamespaceNameCount;
	
}

const std :: u32string _OilTypeRef_EmptyNSName;

const std :: u32string & OilTypeRef :: GetNamespaceName ( uint32_t Index )
{
	
	if ( Index >= NamespaceNameCount )
		return NamespaceNameList [ Index ];
	
	return _OilTypeRef_EmptyNSName;
	
}

OilTemplateSpecification * OilTypeRef :: GetTemplateSpecification ()
{
	
	return TemplateSpecification;
	
}

OilTypeRef :: RefFlag OilTypeRef :: GetFlags ()
{
	
	return Flags;
	
}
