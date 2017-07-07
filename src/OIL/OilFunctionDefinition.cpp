#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilStatementBody.h>

OilFunctionDefinition :: OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * StatementBody, OilTypeRef * ReturnType, bool ReturnTypeMutable ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( NULL ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	NativeFunction ( false ),
	StatementBody ( StatementBody ),
	NativeFunctionTag ( 0 ),
	Ref ( Ref )
{
}
	
OilFunctionDefinition :: OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * StatementBody, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( TemplateDefinition ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	NativeFunction ( false ),
	StatementBody ( StatementBody ),
	NativeFunctionTag ( 0 ),
	Ref ( Ref )
{
}

OilFunctionDefinition :: OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, void * NativeFunctionData, uint64_t NativeFunctionTag, OilTypeRef * ReturnType, bool ReturnTypeMutable ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( NULL ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	NativeFunction ( true ),
	NativeFunctionData ( NativeFunctionData ),
	NativeFunctionTag ( NativeFunctionTag ),
	Ref ( Ref )
{
}

OilFunctionDefinition :: OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, void * NativeFunctionData, uint64_t NativeFunctionTag, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition ):
	Name ( Name ),
	Public ( Public ),
	Inline ( Inline ),
	TemplateDefinition ( TemplateDefinition ),
	ParameterList ( ParameterList ),
	ReturnType ( ReturnType ),
	ReturnTypeMutable ( ReturnTypeMutable ),
	NativeFunction ( true ),
	NativeFunctionData ( NativeFunctionData ),
	NativeFunctionTag ( NativeFunctionTag ),
	Ref ( Ref )
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

bool OilFunctionDefinition :: GetReturnTypeMutable () const
{
	
	return ReturnTypeMutable;
	
}

bool OilFunctionDefinition :: IsNative () const
{
	
	return NativeFunction;
	
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

void * OilFunctionDefinition :: GetNativeFunctionData ()
{
	
	return NativeFunctionData;
	
}

const void * OilFunctionDefinition :: GetNativeFunctionData () const
{
	
	return NativeFunctionData;
	
}

uint64_t OilFunctionDefinition :: GetNativeFunctionTag () const
{
	
	return NativeFunctionTag;
	
}

const SourceRef & OilFunctionDefinition :: GetSourceRef () const
{
	
	return Ref;
	
}
