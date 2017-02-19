#ifndef OIL_OILTEMPLATESPECIFICATION_H
#define OIL_OILTEMPLATESPECIFICATION_H

#include <stdint.h>

class OilTypeRef;

class OilTemplateSpecification
{
public:
	
	OilTemplateSpecification ( OilTypeRef ** TypeRefList, uint32_t TypeRefCount );
	~OilTemplateSpecification ();
	
	uint32_t GetTypeRefCount ();
	OilTypeRef * GetTypeRef ( uint32_t Index );
	
	//bool IsResolved ();
	
private:
	
	OilTypeRef ** TypeRefList;
	uint32_t TypeRefCount;
	
};

#endif
