#include <EarlyAnalysis/OilTraitResolution.h>

#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraversal.h>
#include <OIL/OilTypeDefinition.h>

#include <Logging/Logging.h>
#include <Encoding/CodeConversion.h>

ResolveTraitsStatus OilResolveTraits ( OilNamespaceDefinition & CurrentNS )
{
	
	if ( CurrentNS.GetUnresolvedImplementBlockCount () == 0 )
		return kResolveTraitsStatus_Success_Complete;
	
	LOG_VERBOSE ( std :: string ( "Unres traits: " ) + std :: to_string ( CurrentNS.GetUnresolvedImplementBlockCount () ) );
	
	uint32_t UnresolvedOffset = 0;
	
	while ( UnresolvedOffset < CurrentNS.GetUnresolvedImplementBlockCount () )
	{
		
		OilImplementBlock * Block = CurrentNS.GetUnresolvedImplementBlock ( UnresolvedOffset );
		
		bool TemplateMismatch = false;
		
		OilTypeDefinition * ImplementedTypeDef = FindTypeDefinition ( * Block -> GetImplementedType (), CurrentNS, TemplateMismatch );
		
		if ( TemplateMismatch )
			return kResolveTraitsStatus_Failure_TemplateMismatch;
		
		if ( ImplementedTypeDef == NULL )
		{
			
			UnresolvedOffset ++;
			
			continue;
			
		}
		
		if ( Block -> IsForTrait () )
		{
			
			LOG_VERBOSE ( "TRAIT IMPL" );
			
			OilTypeRef * ForTraitRef = Block -> GetForTrait ();
			
			std :: vector <std :: u32string> AbsoluteNamePath;
			TemplateMismatch = false;
			
			OilTraitDefinition * ForTrait = NULL;
			
			if ( ! OilFindAndBuildAbsoluteTraitNamePath ( AbsoluteNamePath, * ForTraitRef, CurrentNS, ForTrait, TemplateMismatch ) )
			{
				
				if ( TemplateMismatch )
					return kResolveTraitsStatus_Failure_TemplateMismatch;
				
				UnresolvedOffset ++;
				
				continue;
				
			}
			
			bool NameConflict = false;
			bool RedefinitionConflict = false;
			
			{
				
				std :: string PrintString = "";
				
				PrintString += "Adding trait to impl list: ";
				
				for ( uint32_t I = 0; I < AbsoluteNamePath.size (); I ++ )
				{
					
					PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( AbsoluteNamePath [ I ] );
					
					if ( I != AbsoluteNamePath.size () - 1 )
						PrintString += "::";
					
				}
				
				LOG_VERBOSE ( PrintString );
				
			}
			
			ImplementedTypeDef -> AddTraitImplementBlock ( & AbsoluteNamePath [ 0 ], AbsoluteNamePath.size (), Block, NameConflict, RedefinitionConflict );
			
			if ( RedefinitionConflict || NameConflict )
				return kResolveTraitsStatus_Failure_Conflict;
			
		}
		else
		{
			
			LOG_VERBOSE ( "PRINCIPAL IMPL" );
			
			ImplementedTypeDef -> SetPrincipalImplementBlock ( Block );
			
		}
		
		CurrentNS.RemoveUnresolvedImplementBlock ( UnresolvedOffset );
		
	}
	
	bool Complete = true;
	
	for ( uint32_t I = 0; I < CurrentNS.GetSubNamespaceDefinitionCount (); I ++ )
	{
		
		ResolveTraitsStatus Status = OilResolveTraits ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
		if ( Status != kResolveTraitsStatus_Success_Complete )
		{
			
			Complete = false;
			
			if ( Status != kResolveTraitsStatus_Success_Incomplete )
				return Status;
			
		}
		
	}
	
	return ( Complete && ( UnresolvedOffset == 0 ) ) ? kResolveTraitsStatus_Success_Complete : kResolveTraitsStatus_Success_Incomplete;
	
}
