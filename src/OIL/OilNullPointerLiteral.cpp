#include <OIL/OilNullPointerLiteral.h>

OilNullPointerLiteral :: OilNullPointerLiteral ()
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
