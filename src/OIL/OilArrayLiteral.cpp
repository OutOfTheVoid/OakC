#include <OIL/OilArrayLiteral.h>
#include <OIL/OilTypeRef.h>

OilArrayLiteral :: OilArrayLiteral ():
	CountSpecified ( false ),
	SpecificCount ( 0 ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions ()
{
}

OilArrayLiteral :: OilArrayLiteral ( uint64_t SpecificCount ):
	CountSpecified ( true ),
	SpecificCount ( SpecificCount ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions ()
{
}

OilArrayLiteral :: OilArrayLiteral ( uint64_t SpecificCount, OilTypeRef * TypeSpecifier ):
	CountSpecified ( true ),
	SpecificCount ( SpecificCount ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions ()
{
}

OilArrayLiteral :: OilArrayLiteral ( OilTypeRef * TypeSpecifier ):
	CountSpecified ( false ),
	SpecificCount ( 0 ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions ()
{
}

OilArrayLiteral :: OilArrayLiteral ( IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountSpecified ( false ),
	SpecificCount ( 0 ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount )
{
}

OilArrayLiteral :: OilArrayLiteral ( uint64_t SpecificCount, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountSpecified ( true ),
	SpecificCount ( SpecificCount ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount )
{
}

OilArrayLiteral :: OilArrayLiteral ( uint64_t SpecificCount, OilTypeRef * TypeSpecifier, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountSpecified ( true ),
	SpecificCount ( SpecificCount ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount )
{
}

OilArrayLiteral :: OilArrayLiteral ( OilTypeRef * TypeSpecifier, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountSpecified ( false ),
	SpecificCount ( 0 ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount )
{
}


OilArrayLiteral :: ~OilArrayLiteral ()
{
	
	if ( TypeSpecifier != NULL )
		delete TypeSpecifier;
	
	for ( uint64_t I = 0; I < MemberInitializerExpressions.size (); I ++ )
		delete MemberInitializerExpressions [ I ];
	
}

bool OilArrayLiteral :: HasSpecificCount () const
{
	
	return CountSpecified;
	
}

bool OilArrayLiteral :: HasTypeSpecifier () const
{
	
	return TypeSpecifier != NULL;
	
}

bool OilArrayLiteral :: HasMemberInitiailizers () const
{
	
	return MemberInitializerExpressions.size () != 0;
	
}

const OilTypeRef * OilArrayLiteral :: GetTypeSpecifier () const
{
	
	return TypeSpecifier;
	
}

OilTypeRef * OilArrayLiteral :: GetTypeSpecifier ()
{
	
	return TypeSpecifier;
	
}

uint64_t OilArrayLiteral :: GetSpecificCount () const
{
	
	return SpecificCount;
	
}

uint64_t OilArrayLiteral :: GetMemberInitializerCount () const
{
	
	return MemberInitializerExpressions.size ();
	
}

const IOilPrimary * OilArrayLiteral :: GetMemberInitializer ( uint64_t Index ) const
{
	
	if ( Index >= MemberInitializerExpressions.size () )
		return NULL;
	
	return MemberInitializerExpressions [ Index ];
	
}

IOilPrimary * OilArrayLiteral :: GetMemberInitializer ( uint64_t Index )
{
	
	if ( Index >= MemberInitializerExpressions.size () )
		return NULL;
	
	return MemberInitializerExpressions [ Index ];
	
}

bool OilArrayLiteral :: IsConstant () const
{
	
	for ( uint64_t I = 0; I < MemberInitializerExpressions.size (); I ++ )
		if ( ! MemberInitializerExpressions [ I ] -> IsConstant () )
			return false;
	
	return true;
	
}

IOilPrimary :: PrimaryType OilArrayLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_ArrayLiteral;
	
}
