#include <OIL/OilStructLiteral.h>
#include <OIL/OilStructInitializerValue.h>
#include <OIL/OilTypeRef.h>

OilStructLiteral :: OilStructLiteral ( const SourceRef & Ref, OilTypeRef * LiteralType, OilStructInitializerValue ** InitializerValues, uint32_t InitializerValueCount ):
	LiteralType ( LiteralType ),
	InitializerValueCount ( InitializerValueCount ),
	InitializerValues ( new OilStructInitializerValue * [ InitializerValueCount ] ),
	Ref ( Ref )
{
	
	for ( uint32_t I = 0; I < InitializerValueCount; I ++ )
		this -> InitializerValues [ I ] = InitializerValues [ I ];
	
}

OilStructLiteral :: ~OilStructLiteral ()
{
	
	for ( uint32_t I = 0; I < InitializerValueCount; I ++ )
		delete InitializerValues [ I ];
	
	delete [] InitializerValues;
	
	delete LiteralType;
	
}

const OilTypeRef * OilStructLiteral :: GetLiteralType () const
{
	
	return LiteralType;
	
}

OilTypeRef * OilStructLiteral :: GetLiteralType ()
{
	
	return LiteralType;
	
}

uint32_t OilStructLiteral :: GetMemberValueCount () const
{
	
	return InitializerValueCount;
	
}

const OilStructInitializerValue * OilStructLiteral :: GetInitializerValue ( uint32_t Index ) const
{
	
	if ( Index >= InitializerValueCount )
		return NULL;
	
	return InitializerValues [ Index ];
	
}

OilStructInitializerValue * OilStructLiteral :: GetInitializerValue ( uint32_t Index )
{
	
	if ( Index >= InitializerValueCount )
		return NULL;
	
	return InitializerValues [ Index ];
	
}

bool OilStructLiteral :: IsConstant () const
{
	
	return false; // FOR NOW
	
}

IOilPrimary :: PrimaryType OilStructLiteral :: GetPrimaryType () const
{
	
	return IOilPrimary :: kPrimaryType_StructLiteral;
	
}

const SourceRef & OilStructLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
