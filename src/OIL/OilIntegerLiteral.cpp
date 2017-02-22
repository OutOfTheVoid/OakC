#include <OIL/OilIntegerLiteral.h>

OilIntegerLiteral :: OilIntegerLiteral ( IntType Type, uint64_t UValue ):
	Type ( Type ),
	UValue ( UValue )
{
}

OilIntegerLiteral :: OilIntegerLiteral ( IntType Type, int64_t SValue ):
	Type ( Type ),
	IValue ( SValue )
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

IntType OilIntegerLiteral :: GetType () const
{
	
	return Type;
	
}

bool OilIntegerLiteral :: IsConstant () const
{
	
	return true;
	
}
