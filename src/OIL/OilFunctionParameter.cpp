#include <OIL/OilFunctionParameter.h>
#include <OIL/OilTypeRef.h>

OilFunctionParameter :: OilFunctionParameter ( const SourceRef & Ref, const std :: u32string Name, OilTypeRef * Type, bool Mut ):
	Name ( Name ),
	Type ( Type ),
	Mut ( Mut ),
	Ref ( Ref )
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

const SourceRef & OilFunctionParameter :: GetSourceRef () const
{
	
	return Ref;
	
}
