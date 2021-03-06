#include <EarlyAnalysis/OilImplementResolution.h>
#include <EarlyAnalysis/OilTypeResolution.h>
#include <EarlyAnalysis/OilAnalysisTools.h>

#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTraversal.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>

#include <Logging/Logging.h>
#include <Encoding/CodeConversion.h>

ResolveImplementsStatus OilResolveImplements ( OilNamespaceDefinition & CurrentNS )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	uint32_t UnresolvedOffset = 0;
	
	while ( CurrentNS.GetUnresolvedImplementBlockCount () > UnresolvedOffset )
	{
		
		OilImplementBlock * Block = CurrentNS.GetUnresolvedImplementBlock ( CurrentNS.GetUnresolvedImplementBlockCount () - UnresolvedOffset - 1 );
		OilTypeRef * ImplementedTypeRef = Block -> GetImplementedType ();
		
		FlatNameList TemplateNames;
		
		bool UseWhere = Block -> HasWhereDefinition ();
		
		if ( UseWhere )
		{
			
			OilTemplateDefinition * WhereDefinition = Block -> GetWhereDefinition ();
			
			MakeNameList_TemplateDefinition ( * WhereDefinition, TemplateNames );
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TemplateDefinition ( CurrentNS, * WhereDefinition, & TemplateNames );
			
			if ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				return kResolveImplementsStatus_Failure_TemplateMismatch;
				
			}
			
			if ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				return kResolveImplementsStatus_Failure_NonExistantType;
				
			}
			
			if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( kTypeResolutionResult_Success_Progress )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				Progress = true;
				UnresolvedOffset ++;
				
				continue;
				
			}
			else
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				UnresolvedOffset ++;
				
				continue;
				
			}
			
		}
		
		if ( ! ImplementedTypeRef -> IsResolved () )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * ImplementedTypeRef, UseWhere ? ( & TemplateNames ) : NULL );
			
			if ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				return kResolveImplementsStatus_Failure_TemplateMismatch;
				
			}
			
			if ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				return kResolveImplementsStatus_Failure_NonExistantType;
				
			}
			
			if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( kTypeResolutionResult_Success_Progress )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				Progress = true;
				UnresolvedOffset ++;
				
				continue;
				
			}
			else
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				UnresolvedOffset ++;
				
				continue;
				
			}
			
		}
		
		if ( ImplementedTypeRef -> IsResolvedAsTrait () )
		{
			
			LOG_FATALERROR_NOFILE ( std :: string ( "Implement block attemptings to implement trait type: " ) + CodeConversion :: ConvertUTF32ToUTF8 ( ImplementedTypeRef -> GetName () ) );
			
			return kResolveImplementsStatus_Failure_ImplementingTrait;
			
		}
		
		if ( ImplementedTypeRef -> IsResolvedAsTemplateParam () )
		{
			
			LOG_FATALERROR_NOFILE ( std :: string ( "Implement block attemptings to implement template parameter: " ) + CodeConversion :: ConvertUTF32ToUTF8 ( ImplementedTypeRef -> GetName () ) );
			
			return kResolveImplementsStatus_Failure_ImplementingTemplateParam;
			
		}
		
		OilTypeDefinition * ImplementedType = ImplementedTypeRef -> GetResolvedTypeDefinition ();
		
		if ( Block -> IsForTrait () )
		{
			
			OilTypeRef * TraitRef = Block -> GetForTrait ();
			
			if ( ! TraitRef -> IsResolved () )
			{
				
				TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * TraitRef, UseWhere ? ( & TemplateNames ) : NULL );
				
				if ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch )
				{
					
					DestroyFlatNameList ( TemplateNames );
					
					return kResolveImplementsStatus_Failure_TemplateMismatch;
					
				}
				
				if ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType )
				{
					
					DestroyFlatNameList ( TemplateNames );
					
					return kResolveImplementsStatus_Failure_NonExistantType;
					
				}
				
				if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( kTypeResolutionResult_Success_Progress )
				{
					
					DestroyFlatNameList ( TemplateNames );
					
					Progress = true;
					UnresolvedOffset ++;
					
					continue;
					
				}
				else
				{
					
					DestroyFlatNameList ( TemplateNames );
					
					UnresolvedOffset ++;
					
					continue;
					
				}
				
				DestroyFlatNameList ( TemplateNames );
					
			}
			
			if ( ! TraitRef -> IsResolvedAsTrait () )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				LOG_FATALERROR_NOFILE ( std :: string ( "Implement block attempts to implement type: " ) + CodeConversion :: ConvertUTF32ToUTF8 ( ImplementedTypeRef -> GetName () ) + " for a non-trait type: " + CodeConversion :: ConvertUTF32ToUTF8 ( TraitRef -> GetName () ) );
				
				return kResolveImplementsStatus_Failure_ImplementedForNonTrait;
				
			}
			
			std :: vector <std :: u32string> AbsoluteNamePath;
			
			BuildAbsoluteNamePath_Trait ( AbsoluteNamePath, * TraitRef -> GetResolvedTraitDefinition () );
			
			bool NameConflict = false;
			
			ImplementedType -> AddTraitImplementBlock ( & AbsoluteNamePath [ 0 ], AbsoluteNamePath.size (), Block, NameConflict );
			
			if ( NameConflict )
			{
				
				DestroyFlatNameList ( TemplateNames );
				
				LOG_FATALERROR_NOFILE ( std :: string ( "Name of implemented trait: " ) + CodeConversion :: ConvertUTF32ToUTF8 ( TraitRef -> GetName () ) + " conflicts with namespace of the same name of previous implemented trait" );
				
				return kResolveImplementsStatus_Failure_Conflict_TraitImplementation_NamespaceCollision;
				
			}
			
		}
		else
			ImplementedType -> AddPrincipalImplementBlock ( Block );
		
		DestroyFlatNameList ( TemplateNames );
		
		CurrentNS.RemoveUnresolvedImplementBlock ( CurrentNS.GetUnresolvedImplementBlockCount () - UnresolvedOffset - 1 );
		
	}
	
	Unresolved = CurrentNS.GetUnresolvedImplementBlockCount () != 0;
	
	ResolveImplementsStatus SubStatus;
	
	for ( uint32_t I = 0; I < CurrentNS.GetSubNamespaceDefinitionCount (); I ++ )
	{
		
		SubStatus = OilResolveImplements ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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
