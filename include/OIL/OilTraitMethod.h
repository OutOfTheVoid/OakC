#ifndef OIL_OILTRAITMETHOD_H
#define OIL_OILTRAITMETHOD_H

#include <string>

class OilMethodParameterList;
class OilTypeRef;
class OilTemplateDefinition;

class OilTraitMethod
{
public:
	
	OilTraitMethod ( const std :: u32string & Name, OilMethodParameterList * ParameterList, OilTypeRef * ReturnType );
	OilTraitMethod ( const std :: u32string & Name, OilMethodParameterList * ParameterList, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition );
	~OilTraitMethod ();
	
	const std :: u32string & GetName () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	bool IsTemplated () const;
	
	const OilMethodParameterList * GetParameterList () const;
	OilMethodParameterList * GetParameterList ();
	
	const OilTypeRef * GetReturnType () const;
	OilTypeRef * GetReturnType ();
	
	bool HasReturnType () const;
	
private:
	
	const std :: u32string Name;
	
	OilMethodParameterList * ParameterList;
	OilTypeRef * ReturnType;
	OilTemplateDefinition * TemplateDefinition;
	
};

#endif
