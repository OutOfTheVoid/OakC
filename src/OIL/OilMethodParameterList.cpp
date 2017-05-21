#include <OIL/OilMethodParameterList.h>
#include <OIL/OilFunctionParameter.h>

OilMethodParameterList :: OilMethodParameterList ( const SourceRef & Ref, bool SelfIsReference ):
	SelfIsReference ( SelfIsReference ),
	Parameters (),
	Ref ( Ref )
{
}

OilMethodParameterList :: ~OilMethodParameterList ()
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: iterator Iter = Parameters.begin ();
	
	while ( Iter != Parameters.end () )
	{
		
		delete Iter -> second;
		
		Iter ++;
		
	}
	
}

void OilMethodParameterList :: AddParameter ( OilFunctionParameter * Parameter )
{
	
	Parameters [ Parameter -> GetName () ] = Parameter;
	
}

bool OilMethodParameterList :: IsSelfReference () const
{
	
	return SelfIsReference;
	
}

uint32_t OilMethodParameterList :: GetParameterCount () const
{
	
	return Parameters.size ();
	
}

const OilFunctionParameter * OilMethodParameterList :: GetFunctionParameter ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: const_iterator Iter = Parameters.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}

OilFunctionParameter * OilMethodParameterList :: GetFunctionParameter ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: iterator Iter = Parameters.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}

const OilFunctionParameter * OilMethodParameterList :: FindFunctionParameter ( const std :: u32string & Name ) const
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: const_iterator Iter = Parameters.find ( Name );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}

OilFunctionParameter * OilMethodParameterList :: FindFunctionParameter ( const std :: u32string & Name )
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: iterator Iter = Parameters.find ( Name );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}

const SourceRef & OilMethodParameterList :: GetSourceRef () const
{
	
	return Ref;
	
}
