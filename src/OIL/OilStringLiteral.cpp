#include <OIL/OilStringLiteral.h>

OilStringLiteral :: OilStringLiteral ( const SourceRef & Ref, EncodingType Type, const std :: u32string & Value ):
	Type ( Type ),
	Value ( Value ),
	Ref ( Ref )
{
}

OilStringLiteral :: ~OilStringLiteral ()
{
}

void OilStringLiteral :: SetType ( EncodingType Type )
{
	
	this -> Type = Type;
	
}

OilStringLiteral :: EncodingType OilStringLiteral :: GetType () const
{
	
	return Type;
	
}

const std :: u32string OilStringLiteral :: GetValue () const
{
	
	return Value;
	
}

bool OilStringLiteral :: IsConstant () const
{
	
	return true;
	
}

IOilPrimary :: PrimaryType OilStringLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_StringLiteral;
	
}

const SourceRef & OilStringLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
