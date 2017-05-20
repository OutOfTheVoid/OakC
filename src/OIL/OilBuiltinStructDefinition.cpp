#include <OIL/OilBuiltinStructDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilTemplateDefinition.h>

OilBuiltinStructDefinition :: OilBuiltinStructDefinition ( const std :: u32string & Name, uint32_t Size, uint32_t Alignment, TypeFlag Flags, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	Size ( Size ),
	Alignment ( Alignment ),
	Flags ( Flags ),
	UnderlyingStructure ( NULL ),
	TemplateDefinition ( TemplateDefinition )
{
}

OilBuiltinStructDefinition :: OilBuiltinStructDefinition ( const std :: u32string & Name, uint32_t Size, uint32_t Alignment, TypeFlag Flags, OilStructDefinition * UnderlyingStructure ):
	Name ( Name ),
	Size ( Size ),
	Alignment ( Alignment ),
	Flags ( Flags ),
	UnderlyingStructure ( UnderlyingStructure ),
	TemplateDefinition ( UnderlyingStructure -> IsTemplated () ? UnderlyingStructure -> GetTemplateDefinition () : NULL )
{
}

OilBuiltinStructDefinition :: ~OilBuiltinStructDefinition ()
{
	
	if ( UnderlyingStructure != NULL )
		delete UnderlyingStructure;
	
	if ( TemplateDefinition != NULL )
		delete TemplateDefinition;
	
}

const std :: u32string & OilBuiltinStructDefinition :: GetName () const
{
	
	return Name;
	
}

uint32_t OilBuiltinStructDefinition :: GetSize () const
{
	
	return Size;
	
}

uint32_t OilBuiltinStructDefinition :: GetAlignment () const
{
	
	return Alignment;
	
}

OilBuiltinStructDefinition :: TypeFlag OilBuiltinStructDefinition :: GetFlags () const
{
	
	return Flags;
	
}

bool OilBuiltinStructDefinition :: HasUnderlyingStructure () const
{
	
	return UnderlyingStructure != NULL;
	
}

const OilStructDefinition * OilBuiltinStructDefinition :: GetUnderlyingStructure () const
{
	
	return UnderlyingStructure;
	
}

OilStructDefinition * OilBuiltinStructDefinition :: GetUnderlyingStructure ()
{
	
	return UnderlyingStructure;
	
}

bool OilBuiltinStructDefinition :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}

const OilTemplateDefinition * OilBuiltinStructDefinition :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilBuiltinStructDefinition :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}
