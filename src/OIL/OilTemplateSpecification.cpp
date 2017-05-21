#include <OIL/OilTemplateSpecification.h>

#include <OIL/OilTypeRef.h>

OilTemplateSpecification :: OilTemplateSpecification ( const SourceRef & Ref, OilTypeRef ** TypeRefList, uint32_t TypeRefCount ):
	TypeRefCount ( TypeRefCount ),
	Ref ( Ref )
{
	
	this -> TypeRefList = new OilTypeRef * [ TypeRefCount ];
	
	for ( uint32_t I = 0; I < TypeRefCount; I ++ )
		this -> TypeRefList [ I ] = TypeRefList [ I ];
	
}

OilTemplateSpecification :: ~OilTemplateSpecification ()
{
	
	for ( uint32_t I = 0; I < TypeRefCount; I ++ )
		delete TypeRefList [ I ];
	
	delete [] TypeRefList;
	
}

uint32_t OilTemplateSpecification :: GetTypeRefCount () const
{
	
	return TypeRefCount;
	
}

OilTypeRef * OilTemplateSpecification :: GetTypeRef ( uint32_t Index )
{
	
	if ( Index > TypeRefCount )
		return NULL;
	
	return TypeRefList [ Index ];
	
}

const OilTypeRef * OilTemplateSpecification :: GetTypeRef ( uint32_t Index ) const
{
	
	if ( Index > TypeRefCount )
		return NULL;
	
	return TypeRefList [ Index ];
	
}

const SourceRef & OilTemplateSpecification :: GetSourceRef () const
{
	
	return Ref;
	
}
