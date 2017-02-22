#include <OIL/OilBinding.h>
#include <OIL/OilTypeRef.h>

OilBinding :: OilBinding ( const std :: u32string & Name, OilTypeRef * Type, bool Mutable, bool Public ):
	Name ( Name ),
	Type ( Type ),
	Mutable ( Mutable ),
	Public ( Public )
{
}

OilBinding :: ~OilBinding ()
{
	
	delete Type;
	
}

const std :: u32string & OilBinding :: GetName () const
{
	
	return Name;
	
}

const OilTypeRef * OilBinding :: GetTypeRef () const
{
	
	return Type;
	
}

OilTypeRef * OilBinding :: GetTypeRef ()
{
	
	return Type;
	
}

bool OilBinding :: GetMutable () const
{
	
	return Mutable;
	
}

bool OilBinding :: GetPublic () const
{
	
	return Public;
	
}
