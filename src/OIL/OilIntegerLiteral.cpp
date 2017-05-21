#include <OIL/OilIntegerLiteral.h>

OilIntegerLiteral :: OilIntegerLiteral ( const SourceRef & Ref, IntType Type, uint64_t UValue ):
	UValue ( UValue ),
	Type ( Type ),
	Ref ( Ref )
{
}

OilIntegerLiteral :: OilIntegerLiteral ( const SourceRef & Ref, IntType Type, int64_t SValue ):
	SValue ( SValue ),
	Type ( Type ),
	Ref ( Ref )
{
}

void OilIntegerLiteral :: Set ( IntType Type, uint64_t UValue )
{
	
	this -> Type = Type;
	this -> UValue = UValue;
	
}

void OilIntegerLiteral :: Set ( IntType Type, int64_t SValue )
{
	
	this -> Type = Type;
	this -> SValue = SValue;
	
}

uint64_t OilIntegerLiteral :: GetUValue () const
{
	
	return UValue;
	
}

int64_t OilIntegerLiteral :: GetSValue () const
{
	
	return SValue;
	
}

OilIntegerLiteral :: IntType OilIntegerLiteral :: GetType () const
{
	
	return Type;
	
}

bool OilIntegerLiteral :: IsConstant () const
{
	
	return true;
	
}

IOilPrimary :: PrimaryType OilIntegerLiteral :: GetPrimaryType () const
{
	
	return kPrimaryType_IntegerLiteral;
	
}

const SourceRef & OilIntegerLiteral :: GetSourceRef () const
{
	
	return Ref;
	
}
