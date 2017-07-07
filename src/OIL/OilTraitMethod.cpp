#include <OIL/OilTraitMethod.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilMethodParameterList.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTraitMethod :: OilTraitMethod ( const SourceRef & Ref, const std :: u32string & Name, OilMethodParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable ):
	Name ( Name ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	TemplateDefinition ( NULL ),
	Ref ( Ref )
{
}

OilTraitMethod :: OilTraitMethod ( const SourceRef & Ref, const std :: u32string & Name, OilMethodParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	TemplateDefinition ( TemplateDefinition ),
	Ref ( Ref )
{
}

OilTraitMethod :: ~OilTraitMethod ()
{
	
	delete ParameterList;
	
	if ( ReturnType != NULL )
		delete ReturnType;
	
}

const std :: u32string & OilTraitMethod :: GetName () const
{
	
	return Name;
	
}

const OilMethodParameterList * OilTraitMethod :: GetParameterList () const
{
	
	return ParameterList;
	
}

OilMethodParameterList * OilTraitMethod :: GetParameterList ()
{
	
	return ParameterList;
	
}

const OilTypeRef * OilTraitMethod :: GetReturnType () const
{
	
	return ReturnType;
	
}

OilTypeRef * OilTraitMethod :: GetReturnType ()
{
	
	return ReturnType;
	
}

bool OilTraitMethod :: GetReturnTypeMutable () const
{
	
	return ReturnTypeMutable;
	
}

bool OilTraitMethod :: HasReturnType () const
{
	
	return ReturnType != NULL;
	
}

bool OilTraitMethod :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}

const OilTemplateDefinition * OilTraitMethod :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilTraitMethod :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}

const SourceRef & OilTraitMethod :: GetSourceRef () const
{
	
	return Ref;
	
}
