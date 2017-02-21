#ifndef OIL_OILTEMPALTEDEFINITIONPARAMETER_H
#define OIL_OILTEMPALTEDEFINITIONPARAMETER_H

#include <string>

class OilTypeRef;

class OilTemplateDefinitionParameter
{
public:
		
	OilTemplateDefinitionParameter ( const std :: u32string & Name );
	OilTemplateDefinitionParameter ( const std :: u32string & Name, OilTypeRef ** RestrictionTypes, uint32_t RestrictionCount );
	~OilTemplateDefinitionParameter ();
	
	const std :: u32string & GetName ();
	
	bool IsRestricted ();
	
	uint32_t GetRestrictionCount ();
	OilTypeRef * GetRestriction ( uint32_t Index );
	
private:
	
	const std :: u32string Name;
	
	OilTypeRef ** RestrictionTypes;
	uint32_t RestrictionCount;
	
};

#endif
