#ifndef OIL_OILTEMPLATESPECIFICATION_H
#define OIL_OILTEMPLATESPECIFICATION_H

#include <stdint.h>

#include <Tokenization/SourceRef.h>

class OilTypeRef;

class OilTemplateSpecification
{
public:
	
	OilTemplateSpecification ( const SourceRef & Ref, OilTypeRef ** TypeRefList, uint32_t TypeRefCount );
	~OilTemplateSpecification ();
	
	uint32_t GetTypeRefCount () const;
	OilTypeRef * GetTypeRef ( uint32_t Index );
	const OilTypeRef * GetTypeRef ( uint32_t Index ) const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilTypeRef ** TypeRefList;
	uint32_t TypeRefCount;
	
	SourceRef Ref;
	
};

#endif
