#ifndef OIL_OILTRAITMETHOD_H
#define OIL_OILTRAITMETHOD_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilMethodParameterList;
class OilTypeRef;
class OilTemplateDefinition;

class OilTraitMethod
{
public:
	
	OilTraitMethod ( const SourceRef & Ref, const std :: u32string & Name, OilMethodParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable );
	OilTraitMethod ( const SourceRef & Ref, const std :: u32string & Name, OilMethodParameterList * ParameterList, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition );
	~OilTraitMethod ();
	
	const std :: u32string & GetName () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	bool IsTemplated () const;
	
	const OilMethodParameterList * GetParameterList () const;
	OilMethodParameterList * GetParameterList ();
	
	const OilTypeRef * GetReturnType () const;
	OilTypeRef * GetReturnType ();
	
	bool GetReturnTypeMutable () const;
	
	bool HasReturnType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string Name;
	
	OilMethodParameterList * ParameterList;
	OilTypeRef * ReturnType;
	bool ReturnTypeMutable;
	OilTemplateDefinition * TemplateDefinition;
	
	SourceRef Ref;
	
};

#endif
