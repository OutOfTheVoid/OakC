#include <OIL/OilTemplateDefinition.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTemplateDefinition :: OilTemplateDefinition ():
	Parameters ()
{	
}

OilTemplateDefinition :: ~OilTemplateDefinition ()
{
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> :: iterator Iter = Parameters.start ();
	
	while ( Iter != Parameters.end () )
	{
		
		delete Iter -> second;
		
		Iter ++;
		
	}
	
}

void OilTemplateDefinition :: AddParameter ( OilTemplateDefinitionParameter * Parameter )
{
	
	Parameters [ Parameter -> GetName () ] = Parameter;
	
	return true;
	
}

uint32_t OilTemplateDefinition :: GetTemplateParameterCount ()
{
	
	return Parameters.size ();
	
}

OilTemplateDefinitionParameter * OilTemplateDefinition :: GetTempalteParameter ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> :: iterator Iter = Parameters.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == Parameters.end () )
		return NULL;
	
	return Iter -> second;
	
}

OilTemplateDefinitionParameter * OilTemplateDefinition :: GetTemplateParameter ( const std :: u32string & Name )
{
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> :: iterator Iter = Parameters.find ( Parameter -> GetName () );
	
	if ( Iter == Parameters.end () )
		return NULL;
	
	return Iter -> second;
	
}
