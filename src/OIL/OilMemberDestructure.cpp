#include <OIL/OilMemberDestructure.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilStructDestructure.h>

#ifndef NULL
	#define nullptr
#endif

OilMemberDestructure :: OilMemberDestructure ( const SourceRef & Ref, const std :: u32string & MemberName ):
	Ref ( Ref ),
	Ignored ( true ),
	MemberName ( MemberName ),
	ValueName ( U"" ),
	SubDestructure ( NULL ),
	DestructureType ( NULL )
{
}

OilMemberDestructure :: OilMemberDestructure ( const SourceRef & Ref, const std :: u32string & MemberName, const std :: u32string ValueName ):
	Ref ( Ref ),
	Ignored ( false ),
	MemberName ( MemberName ),
	ValueName ( ValueName ),
	SubDestructure ( NULL ),
	DestructureType ( NULL )
{
}

OilMemberDestructure :: OilMemberDestructure ( const SourceRef & Ref, const std :: u32string & MemberName, OilStructDestructure * SubDestructure ):
	Ref ( Ref ),
	Ignored ( false ),
	MemberName ( MemberName ),
	ValueName ( U"" ),
	SubDestructure ( SubDestructure ),
	DestructureType ( NULL )
{
}

OilMemberDestructure :: ~OilMemberDestructure ()
{
	
	if ( DestructureType != NULL )
		delete DestructureType;
	
}

const std :: u32string & OilMemberDestructure :: GetMemberName () const
{
	
	return MemberName;
	
}

bool OilMemberDestructure :: IsIgnored () const
{
	
	return Ignored;
	
}

bool OilMemberDestructure :: IsSubDestructure () const
{
	
	return SubDestructure != NULL;
	
}

const std :: u32string & OilMemberDestructure :: GetValueName () const
{
	
	return ValueName;
	
}

const OilStructDestructure * OilMemberDestructure :: GetSubDestructure () const
{
	
	return SubDestructure;
	
}

OilStructDestructure * OilMemberDestructure :: GetSubDestructure ()
{
	
	return SubDestructure;
	
}

bool OilMemberDestructure :: IsDestructuredTypeResolved () const
{
	
	return SubDestructure != NULL ? SubDestructure -> IsDestructuredTypeResolved () : ( DestructureType == NULL ) ? false : DestructureType -> IsResolved ();
	
}

void OilMemberDestructure :: SetDestructuredType ( OilTypeRef * Ref )
{
	
	if ( ( DestructureType != NULL ) && ( Ref != DestructureType ) )
		delete DestructureType;
	
	this -> DestructureType = Ref;
	
}

const OilTypeRef * OilMemberDestructure :: GetDestructuredType () const
{
	
	return DestructureType;
	
}

OilTypeRef * OilMemberDestructure :: GetDestructuredType ()
{
	
	return DestructureType;
	
}

const SourceRef & OilMemberDestructure :: GetSourceRef () const
{
	
	return Ref;
	
}
