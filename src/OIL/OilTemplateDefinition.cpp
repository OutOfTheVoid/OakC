#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTemplateDefinition :: OilTemplateDefinition ():
	Parameters ()
{	
}

OilTemplateDefinition :: ~OilTemplateDefinition ()
{
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> :: iterator Iter = Parameters.begin ();
	
	while ( Iter != Parameters.end () )
	{
		
		delete Iter -> second;
		
		Iter ++;
		
	}
	
}

void OilTemplateDefinition :: AddParameter ( OilTemplateDefinitionParameter * Parameter )
{
	
	Parameters [ Parameter -> GetName () ] = Parameter;
	
}

uint32_t OilTemplateDefinition :: GetTemplateParameterCount () const
{
	
	return Parameters.size ();
	
}

OilTemplateDefinitionParameter * OilTemplateDefinition :: GetTemplateParameter ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> :: const_iterator Iter = Parameters.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == Parameters.end () )
		return NULL;
	
	return Iter -> second;
	
}

OilTemplateDefinitionParameter * OilTemplateDefinition :: GetTemplateParameter ( const std :: u32string & Name ) const
{
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> :: const_iterator Iter = Parameters.find ( Name );
	
	if ( Iter == Parameters.end () )
		return NULL;
	
	return Iter -> second;
	
}
