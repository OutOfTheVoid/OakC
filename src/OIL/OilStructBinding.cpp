#include <OIL/OilStructBinding.h>
#include <OIL/OilTypeRef.h>

OilStructBinding :: OilStructBinding ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef * TypeRef ):
	Name ( Name ),
	TypeRef ( TypeRef ),
	Ref ( Ref )
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
