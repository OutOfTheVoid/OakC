#include <OIL/OilNullPointerLiteral.h>

OilNullPointerLiteral :: OilNullPointerLiteral ( const SourceRef & Ref ):
	Ref ( Ref )
{
}

OilNullPointerLiteral :: ~OilNullPointerLiteral ()
{
}

bool OilNullPointerLiteral :: IsConstant () const
{
	
	return true;
	
}

IOilPrimary :: PrimaryType OilNullPointerLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_NullPointerLiteral;
	
}

const SourceRef & OilNullPointerLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
