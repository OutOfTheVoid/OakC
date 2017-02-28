#include <OIL/OilStringLiteral.h>

OilStringLiteral :: OilStringLiteral ( EncodingType Type, const std :: u32string & Value ):
	Type ( Type ),
	Value ( Value )
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
