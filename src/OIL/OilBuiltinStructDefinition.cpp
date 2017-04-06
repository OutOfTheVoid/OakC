#include <OIL/OilBuiltinStructDefinition.h>
#include <OIL/OilStructDefinition.h>

OilBuiltinStructDefinition :: OilBuiltinStructDefinition ( const std :: u32string & Name, uint32_t Size, uint32_t Alignment, TypeFlag Flags ):
	Name ( Name ),
	Size ( Size ),
	Alignment ( Alignment ),
	Flags ( Flags ),
	UnderlyingStructure ( NULL )
{
}

OilBuiltinStructDefinition :: OilBuiltinStructDefinition ( const std :: u32string & Name, uint32_t Size, uint32_t Alignment, TypeFlag Flags, OilStructDefinition * UnderlyingStructure ):
	Name ( Name ),
	Size ( Size ),
	Alignment ( Alignment ),
	Flags ( Flags ),
	UnderlyingStructure ( UnderlyingStructure ) 
{
}

OilBuiltinStructDefinition :: ~OilBuiltinStructDefinition ()
{
	
	if ( UnderlyingStructure != NULL )
		delete UnderlyingStructure;
	
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
