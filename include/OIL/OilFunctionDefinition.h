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
	
	bool IsTemplated () const;
	bool ConstantTerms () const;
	
private:
	
	const std :: u32string Name;
	
	OilTemplateDefinition * TemplateDefinition;
	OilFunctionParameterList * ParameterList;
	OilStatementBody * StatementBody;
	
};

#endif
