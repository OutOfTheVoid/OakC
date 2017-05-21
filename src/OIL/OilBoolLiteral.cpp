#include <OIL/OilBoolLiteral.h>

OilBoolLiteral :: OilBoolLiteral ( const SourceRef & Ref, bool Value ):
	Value ( Value ),
	Ref ( Ref )
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

const SourceRef & OilBoolLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
