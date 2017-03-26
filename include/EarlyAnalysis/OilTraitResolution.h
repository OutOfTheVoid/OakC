#ifndef OIL_OILTRAITRESOLUTION_H
#define OIL_OILTRAITRESOLUTION_H

class OilNamespaceDefinition;

typedef enum
{
	
	kResolveTraitsStatus_Success_Incomplete = 0,
	kResolveTraitsStatus_Success_Complete = 1,
	kResolveTraitsStatus_Failure_NoResolution = 2,
	kResolveTraitsStatus_Failure_TemplateMismatch = 3,
	
} ResolveTraitsStatus;

ResolveTraitsStatus OilResolveTraits ( OilNamespaceDefinition & GlobalNS );

#endif
