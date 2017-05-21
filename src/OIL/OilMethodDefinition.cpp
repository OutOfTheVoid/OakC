#include <OIL/OilMethodDefinition.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilMethodParameterList.h>
#include <OIL/OilStatementBody.h>

OilMethodDefinition :: OilMethodDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilMethodParameterList * ParameterList, OilStatementBody * StatementBody, OilTypeRef * ReturnType ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( NULL ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	StatementBody ( StatementBody ),
	Ref ( Ref )
{
}
	
OilMethodDefinition :: OilMethodDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilMethodParameterList * ParameterList, OilStatementBody * StatementBody, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( TemplateDefinition ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	StatementBody ( StatementBody ),
	Ref ( Ref )
{
}

OilMethodDefinition :: ~OilMethodDefinition ()
{
	
	if ( TemplateDefinition != NULL )
		delete TemplateDefinition;
	
	delete ParameterList;
	delete StatementBody;
	
}

const std :: u32string OilMethodDefinition :: GetName () const
{
	
	return Name;
	
}

const OilMethodParameterList * OilMethodDefinition :: GetParameterList () const
{
	
	return ParameterList;
	
}

OilMethodParameterList * OilMethodDefinition :: GetParameterList ()
{
	
	return ParameterList;
	
}

const OilStatementBody * OilMethodDefinition :: GetStatementBody () const
{
	
	return StatementBody;
	
}

OilStatementBody * OilMethodDefinition :: GetStatementBody ()
{
	
	return StatementBody;
	
}

const OilTemplateDefinition * OilMethodDefinition :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilMethodDefinition :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}

const OilTypeRef * OilMethodDefinition :: GetReturnType () const
{
	
	return ReturnType;
	
}

OilTypeRef * OilMethodDefinition :: GetReturnType ()
{
	
	return ReturnType;
	
}

bool OilMethodDefinition :: IsPublic () const
{
	
	return Public;
	
}

bool OilMethodDefinition :: IsInline () const
{
	
	return Inline;
	
}

bool OilMethodDefinition :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}

bool OilMethodDefinition :: HasReturnType () const
{
	
	return ReturnType != NULL;
	
}

bool OilMethodDefinition :: ConstantTerms () const
{
	
	// FOR NOW
	return false;
	
}

const SourceRef & OilMethodDefinition :: GetSourceRef () const
{
	
	return Ref;
	
}
