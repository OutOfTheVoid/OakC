#include <OIL/OilFloatLiteral.h>

OilFloatLiteral :: OilFloatLiteral ( const SourceRef & Ref, const BigFloat & Value, FloatType Type ):
	Value ( Value ),
	Type ( Type ),
	Ref ( Ref )
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

OilFloatLiteral :: FloatType OilFloatLiteral :: GetType () const
{
	
	return Type;
	
}

bool OilFloatLiteral :: IsConstant () const
{
	
	return true;
	
}

IOilPrimary :: PrimaryType OilFloatLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_FloatLiteral;
	
}

const SourceRef & OilFloatLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
