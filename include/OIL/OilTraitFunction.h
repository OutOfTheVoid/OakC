#ifndef OIL_OILNAMESPACEFUNCTION_H
#define OIL_OILNAMESPACEFUNCTION_H

#include <string>

class OilFunctionParameterList;
class OilTypeRef;
class OilTemplateDefinition;

class OilTraitFunction
{
public:
	
	OilTraitFunction ( const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType );
	OilTraitFunction ( const std :: u32string & Name, OilFunctionParameterList * ParameterList, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition );
	~OilTraitFunction ();
	
	const std :: u32string & GetName () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	bool IsTemplated () const;
	
	const OilFunctionParameterList * GetParameterList () const;
	OilFunctionParameterList * GetParameterList ();
	
	const OilTypeRef * GetReturnType () const;
	OilTypeRef * GetReturnType ();
	
	bool HasReturnType () const;
	
private:
	
	const std :: u32string Name;
	
	OilFunctionParameterList * ParameterList;
	OilTypeRef * ReturnType;
	OilTemplateDefinition * TemplateDefinition;
	
};

#endif
