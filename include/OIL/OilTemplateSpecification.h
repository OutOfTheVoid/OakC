#ifndef OIL_OILTEMPLATESPECIFICATION_H
#define OIL_OILTEMPLATESPECIFICATION_H

#include <stdint.h>

class OilTypeRef;

class OilTemplateSpecification
{
public:
	
	OilTemplateSpecification ( OilTypeRef ** TypeRefList, uint32_t TypeRefCount );
	~OilTemplateSpecification ();
	
	uint32_t GetTypeRefCount () const;
	OilTypeRef * GetTypeRef ( uint32_t Index );
	const OilTypeRef * GetTypeRef ( uint32_t Index ) const;
	
private:
	
	OilTypeRef ** TypeRefList;
	uint32_t TypeRefCount;
	
};

#endif
