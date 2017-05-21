#ifndef OIL_OILTEMPALTEDEFINITIONPARAMETER_H
#define OIL_OILTEMPALTEDEFINITIONPARAMETER_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilTypeRef;

class OilTemplateDefinitionParameter
{
public:
		
	OilTemplateDefinitionParameter ( const SourceRef & Ref, const std :: u32string & Name );
	OilTemplateDefinitionParameter ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef ** RestrictionTypes, uint32_t RestrictionCount );
	~OilTemplateDefinitionParameter ();
	
	const std :: u32string & GetName () const;
	
	bool IsRestricted () const;
	
	uint32_t GetRestrictionCount () const;
	OilTypeRef * GetRestriction ( uint32_t Index );
	const OilTypeRef * GetRestriction ( uint32_t Index ) const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string Name;
	
	OilTypeRef ** RestrictionTypes;
	uint32_t RestrictionCount;
	
	SourceRef Ref;
	
};

#endif
