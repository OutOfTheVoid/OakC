#include <OIL/OilTraitFunction.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilFunctionParameterList.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTraitFunction :: OilTraitFunction ( const SourceRef & Ref, const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable ):
	Name ( Name ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	TemplateDefinition ( NULL ),
	Ref ( Ref )
{
}

OilTraitFunction :: OilTraitFunction ( const SourceRef & Ref, const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	TemplateDefinition ( TemplateDefinition ),
	Ref ( Ref )
{
}

OilTraitFunction :: ~OilTraitFunction ()
{
	
	delete ParameterList;
	
	if ( ReturnType != NULL )
		delete ReturnType;
	
}

const std :: u32string & OilTraitFunction :: GetName () const
{
	
	return Name;
	
}

const OilFunctionParameterList * OilTraitFunction :: GetParameterList () const
{
	
	return ParameterList;
	
}

OilFunctionParameterList * OilTraitFunction :: GetParameterList ()
{
	
	return ParameterList;
	
}

const OilTypeRef * OilTraitFunction :: GetReturnType () const
{
	
	return ReturnType;
	
}

OilTypeRef * OilTraitFunction :: GetReturnType ()
{
	
	return ReturnType;
	
}

bool OilTraitFunction :: GetReturnTypeMutable () const
{
	
	return ReturnTypeMutable;
	
}

bool OilTraitFunction :: HasReturnType () const
{
	
	return ReturnType != NULL;
	
}

bool OilTraitFunction :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}

const OilTemplateDefinition * OilTraitFunction :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilTraitFunction :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}

const SourceRef & OilTraitFunction :: GetSourceRef () const
{
	
	return Ref;
	
}
