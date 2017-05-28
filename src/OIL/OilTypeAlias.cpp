#include <OIL/OilTypeAlias.h>

#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateDefinition.h>

OilTypeAlias :: OilTypeAlias ( const SourceRef & Ref, const std :: u32string & AliasName, OilTypeRef * AliasedType, OilTemplateDefinition * TemplateDefinition, bool Builtin ):
	AliasedType ( AliasedType ),
	TemplateDefinition ( TemplateDefinition ),
	AliasName ( AliasName ),
	Builtin ( Builtin ),
	Ref ( Ref )
{
}

OilTypeAlias :: ~OilTypeAlias ()
{
	
	delete AliasedType;
	
	if ( TemplateDefinition != NULL )
		delete TemplateDefinition;
	
}

const std :: u32string & OilTypeAlias :: GetName () const
{
	
	return AliasName;
	
}

const OilTypeRef * OilTypeAlias :: GetAliasedType () const
{
	
	return AliasedType;
	
}

OilTypeRef * OilTypeAlias :: GetAliasedType ()
{
	
	return AliasedType;
	
}

bool OilTypeAlias :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}

const OilTemplateDefinition * OilTypeAlias :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilTypeAlias :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}

bool OilTypeAlias :: IsBuiltin () const
{
	
	return Builtin;
	
}

const SourceRef & OilTypeAlias :: GetSourceRef ()
{
	
	return Ref;
	
}
