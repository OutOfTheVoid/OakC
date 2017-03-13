#include <OIL/OilCharLiteral.h>

OilCharLiteral :: OilCharLiteral ( char32_t Value ):
	Value ( Value )
{
}

OilCharLiteral :: ~OilCharLiteral ()
{
}

char32_t OilCharLiteral :: GetValue () const
{
	
	return Value;
	
}

bool OilCharLiteral :: IsConstant () const
{
	
	return true;
	
}

IOilPrimary :: PrimaryType OilCharLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_CharLiteral;
	
}
