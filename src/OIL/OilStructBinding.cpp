#include <OIL/OilStructBinding.h>
#include <OIL/OilTypeRef.h>

OilStructBinding :: OilStructBinding ( const std :: u32string & Name, OilTypeRef * TypeRef ):
	Name ( Name ),
	TypeRef ( TypeRef )
{
}

OilStructBinding :: ~OilStructBinding ()
{
	
	delete TypeRef;
	
}

const std :: u32string & OilStructBinding :: GetName () const
{
	
	return Name;
	
}

OilTypeRef * OilStructBinding :: GetTypeRef ()
{
	
	return TypeRef;
	
}

const OilTypeRef * OilStructBinding :: GetTypeRef () const
{
	
	return TypeRef;
	
}
