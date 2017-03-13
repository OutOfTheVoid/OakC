#include <OIL/OilBoolLiteral.h>

OilBoolLiteral :: OilBoolLiteral ( bool Value ):
	Value ( Value )
{
}

OilBoolLiteral :: ~OilBoolLiteral ()
{
}

bool OilBoolLiteral :: GetValue () const
{
	
	return Value;
	
}

bool OilBoolLiteral :: IsConstant () const
{
	
	return true;
	
}

IOilPrimary :: PrimaryType OilBoolLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_BoolLiteral;
	
}
