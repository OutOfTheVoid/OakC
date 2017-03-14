#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraitFunction.h>
#include <OIL/OilTemplateDefinition.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTraitDefinition :: OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount ):
	Name ( Name ),
	TraitFunctions ( new OilTraitFunction * [ FunctionCount ] ),
	FunctionCount ( FunctionCount ),
	TemplateDefinition ( NULL )
{
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		this -> TraitFunctions [ I ] = TraitFunctions [ I ];
	
}

OilTraitDefinition :: OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	TraitFunctions ( new OilTraitFunction * [ FunctionCount ] ),
	FunctionCount ( FunctionCount ),
	TemplateDefinition ( TemplateDefinition )
{
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		this -> TraitFunctions [ I ] = TraitFunctions [ I ];
	
}
	
OilTraitDefinition :: ~OilTraitDefinition ()
{
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		delete TraitFunctions [ I ];
	
	delete [] TraitFunctions;
	
	if ( TemplateDefinition != NULL )
		delete TemplateDefinition;
	
}

uint32_t OilTraitDefinition :: GetFunctionCount () const
{
	
	return FunctionCount;
	
}

const OilTraitFunction * OilTraitDefinition :: GetTraitFunction ( uint32_t Index ) const
{
	
	if ( Index >= FunctionCount )
		return NULL;
	
	return TraitFunctions [ Index ];
	
}

OilTraitFunction * OilTraitDefinition :: GetTraitFunction ( uint32_t Index )
{
	
	if ( Index >= FunctionCount )
		return NULL;
	
	return TraitFunctions [ Index ];
	
}

bool OilTraitDefinition :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}

const OilTemplateDefinition * OilTraitDefinition :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilTraitDefinition :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}

const std :: u32string & OilTraitDefinition :: GetName () const
{
	
	return Name;
	
}
