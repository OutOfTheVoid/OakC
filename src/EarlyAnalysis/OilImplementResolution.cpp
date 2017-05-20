#include <EarlyAnalysis/OilImplementResolution.h>

#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraversal.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTypeRef.h>

#include <Logging/Logging.h>
#include <Encoding/CodeConversion.h>

ResolveImplementsStatus OilResolveImplements ( OilNamespaceDefinition & CurrentNS, OilImplementBlock *& FailedBlock )
{
	
	FailedBlock = NULL;
	
	while ( CurrentNS.GetUnresolvedImplementBlockCount () != 0 )
	{
		
		OilImplementBlock * Block = CurrentNS.GetUnresolvedImplementBlock ( CurrentNS.GetUnresolvedImplementBlockCount () - 1 );
		
		bool TemplateMismatch = false;
		OilTypeDefinition * ImplementedType = FindTypeDefinition ( * Block -> GetImplementedType (), CurrentNS, TemplateMismatch );
		
		if ( ImplementedType == NULL )
		{
			
			FailedBlock = Block;
			
			if ( TemplateMismatch )
				return kResolveImplementsStatus_Failure_TemplateMismatch;
			else
				return kResolveImplementsStatus_Failure_NoResolution;
			
		}
		
		if ( Block -> IsForTrait () )
		{
			
			OilTraitDefinition * ForTrait = FindTraitDefinition ( * Block -> GetForTrait (), CurrentNS, TemplateMismatch );
			
			if ( ForTrait == NULL )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_NoResolution_ForTrait;
				
			}
			
			std :: vector <std :: u32string> AbsoluteNamePath;
			
			BuildAbsoluteNamePath_Trait ( AbsoluteNamePath, * ForTrait );
			
			bool NameConflict = false;
			bool RedefConflict = false;
			
			ImplementedType -> AddTraitImplementBlock ( & AbsoluteNamePath [ 0 ], AbsoluteNamePath.size (), Block, NameConflict, RedefConflict );
			
			if ( NameConflict || RedefConflict )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_Conflict;
				
			}
			
		}
		else
		{
			
			if ( ImplementedType -> GetPrincipalImplementBlock () != NULL )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_Conflict;
				
			}
			
			ImplementedType -> SetPrincipalImplementBlock ( Block );
			
		}
		
		CurrentNS.RemoveUnresolvedImplementBlock ( CurrentNS.GetUnresolvedImplementBlockCount () - 1 );
		
	}
	
	ResolveImplementsStatus SubStatus;
	
	for ( uint32_t I = 0; I < CurrentNS.GetSubNamespaceDefinitionCount (); I ++ )
	{
		
		SubStatus = OilResolveImplements ( * CurrentNS.GetNamespaceDefinition ( I ), FailedBlock );
		
		if ( SubStatus != kResolveImplementsStatus_Success )
			return SubStatus;
		
	}
	
	return kResolveImplementsStatus_Success;
		
}
