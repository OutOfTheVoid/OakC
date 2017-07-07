#ifndef OIL_OILTRAITFUNCTION_H
#define OIL_OILTRAITFUNCTION_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilFunctionParameterList;
class OilTypeRef;
class OilTemplateDefinition;

class OilTraitFunction
{
public:
	
	OilTraitFunction ( const SourceRef & Ref, const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable );
	OilTraitFunction ( const SourceRef & Ref, const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition );
	~OilTraitFunction ();
	
	const std :: u32string & GetName () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	bool IsTemplated () const;
	
	const OilFunctionParameterList * GetParameterList () const;
	OilFunctionParameterList * GetParameterList ();
	
	const OilTypeRef * GetReturnType () const;
	OilTypeRef * GetReturnType ();
	
	bool GetReturnTypeMutable () const;
	
	bool HasReturnType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string Name;
	
	OilFunctionParameterList * ParameterList;
	OilTypeRef * ReturnType;
	bool ReturnTypeMutable;
	OilTemplateDefinition * TemplateDefinition;
	
	SourceRef Ref;
	
};

#endif
