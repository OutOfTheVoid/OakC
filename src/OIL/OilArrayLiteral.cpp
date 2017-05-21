#include <OIL/OilArrayLiteral.h>
#include <OIL/OilTypeRef.h>

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref ):
	CountExpression ( NULL ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions (),
	Ref ( Ref )
{
}

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref, IOilPrimary * CountExpression ):
	CountExpression ( CountExpression ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions (),
	Ref ( Ref )
{
}

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref, IOilPrimary * CountExpression, OilTypeRef * TypeSpecifier ):
	CountExpression ( CountExpression ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions (),
	Ref ( Ref )
{
}

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref, OilTypeRef * TypeSpecifier ):
	CountExpression ( 0 ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions (),
	Ref ( Ref )
{
}

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountExpression ( 0 ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount ),
	Ref ( Ref )
{
}

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref, IOilPrimary * CountExpression, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountExpression ( CountExpression ),
	TypeSpecifier ( NULL ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount ),
	Ref ( Ref )
{
}

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref, IOilPrimary * CountExpression, OilTypeRef * TypeSpecifier, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountExpression ( CountExpression ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount ),
	Ref ( Ref )
{
}

OilArrayLiteral :: OilArrayLiteral ( const SourceRef & Ref, OilTypeRef * TypeSpecifier, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount ):
	CountExpression ( NULL ),
	TypeSpecifier ( TypeSpecifier ),
	MemberInitializerExpressions ( MemberInitializerExpressions, MemberInitializerExpressions + ValueCount ),
	Ref ( Ref )
{
}


OilArrayLiteral :: ~OilArrayLiteral ()
{
	
	if ( CountExpression != NULL )
		delete CountExpression;
	
	if ( TypeSpecifier != NULL )
		delete TypeSpecifier;
	
	for ( uint64_t I = 0; I < MemberInitializerExpressions.size (); I ++ )
		delete MemberInitializerExpressions [ I ];
	
}

bool OilArrayLiteral :: HasSpecificCount () const
{
	
	return CountExpression != NULL;
	
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

const IOilPrimary * OilArrayLiteral :: GetCountExpression () const
{
	
	return CountExpression;
	
}

IOilPrimary * OilArrayLiteral :: GetCountExpression ()
{
	
	return CountExpression;
	
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
		
	if ( CountExpression != NULL )
		return CountExpression -> IsConstant ();
	
	return true;
	
}

IOilPrimary :: PrimaryType OilArrayLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_ArrayLiteral;
	
}

const SourceRef & OilArrayLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
