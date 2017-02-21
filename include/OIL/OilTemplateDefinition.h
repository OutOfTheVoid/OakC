#ifndef OIL_OILTEMPLATEDEFINITION_H
#define OIL_OILTEMPLATEDEFINITION_H

#include <string>
#include <map>

class OilTemplateDefinitionParameter;

class OilTemplateDefinition
{
public:
	
	OilTemplateDefinition ();
	~OilTemplateDefinition ();
	
	void AddParameter ( OilTemplateDefinitionParameter * Parameter );
	
	uint32_t GetTemplateParameterCount ();
	
	OilTemplateDefinitionParameter * GetTemplateParameter ( uint32_t Index );
	OilTemplateDefinitionParameter * GetTemplateParameter ( const std :: u32string & Name );
	
private:
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> Parameters;
	
};

#endif
