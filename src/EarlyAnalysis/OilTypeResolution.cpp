#include <EarlyAnalysis/OilTypeResolution.h>

#include <OIL/OilTraversal.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilConstStatement.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>
#include <OIL/OilTemplateSpecification.h>

TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef )
{
	
	bool VoidType = false;
	
	OilTypeRef * Ref = & TypeRef;
	
	while ( ! Ref -> IsDirectType () )
	{
		
		if ( Ref -> IsVoid () )
		{
			
			VoidType = true;
			
			break;
			
		}
		
		Ref = Ref -> GetSubType ();
		
	}
	
	if ( Ref -> IsTemplated () )
	{
		
		TypeResolutionResult TemplateResult = OilTypeResolution_TemplateSpecification ( CurrentNS, * Ref -> GetTemplateSpecification () );
		
		if ( TemplateResult == kTypeResolutionResult_Success_Complete )
		{
			
			bool TemplateMismatch = false;
			
			OilTypeDefinition * ResolvedType = FindTypeDefinition ( * Ref, CurrentNS, TemplateMismatch );
			
			if ( TemplateMismatch )
				return kTypeResolutionResult_Failure_TemplateMismatch;
			
			if ( ResolvedType != NULL )
			{
				
				Ref -> SetResolvedTypeDefinition ( ResolvedType );
				
				return kTypeResolutionResult_Success_Complete;
				
			}
			else
			{
				
				TemplateMismatch = false;
				OilTraitDefinition * ResolvedTrait = FindTraitDefinition ( * Ref, CurrentNS, TemplateMismatch );
				
				if ( TemplateMismatch )
					return kTypeResolutionResult_Failure_TemplateMismatch;
				
				if ( ResolvedTrait == NULL )
					return kTypeResolutionResult_Failure_NonExistantType;
				
				Ref -> SetResolvedTraitDefinition ( ResolvedTrait );
				
			}
			
			return kTypeResolutionResult_Success_Complete;
			
		}
		
		return TemplateResult;
		
	}
	
	bool TemplateMismatch = false;
	
	OilTypeDefinition * ResolvedType = FindTypeDefinition ( * Ref, CurrentNS, TemplateMismatch );
	
	if ( TemplateMismatch )
		return kTypeResolutionResult_Failure_TemplateMismatch;
	
	if ( ResolvedType != NULL )
	{
		
		Ref -> SetResolvedTypeDefinition ( ResolvedType );
		
		return kTypeResolutionResult_Success_Complete;
		
	}
	else
	{
		
		TemplateMismatch = false;
		OilTraitDefinition * ResolvedTrait = FindTraitDefinition ( * Ref, CurrentNS, TemplateMismatch );
		
		if ( TemplateMismatch )
			return kTypeResolutionResult_Failure_TemplateMismatch;
		
		if ( ResolvedTrait == NULL )
			return kTypeResolutionResult_Failure_NonExistantType;
		
		Ref -> SetResolvedTraitDefinition ( ResolvedTrait );
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_TemplateSpecification ( OilNamespaceDefinition & CurrentNS, OilTemplateSpecification & TemplateSpecification )
{
	
	bool Unresolved = false;
	
	uint32_t ResolvedCount = 0;
	uint32_t TypeRefCount = TemplateSpecification.GetTypeRefCount ();
	
	for ( uint32_t I = 0; I < TypeRefCount; I ++ )
	{
		
		OilTypeRef * TypeRef = TemplateSpecification.GetTypeRef ( I );
		
		if ( ! TypeRef -> IsResolved () )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * TypeRef );
			
			if ( ResolutionResult != kTypeResolutionResult_Success_Complete )
			{
				
				Unresolved = true;
				
				if ( ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch ) || ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType ) )
					return ResolutionResult;
				
				if ( kTypeResolutionResult_Success_Progress )
					ResolvedCount ++;
				
			}
			else
				ResolvedCount ++;
			
		}
		
	}
	
	if ( ( ResolvedCount == 0 ) && Unresolved )
		return kTypeResolutionResult_Success_NoProgress;
	
	if ( Unresolved )
		return kTypeResolutionResult_Success_Progress;
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilResolveTypes_Constants ( OilNamespaceDefinition & CurrentNS, OilConstStatement *& FailedStatement )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t ConstantCount = CurrentNS.GetConstStatementCount ();
	
	for ( uint32_t I = 0; I < ConstantCount; I ++ )
	{
		
		OilConstStatement * Statement = CurrentNS.GetConstStatement ( I );
		OilTypeRef * TypeRef = Statement -> GetType ();
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * TypeRef );
		
		if ( ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch ) || ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType ) )
		{
			
			FailedStatement = Statement;
			
			return ResolutionResult;
			
		}
		
		if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else
			Unresolved = true;
		
	}
	
	uint32_t SubNamespaces = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNamespaces; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilResolveTypes_Constants ( * CurrentNS.GetNamespaceDefinition ( I ), FailedStatement );
		
		if ( ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch ) || ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType ) )
			return ResolutionResult;
		
		if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else
			Unresolved = true;
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	else
		return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilResolveTypes_Bindings ( OilNamespaceDefinition & CurrentNS, OilBindingStatement *& FailedStatement )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t BindingCount = CurrentNS.GetBindingStatementCount ();
	
	for ( uint32_t I = 0; I < BindingCount; I ++ )
	{
		
		OilBindingStatement * Statement = CurrentNS.GetBindingStatement ( I );
		OilTypeRef * TypeRef = Statement -> GetType ();
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * TypeRef );
		
		if ( ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch ) || ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType ) )
		{
			
			FailedStatement = Statement;
			
			return ResolutionResult;
			
		}
		
		if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else
			Unresolved = true;
		
	}
	
	uint32_t SubNamespaces = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNamespaces; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilResolveTypes_Bindings ( * CurrentNS.GetNamespaceDefinition ( I ), FailedStatement );
		
		if ( ( ResolutionResult == kTypeResolutionResult_Failure_TemplateMismatch ) || ( ResolutionResult == kTypeResolutionResult_Failure_NonExistantType ) )
			return ResolutionResult;
		
		if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else
			Unresolved = true;
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	else
		return kTypeResolutionResult_Success_Complete;
	
}

// TODO
/*TypeResolutionResult OilResolveTypes_StructBindings ( OilNamespaceDefinition & RootNS, OilStructDefinition *& FailedStruct, std :: u32string & FailedBindingName )
{
	
	uint32_t TypeCount = CurrentNS.TypeDefinition ();
	
	for ( uint32_t I = 0; I < TypeCount; I ++ )
	{
		
		OilTypeDefinition * Type = CurrentNS.GetTypeDefininition ( I );
		
		if ( ! Type -> IsBuiltinStructure () )
		{
			
			
			
		}
		
	}
	
}*/
