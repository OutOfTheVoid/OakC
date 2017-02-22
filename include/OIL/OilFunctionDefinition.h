#ifndef OIL_OILFUNCTIONDEFINITION_H
#define OIL_OILFUNCTIONDEFINITION_H

class OilFunctionDefinition
{
public:
	
	OilFunctionDefinition ( const std :: u32string & Name, OilFunctionParameterList * ParamList, OilStatementBody * Body );
	OilFunctionDefinition ( const std :: u32string & Name, OilFunctionParameterList * ParamList, OilStatementBody * Body, OilTemplateDefinition * Template );
	~OilFunctionDefinition ();
	
	const std :: u32string GetName () const;
	
	const OilFunctionParameterList * GetParameterList () const;
	OilFunctionParameterList * GetParameterList ();
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
private:
	
	const std :: u32string Name;
	
}

#endif
