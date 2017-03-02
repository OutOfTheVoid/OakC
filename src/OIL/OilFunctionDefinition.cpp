#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilStatementBody.h>

OilFunctionDefinition :: OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * StatementBody, OilTypeRef * ReturnType ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( NULL ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	StatementBody ( StatementBody )
{
}
	
OilFunctionDefinition :: OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * StatementBody, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( TemplateDefinition ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	StatementBody ( StatementBody )
{
}

OilFunctionDefinition :: ~OilFunctionDefinition ()
{
	
	if ( TemplateDefinition != NULL )
		delete TemplateDefinition;
	
	delete ParameterList;
	delete StatementBody;
	
}

const std :: u32string OilFunctionDefinition :: GetName () const
{
	
	return Name;
	
}

const OilFunctionParameterList * OilFunctionDefinition :: GetParameterList () const
{
	
	return ParameterList;
	
}

OilFunctionParameterList * OilFunctionDefinition :: GetParameterList ()
{
	
	return ParameterList;
	
}

const OilStatementBody * OilFunctionDefinition :: GetStatementBody () const
{
	
	return StatementBody;
	
}

OilStatementBody * OilFunctionDefinition :: GetStatementBody ()
{
	
	return StatementBody;
	
}

const OilTemplateDefinition * OilFunctionDefinition :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilFunctionDefinition :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}

const OilTypeRef * OilFunctionDefinition :: GetReturnType () const
{
	
	return ReturnType;
	
}

OilTypeRef * OilFunctionDefinition :: GetReturnType ()
{
	
	return ReturnType;
	
}

bool OilFunctionDefinition :: IsPublic () const
{
	
	return Public;
	
}

bool OilFunctionDefinition :: IsInline () const
{
	
	return Inline;
	
}

bool OilFunctionDefinition :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}

bool OilFunctionDefinition :: HasReturnType () const
{
	
	return ReturnType != NULL;
	
}

bool OilFunctionDefinition :: ConstantTerms () const
{
	
	// FOR NOW
	return false;
	
}
