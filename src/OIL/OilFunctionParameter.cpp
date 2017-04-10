#include <OIL/OilFunctionParameter.h>
#include <OIL/OilTypeRef.h>

OilFunctionParameter :: OilFunctionParameter ( const std :: u32string Name, OilTypeRef * Type, bool Mut ):
	Name ( Name ),
	Type ( Type ),
	Mut ( Mut )
{
}

OilFunctionParameter :: ~OilFunctionParameter ()
{
	
	delete Type;
	
}

const OilTypeRef * OilFunctionParameter :: GetType () const
{
	
	return Type;
	
}

OilTypeRef * OilFunctionParameter :: GetType ()
{
	
	return Type;
	
}

const std :: u32string & OilFunctionParameter :: GetName () const
{
	
	return Name;
	
}

bool OilFunctionParameter :: GetMut () const
{
	
	return Mut;
	
}