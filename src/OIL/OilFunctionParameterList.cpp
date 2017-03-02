#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilFunctionParameter.h>

OilFunctionParameterList :: OilFunctionParameterList ():
	Parameters ()
{
}

OilFunctionParameterList :: ~OilFunctionParameterList ()
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: iterator Iter = Parameters.begin ();
	
	while ( Iter != Parameters.end () )
	{
		
		delete Iter -> second;
		
		Iter ++;
		
	}
	
}

void OilFunctionParameterList :: AddParameter ( OilFunctionParameter * Parameter )
{
	
	Parameters [ Parameter -> GetName () ] = Parameter;
	
}

uint32_t OilFunctionParameterList :: GetParameterCount () const
{
	
	return Parameters.size ();
	
}

const OilFunctionParameter * OilFunctionParameterList :: GetFunctionParameter ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: const_iterator Iter = Parameters.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}

OilFunctionParameter * OilFunctionParameterList :: GetFunctionParameter ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: iterator Iter = Parameters.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}

const OilFunctionParameter * OilFunctionParameterList :: FindFunctionParameter ( const std :: u32string & Name ) const
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: const_iterator Iter = Parameters.find ( Name );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}

OilFunctionParameter * OilFunctionParameterList :: FindFunctionParameter ( const std :: u32string & Name )
{
	
	std :: map <std :: u32string, OilFunctionParameter *> :: iterator Iter = Parameters.find ( Name );
	
	if ( Iter != Parameters.end () )
		return Iter -> second;
	
	return NULL;
	
}