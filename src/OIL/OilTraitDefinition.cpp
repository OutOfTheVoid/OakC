#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraitFunction.h>
#include <OIL/OilTraitMethod.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTypeRef.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTraitDefinition :: OilTraitDefinition ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef ** RequiredTraits, uint32_t RequiredTraitCount, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount, bool IsBuiltin ):
	Name ( Name ),
	RequiredTraits ( new OilTypeRef * [ RequiredTraitCount ] ),
	RequiredTraitCount ( RequiredTraitCount ),
	TraitFunctions ( new OilTraitFunction * [ FunctionCount ] ),
	FunctionCount ( FunctionCount ),
	TraitMethods ( new OilTraitMethod * [ MethodCount ] ),
	MethodCount ( MethodCount ),
	TemplateDefinition ( NULL ),
	Builtin ( IsBuiltin ),
	ParentNamespace ( NULL ),
	Ref ( Ref )
{
	
	for ( uint32_t I = 0; I < RequiredTraitCount; I ++ )
		this -> RequiredTraits [ I ] = RequiredTraits [ I ];
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		this -> TraitFunctions [ I ] = TraitFunctions [ I ];
	
	for ( uint32_t I = 0; I < MethodCount; I ++ )
		this -> TraitMethods [ I ] = TraitMethods [ I ];
	
}

OilTraitDefinition :: OilTraitDefinition ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef ** RequiredTraits, uint32_t RequiredTraitCount, OilTraitFunction ** TraitFunctions, uint32_t FunctionCount, OilTraitMethod ** TraitMethods, uint32_t MethodCount, OilTemplateDefinition * TemplateDefinition, bool IsBuiltin ):
	Name ( Name ),
	RequiredTraits ( new OilTypeRef * [ RequiredTraitCount ] ),
	RequiredTraitCount ( RequiredTraitCount ),
	TraitFunctions ( new OilTraitFunction * [ FunctionCount ] ),
	FunctionCount ( FunctionCount ),
	TraitMethods ( new OilTraitMethod * [ MethodCount ] ),
	MethodCount ( MethodCount ),
	TemplateDefinition ( TemplateDefinition ),
	Builtin ( IsBuiltin ),
	ParentNamespace ( NULL ),
	Ref ( Ref )
{
	
	for ( uint32_t I = 0; I < RequiredTraitCount; I ++ )
		this -> RequiredTraits [ I ] = RequiredTraits [ I ];
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		this -> TraitFunctions [ I ] = TraitFunctions [ I ];
	
	for ( uint32_t I = 0; I < MethodCount; I ++ )
		this -> TraitMethods [ I ] = TraitMethods [ I ];
	
}
	
OilTraitDefinition :: ~OilTraitDefinition ()
{
	
	for ( uint32_t I = 0; I < RequiredTraitCount; I ++ )
		delete RequiredTraits [ I ];
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
		delete TraitFunctions [ I ];
	
	for ( uint32_t I = 0; I < MethodCount; I ++ )
		delete TraitMethods [ I ];
	
	delete [] RequiredTraits;
	delete [] TraitFunctions;
	delete [] TraitMethods;
	
	if ( TemplateDefinition != NULL )
		delete TemplateDefinition;
	
}

bool OilTraitDefinition :: IsBuiltin () const
{
	
	return Builtin;
	
}

uint32_t OilTraitDefinition :: GetRequiredTraitCount () const
{
	
	return RequiredTraitCount;
	
}

const OilTypeRef * OilTraitDefinition :: GetRequiredTrait ( uint32_t Index ) const
{
	
	if ( Index >= RequiredTraitCount )
		return NULL;
	
	return RequiredTraits [ Index ];
	
}

OilTypeRef * OilTraitDefinition :: GetRequiredTrait ( uint32_t Index )
{
	
	if ( Index >= RequiredTraitCount )
		return NULL;
	
	return RequiredTraits [ Index ];
	
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

const OilNamespaceDefinition * OilTraitDefinition :: GetParentNamespace () const
{
	
	return ParentNamespace;
	
}

OilNamespaceDefinition * OilTraitDefinition :: GetParentNamespace ()
{
	
	return ParentNamespace;
	
}

const SourceRef & OilTraitDefinition :: GetSourceRef () const
{
	
	return Ref;
	
}
