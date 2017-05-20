#include <EarlyAnalysis/OilImplementResolution.h>
#include <EarlyAnalysis/OilTypeResolution.h>

#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTraversal.h>

#include <Logging/Logging.h>
#include <Encoding/CodeConversion.h>

ResolveImplementsStatus OilResolveImplements ( OilNamespaceDefinition & CurrentNS, OilImplementBlock *& FailedBlock )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	FailedBlock = NULL;
	
	uint32_t UnresolvedOffset = 0;
	
	while ( CurrentNS.GetUnresolvedImplementBlockCount () > UnresolvedOffset )
	{
		
		OilImplementBlock * Block = CurrentNS.GetUnresolvedImplementBlock ( CurrentNS.GetUnresolvedImplementBlockCount () - UnresolvedOffset - 1 );
		OilTypeRef * ImplementedTypeRef = Block -> GetImplementedType ();
		
		if ( ! ImplementedTypeRef -> IsResolved () )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * ImplementedTypeRef );
			
			if ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_TemplateMismatch;
				
			}
			
			if ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_NonExistantType;
				
			}
			
			if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				UnresolvedOffset ++;
				
				continue;
				
			}
			else
			{
				
				UnresolvedOffset ++;
				
				continue;
				
			}
			
		}
		
		if ( ImplementedTypeRef -> IsResolvedAsTrait () )
		{
			
			FailedBlock = Block;
			
			return kResolveImplementsStatus_Failure_ImplementingTrait;
			
		}
		
		OilTypeDefinition * ImplementedType = ImplementedTypeRef -> GetResolvedTypeDefinition ();
		
		if ( Block -> IsForTrait () )
		{
			
			OilTypeRef * TraitRef = Block -> GetForTrait ();
			
			if ( ! TraitRef -> IsResolved () )
			{
				
				TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * ImplementedTypeRef );
				
				if ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch )
				{
					
					FailedBlock = Block;
					
					return kResolveImplementsStatus_Failure_TemplateMismatch;
					
				}
				
				if ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType )
				{
					
					FailedBlock = Block;
					
					return kResolveImplementsStatus_Failure_NonExistantType;
					
				}
				
				if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					UnresolvedOffset ++;
					
					continue;
					
				}
				else
				{
					
					UnresolvedOffset ++;
					
					continue;
					
				}
					
			}
			
			if ( ! TraitRef -> IsResolvedAsTrait () )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_ImplementedForNonTrait;
				
			}
			
			std :: vector <std :: u32string> AbsoluteNamePath;
			
			BuildAbsoluteNamePath_Trait ( AbsoluteNamePath, * TraitRef -> GetResolvedTraitDefinition () );
			
			bool NameConflict;
			bool RedefinitionConflict;
			
			ImplementedType -> AddTraitImplementBlock ( & AbsoluteNamePath [ 0 ], AbsoluteNamePath.size (), Block, NameConflict, RedefinitionConflict );
			
			if ( NameConflict )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_Conflict_TraitImplementation_NamespaceCollision;
				
			}
			
			if ( RedefinitionConflict )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_Conflict_TraitImplementation_TraitCollision;
				
			}
			
		}
		else
		{
			
			if ( ImplementedType -> GetPrincipalImplementBlock () != NULL )
			{
				
				FailedBlock = Block;
				
				return kResolveImplementsStatus_Failure_Conflict_PrincipalImplementation;
				
			}
			
			ImplementedType -> SetPrincipalImplementBlock ( Block );
			
		}
		
		CurrentNS.RemoveUnresolvedImplementBlock ( CurrentNS.GetUnresolvedImplementBlockCount () - UnresolvedOffset - 1 );
		
	}
	
	Unresolved = CurrentNS.GetUnresolvedImplementBlockCount () != 0;
	
	ResolveImplementsStatus SubStatus;
	
	for ( uint32_t I = 0; I < CurrentNS.GetSubNamespaceDefinitionCount (); I ++ )
	{
		
		SubStatus = OilResolveImplements ( * CurrentNS.GetNamespaceDefinition ( I ), FailedBlock );
		
		if ( SubStatus == kResolveImplementsStatus_Success_Complete )
			Progress = true;
		else if ( SubStatus == kResolveImplementsStatus_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( SubStatus == kResolveImplementsStatus_Success_NoProgress )
			Unresolved = true;
		else
			return SubStatus;
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kResolveImplementsStatus_Success_Progress;
		else
			return kResolveImplementsStatus_Success_NoProgress;
		
	}
	
	return kResolveImplementsStatus_Success_Complete;
		
}
