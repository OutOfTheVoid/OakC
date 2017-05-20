#include <EarlyAnalysis/OilTypeResolution.h>

#include <OIL/OilTraversal.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilConstStatement.h>
#include <OIL/OilBindingStatement.h>

TypeResolutionResult OilResolveTypes_Constants ( OilNamespaceDefinition & CurrentNS, OilConstStatement *& FailedStatement )
{
	
	uint32_t ConstantCount = CurrentNS.GetConstStatementCount ();
	
	for ( uint32_t I = 0; I < ConstantCount; I ++ )
	{
		
		OilConstStatement * Statement = CurrentNS.GetConstStatement ( I );
		OilTypeRef * TypeRef = Statement -> GetType ();
		
		bool VoidType = false;
		
		while ( ! TypeRef -> IsDirectType () )
		{
			
			if ( TypeRef -> IsVoid () )
			{
				
				VoidType = true;
				
				break;
				
			}
			
			TypeRef = TypeRef -> GetSubType ();
			
		}
		
		if ( ! VoidType )
		{
			
			bool TemplateMismatch = false;
			
			OilTypeDefinition * ResolvedType = FindTypeDefinition ( * TypeRef, CurrentNS, TemplateMismatch );
			
			if ( TemplateMismatch )
			{
				
				FailedStatement = Statement;
				
				return kTypeResolutionResult_Failure_TemplateMismatch;
				
			}
			
			if ( ResolvedType != NULL )
				TypeRef -> SetResolvedTypeDefinition ( ResolvedType );
			else
			{
				
				TemplateMismatch = false;
				OilTraitDefinition * ResolvedTrait = FindTraitDefinition ( * TypeRef, CurrentNS, TemplateMismatch );
				
				if ( TemplateMismatch )
				{
					
					FailedStatement = Statement;
					
					return kTypeResolutionResult_Failure_TemplateMismatch;
					
				}
				
				if ( ResolvedTrait == NULL )
					return kTypeResolutionResult_Failure_NonExistantType;
				
				TypeRef -> SetResolvedTraitDefinition ( ResolvedTrait );
				
			}
			
		}
		
	}
	
	uint32_t SubNamespaces = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNamespaces; I ++ )
	{
		
		TypeResolutionResult Result = OilResolveTypes_Constants ( * CurrentNS.GetNamespaceDefinition ( I ), FailedStatement );
		
		if ( Result != kTypeResolutionResult_Success )
			return Result;
		
	}
	
	return kTypeResolutionResult_Success;
	
}

TypeResolutionResult OilResolveTypes_Bindings ( OilNamespaceDefinition & CurrentNS, OilBindingStatement *& FailedStatement )
{
	
	uint32_t BindingCount = CurrentNS.GetBindingStatementCount ();
	
	for ( uint32_t I = 0; I < BindingCount; I ++ )
	{
		
		OilBindingStatement * Statement = CurrentNS.GetBindingStatement ( I );
		OilTypeRef * TypeRef = Statement -> GetType ();
		
		bool VoidType = false;
		
		while ( ! TypeRef -> IsDirectType () )
		{
			
			if ( TypeRef -> IsVoid () )
			{
				
				VoidType = true;
				
				break;
				
			}
			
			TypeRef = TypeRef -> GetSubType ();
			
		}
		
		if ( ! VoidType )
		{
			
			bool TemplateMismatch = false;
			
			OilTypeDefinition * ResolvedType = FindTypeDefinition ( * TypeRef, CurrentNS, TemplateMismatch );
			
			if ( TemplateMismatch )
			{
				
				FailedStatement = Statement;
				
				return kTypeResolutionResult_Failure_TemplateMismatch;
				
			}
			
			if ( ResolvedType != NULL )
				TypeRef -> SetResolvedTypeDefinition ( ResolvedType );
			else
			{
				
				TemplateMismatch = false;
				OilTraitDefinition * ResolvedTrait = FindTraitDefinition ( * TypeRef, CurrentNS, TemplateMismatch );
				
				if ( TemplateMismatch )
				{
					
					FailedStatement = Statement;
					
					return kTypeResolutionResult_Failure_TemplateMismatch;
					
				}
				
				if ( ResolvedTrait == NULL )
					return kTypeResolutionResult_Failure_NonExistantType;
				
				TypeRef -> SetResolvedTraitDefinition ( ResolvedTrait );
				
			}
			
		}
		
	}
	
	uint32_t SubNamespaces = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNamespaces; I ++ )
	{
		
		TypeResolutionResult Result = OilResolveTypes_Bindings ( * CurrentNS.GetNamespaceDefinition ( I ), FailedStatement );
		
		if ( Result != kTypeResolutionResult_Success )
			return Result;
		
	}
	
	return kTypeResolutionResult_Success;
	
}
