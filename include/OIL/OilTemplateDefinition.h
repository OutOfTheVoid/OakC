#ifndef OIL_OILTEMPLATEDEFINITION_H
#define OIL_OILTEMPLATEDEFINITION_H

#include <string>
#include <map>

#include <Tokenization/SourceRef.h>

class OilTemplateDefinitionParameter;

class OilTemplateDefinition
{
public:
	
	OilTemplateDefinition ( const SourceRef & Ref );
	~OilTemplateDefinition ();
	
	void AddParameter ( OilTemplateDefinitionParameter * Parameter );
	
	uint32_t GetTemplateParameterCount () const;
	
	const OilTemplateDefinitionParameter * GetTemplateParameter ( uint32_t Index ) const;
	OilTemplateDefinitionParameter * GetTemplateParameter ( uint32_t Index );
	
	const OilTemplateDefinitionParameter * GetTemplateParameter ( const std :: u32string & Name ) const;
	OilTemplateDefinitionParameter * GetTemplateParameter ( const std :: u32string & Name );
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	std :: map <std :: u32string, OilTemplateDefinitionParameter *> Parameters;
	
	SourceRef Ref;
	
};

#endif
