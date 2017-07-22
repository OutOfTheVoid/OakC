#include <OIL/OilStructDestructure.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilMemberDestructure.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilStructDestructure :: OilStructDestructure ( const SourceRef & Ref ):
	Ref ( Ref ),
	DestructuredMembers (),
	StructType ( NULL )
{
}

OilStructDestructure :: ~OilStructDestructure ()
{
	
	if ( StructType != NULL )
		delete StructType;
	
	for ( uint32_t I = 0; I < DestructuredMembers.size (); I ++ )
		delete DestructuredMembers [ I ];
	
}

bool OilStructDestructure :: IsDestructuredTypeResolved () const
{
	
	return StructType != NULL ? StructType -> IsResolved () : false;
	
}

void OilStructDestructure :: SetDestructuredType ( OilTypeRef * Ref )
{
	
	if ( StructType != NULL && Ref != StructType )
		delete StructType;
	
	StructType = Ref;
	
}

const OilTypeRef * OilStructDestructure :: GetDestructuredType () const
{
	
	return StructType;
	
}

OilTypeRef * OilStructDestructure :: GetDestructuredType ()
{
	
	return StructType;
	
}

uint32_t OilStructDestructure :: GetMemberDestructureCount () const
{
	
	return DestructuredMembers.size ();
	
}

void OilStructDestructure :: AddMemberDestructure ( OilMemberDestructure * Member )
{
	
	DestructuredMembers.push_back ( Member );
	
}

const OilMemberDestructure * OilStructDestructure :: GetMemberDestructure ( uint32_t Index ) const
{
	
	if ( Index >= DestructuredMembers.size () )
		return NULL;
	
	return DestructuredMembers [ Index ];
	
}

OilMemberDestructure * OilStructDestructure :: GetMemberDestructure ( uint32_t Index )
{
	
	if ( Index >= DestructuredMembers.size () )
		return NULL;
	
	return DestructuredMembers [ Index ];
	
}

const SourceRef & OilStructDestructure :: GetSourceRef () const
{
	
	return Ref;
	
}
