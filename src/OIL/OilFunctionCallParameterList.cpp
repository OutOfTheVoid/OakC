#include <OIL/OilFunctionCallParameterList.h>
#include <OIL/OilExpression.h>

OilFunctionCallParameterList :: OilFunctionCallParameterList ():
	Parameters ()
{
}

OilFunctionCallParameterList :: ~OilFunctionCallParameterList ()
{
	
	for ( uint32_t I = 0; I < Parameters.size (); I ++ )
		delete Parameters [ I ];
	
}

void OilFunctionCallParameterList :: AddParameter ( OilExpression * ParamExpression )
{
	
	Parameters.push_back ( ParamExpression );
	
}

uint32_t OilFunctionCallParameterList :: GetParameterCount () const
{
	
	return Parameters.size ();
	
}

const OilExpression * OilFunctionCallParameterList :: GetParameter ( uint32_t Index ) const
{
	
	if ( Index > Parameters.size () )
		return NULL;
	
	return Parameters [ Index ];
	
}

OilExpression * OilFunctionCallParameterList :: GetParameter ( uint32_t Index )
{
	
	if ( Index > Parameters.size () )
		return NULL;
	
	return Parameters [ Index ];
	
}
