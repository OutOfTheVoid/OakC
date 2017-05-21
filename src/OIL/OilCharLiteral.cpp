#include <OIL/OilCharLiteral.h>

OilCharLiteral :: OilCharLiteral ( const SourceRef & Ref, char32_t Value ):
	Value ( Value ),
	Ref ( Ref )
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

const SourceRef & OilCharLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
