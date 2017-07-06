#include <OIL/OilStructBinding.h>
#include <OIL/OilTypeRef.h>

OilStructBinding :: OilStructBinding ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef * TypeRef, bool Public ):
	Name ( Name ),
	TypeRef ( TypeRef ),
	Ref ( Ref ),
	Public ( Public )
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

const SourceRef & OilStructBinding :: GetSourceRef () const
{
	
	return Ref;
	
}

bool OilStructBinding :: IsPublic () const
{
	
	return Public;
	
}
