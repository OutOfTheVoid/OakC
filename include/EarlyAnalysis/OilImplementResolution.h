#ifndef OIL_OILIMPLEMENTRESOLUTION_H
#define OIL_OILIMPLEMENTRESOLUTION_H

class OilNamespaceDefinition;
class OilImplementBlock;

typedef enum
{
	
	kResolveImplementsStatus_Success,
	kResolveImplementsStatus_Failure_NoResolution,
	kResolveImplementsStatus_Failure_NoResolution_ForTrait,
	kResolveImplementsStatus_Failure_TemplateMismatch,
	kResolveImplementsStatus_Failure_Conflict,
	
} ResolveImplementsStatus;

ResolveImplementsStatus OilResolveImplements ( OilNamespaceDefinition & GlobalNS, OilImplementBlock *& FailedBlock );

#endif
