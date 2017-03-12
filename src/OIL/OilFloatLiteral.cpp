#include <OIL/OilFloatLiteral.h>

OilFloatLiteral :: OilFloatLiteral ( const BigFloat & Value, FloatType Type ):
	Value ( Value ),
	Type ( Type )
{
}

OilFloatLiteral :: ~OilFloatLiteral ()
{
}

void OilFloatLiteral :: SetValue ( const BigFloat & Value, FloatType Type )
{
	
	this -> Value = Value;
	this -> Type = Type;
	
}

const BigFloat & OilFloatLiteral :: GetValue () const
{
	
	return Value;
	
}

OilFloatLiteral :: FloatType OilFloatLiteral :: GetType ()
{
	
	return Type;
	
}

bool OilFloatLiteral :: IsConstant () const
{
	
	return true;
	
}
