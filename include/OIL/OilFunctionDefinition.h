#ifndef OIL_OILFUNCTIONDEFINITION_H
#define OIL_OILFUNCTIONDEFINITION_H

#include <string>
#include <map>

class OilFunctionParameterList;
class OilStatementBody;
class OilTemplateDefinition;
class OilTypeRef;

class OilFunctionDefinition
{
public:
	
	OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType );
	OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition );
	~OilFunctionDefinition ();
	
	const std :: u32string GetName () const;
	
	const OilFunctionParameterList * GetParameterList () const;
	OilFunctionParameterList * GetParameterList ();
	
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
	OilFunctionParameterList * ParameterList;
	OilTypeRef * ReturnType;
	OilStatementBody * StatementBody;
	
};

#endif
