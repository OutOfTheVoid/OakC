#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilTypeRef.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTemplateDefinitionParameter :: OilTemplateDefinitionParameter ( const SourceRef & Ref, const std :: u32string & Name ):
	Name ( Name ),
	RestrictionTypes ( NULL ),
	RestrictionCount ( 0 ),
	Ref ( Ref )
{
}

OilTemplateDefinitionParameter :: OilTemplateDefinitionParameter ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef ** RestrictionTypes, uint32_t RestrictionCount ):
	Name ( Name ),
	RestrictionCount ( RestrictionCount ),
	Ref ( Ref )
{
	
	this -> RestrictionTypes = new OilTypeRef * [ RestrictionCount ];
	
	for ( uint32_t I = 0; I < RestrictionCount; I ++ )
		this -> RestrictionTypes [ I ] = RestrictionTypes [ I ];
	
}

OilTemplateDefinitionParameter :: ~OilTemplateDefinitionParameter ()
{
	
	if ( RestrictionTypes != NULL )
	{
		
		for ( uint32_t I = 0; I < RestrictionCount; I ++ )
			delete RestrictionTypes [ I ];
		
		delete [] RestrictionTypes;
		
	}
	
}

const std :: u32string & OilTemplateDefinitionParameter :: GetName () const
{
	
	return Name;
	
}

bool OilTemplateDefinitionParameter :: IsRestricted () const
{
	
	return RestrictionTypes != NULL;
	
}

uint32_t OilTemplateDefinitionParameter :: GetRestrictionCount () const
{
	
	return RestrictionCount;
	
}

OilTypeRef * OilTemplateDefinitionParameter :: GetRestriction ( uint32_t Index )
{
	
	if ( Index >= RestrictionCount )
		return NULL;
	
	return RestrictionTypes [ Index ];
	
}

const OilTypeRef * OilTemplateDefinitionParameter :: GetRestriction ( uint32_t Index ) const
{
	
	if ( Index >= RestrictionCount )
		return NULL;
	
	return RestrictionTypes [ Index ];
	
}

const SourceRef & OilTemplateDefinitionParameter :: GetSourceRef () const
{
	
	return Ref;
	
}
