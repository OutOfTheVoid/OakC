#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraitFunction.h>
#include <OIL/OilTraitMethod.h>
#include <OIL/OilTemplateDefinition.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTraitDefinition :: OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount ):
	Name ( Name ),
	TraitFunctions ( new OilTraitFunction * [ FunctionCount ] ),
	FunctionCount ( FunctionCount ),
	TraitMethods ( new OilTraitMethod * [ MethodCount ] ),
	MethodCount ( MethodCount ),
	TemplateDefinition ( NULL )
{
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		this -> TraitFunctions [ I ] = TraitFunctions [ I ];
	
	for ( uint32_t I = 0; I < MethodCount; I ++ )
		this -> TraitMethods [ I ] = TraitMethods [ I ];
	
}

OilTraitDefinition :: OilTraitDefinition ( const std :: u32string & Name, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	TraitFunctions ( new OilTraitFunction * [ FunctionCount ] ),
	FunctionCount ( FunctionCount ),
	TraitMethods ( new OilTraitMethod * [ MethodCount ] ),
	MethodCount ( MethodCount ),
	TemplateDefinition ( TemplateDefinition )
{
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		this -> TraitFunctions [ I ] = TraitFunctions [ I ];
	
	for ( uint32_t I = 0; I < MethodCount; I ++ )
		this -> TraitMethods [ I ] = TraitMethods [ I ];
	
}
	
OilTraitDefinition :: ~OilTraitDefinition ()
{
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		delete TraitFunctions [ I ];
	
	for ( uint32_t I = 0; I < MethodCount; I ++ )
		delete TraitMethods [ I ];
	
	delete [] TraitFunctions;
	delete [] TraitMethods;
	
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

uint32_t OilTraitDefinition :: GetMethodCount () const
{
	
	return MethodCount;
	
}

const OilTraitMethod * OilTraitDefinition :: GetTraitMethod ( uint32_t Index ) const
{
	
	if ( Index >= MethodCount )
		return NULL;
	
	return TraitMethods [ Index ];
	
}

OilTraitMethod * OilTraitDefinition :: GetTraitMethod ( uint32_t Index )
{
	
	if ( Index >= MethodCount )
		return NULL;
	
	return TraitMethods [ Index ];
	
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
