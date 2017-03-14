#include <OIL/OilTraitFunction.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilFunctionParameterList.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilTraitFunction :: OilTraitFunction ( const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType ):
	Name ( Name ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	TemplateDefinition ( NULL )
{
}

OilTraitFunction :: OilTraitFunction ( const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	TemplateDefinition ( TemplateDefinition )
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
