#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilTypeRef.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTemplateDefinitionParameter :: OilTemplateDefinitionParameter ( const std :: u32string & Name ):
	Name ( Name ),
	RestrictionTypes ( NULL ),
	RestrictionCount ( 0 )
{
}

OilTemplateDefinitionParameter :: OilTemplateDefinitionParameter ( const std :: u32string & Name, OilTypeRef ** RestrictionTypes, uint32_t RestrictionCount ):
	Name ( Name ),
	RestrictionCount ( RestrictionCount )
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

const std :: u32string & OilTemplateDefinitionParameter :: GetName ()
{
	
	return Name;
	
}

bool OilTemplateDefinitionParameter :: IsRestricted ()
{
	
	return RestrictionTypes != NULL;
	
}

uint32_t OilTemplateDefinitionParameter :: GetRestrictionCount ()
{
	
	return RestrictionCount;
	
}

OilTypeRef * OilTemplateDefinitionParameter :: GetRestriction ( uint32_t Index )
{
	
	if ( Index >= RestrictionCount )
		return NULL;
	
	return RestrictionTypes [ Index ];
	
}
