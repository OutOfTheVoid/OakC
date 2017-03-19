#ifndef OIL_OILMETHODDEFINITION_H
#define OIL_OILMETHODDEFINITION_H

#include <string>
#include <map>

class OilMethodParameterList;
class OilStatementBody;
class OilTemplateDefinition;
class OilTypeRef;

class OilMethodDefinition
{
public:
	
	OilMethodDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilMethodParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType );
	OilMethodDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilMethodParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition );
	~OilMethodDefinition ();
	
	const std :: u32string GetName () const;
	
	const OilMethodParameterList * GetParameterList () const;
	OilMethodParameterList * GetParameterList ();
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	const OilTypeRef * GetReturnType () const;
	OilTypeRef * GetReturnType ();
	
	bool IsTemplated () const;
	bool ConstantTerms () const;
	
	bool IsPublic () const;
	bool IsInline () const;
	
	bool HasReturnType () const;
	
private:
	
	const std :: u32string Name;
	
	bool Public;
	bool Inline;
	
	OilTemplateDefinition * TemplateDefinition;
	OilMethodParameterList * ParameterList;
	OilTypeRef * ReturnType;
	OilStatementBody * StatementBody;
	
};

#endif
