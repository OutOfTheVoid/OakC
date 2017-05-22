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
#include <OIL/OilBuiltinStructDefinition.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilTemplateDefinition.h>

#include <Logging/Logging.h>
#include <Encoding/CodeConversion.h>

TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef, TypeResolution_TemplateNameList * TemplateNames )
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
		
		TypeResolutionResult TemplateResult = OilTypeResolution_TemplateSpecification ( CurrentNS, * Ref -> GetTemplateSpecification (), TemplateNames );
		
		if ( TemplateResult == kTypeResolutionResult_Success_Complete )
		{
			
			bool TemplateMismatch = false;
			
			OilTypeDefinition * ResolvedType = FindTypeDefinition ( * Ref, CurrentNS, TemplateMismatch );
			
			if ( TemplateMismatch )
			{
				
				LOG_FATALERROR_NOFILE ( std :: string ( "Template mismatch: template of reference to " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
				
				return kTypeResolutionResult_Failure_TemplateMismatch;
				
			}
			
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
				{
					
					LOG_FATALERROR_NOFILE ( std :: string ( "Template mismatch: reference to template of " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
					
					return kTypeResolutionResult_Failure_TemplateMismatch;
					
				}
				
				if ( ResolvedTrait == NULL )
				{
					
					LOG_FATALERROR_NOFILE ( std :: string ( "Type not found: " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) );
					
					return kTypeResolutionResult_Failure_NonExistantType;
					
				}
				
				Ref -> SetResolvedTraitDefinition ( ResolvedTrait );
				
			}
			
			return kTypeResolutionResult_Success_Complete;
			
		}
		
		return TemplateResult;
		
	}
	
	bool TemplateMismatch = false;
	
	OilTypeDefinition * ResolvedType = FindTypeDefinition ( * Ref, CurrentNS, TemplateMismatch );
	
	if ( TemplateMismatch )
	{
		
		LOG_FATALERROR_NOFILE ( std :: string ( "Template mismatch: template of reference to " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
		
		return kTypeResolutionResult_Failure_TemplateMismatch;
		
	}
	
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
		{
			
			LOG_FATALERROR_NOFILE ( std :: string ( "Template mismatch: template of reference to " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
			
			return kTypeResolutionResult_Failure_TemplateMismatch;
			
		}
		
		if ( ResolvedTrait == NULL )
		{
			
			if ( TemplateNames != NULL )
			{
				
				if ( ! ( Ref -> IsNamespaced () || Ref -> IsTemplated () ) )
				{
					
					for ( uint32_t I = 0; I < TemplateNames -> Count; I ++ )
					{
						
						if ( Ref -> GetName () == TemplateNames -> Names [ I ] )
						{
							
							Ref -> SetResolvedTemplateParamName ();
							
							return kTypeResolutionResult_Success_Complete;
							
						}
						
					}
					
				}
				
			}
			
			LOG_FATALERROR_NOFILE ( std :: string ( "Type not found: " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) );
			
			return kTypeResolutionResult_Failure_NonExistantType;
			
		}
		
		Ref -> SetResolvedTraitDefinition ( ResolvedTrait );
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_TemplateSpecification ( OilNamespaceDefinition & CurrentNS, OilTemplateSpecification & TemplateSpecification, TypeResolution_TemplateNameList * TemplateNames )
{
	
	bool Unresolved = false;
	
	uint32_t ResolvedCount = 0;
	uint32_t TypeRefCount = TemplateSpecification.GetTypeRefCount ();
	
	for ( uint32_t I = 0; I < TypeRefCount; I ++ )
	{
		
		OilTypeRef * TypeRef = TemplateSpecification.GetTypeRef ( I );
		
		if ( ! TypeRef -> IsResolved () )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * TypeRef, TemplateNames );
			
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

TypeResolutionResult OilTypeResolution_TemplateDefinition ( OilNamespaceDefinition & CurrentNS, OilTemplateDefinition & TemplateDefinition )
{
	
	bool Unresolved = false;
	
	uint32_t ResolvedCount = 0;
	uint32_t ParamCount = TemplateDefinition.GetTemplateParameterCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OilTemplateDefinitionParameter * Param = TemplateDefinition.GetTemplateParameter ( I );
		
		if ( Param -> IsRestricted () )
		{
			
			uint32_t RestrictionCount = Param -> GetRestrictionCount ();
			
			for ( uint32_t J = 0; J < RestrictionCount; J ++ )
			{
				
				OilTypeRef * RestrictType = Param -> GetRestriction ( J );
				
				if ( ! RestrictType -> IsResolved () )
				{
					
					TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * RestrictType, NULL );
					
					if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
					{
						
						ResolvedCount ++;
						
						if ( ! RestrictType -> IsResolvedAsTrait () )
						{
							
							LOG_FATALERROR_NOFILE ( "Template restrictions cannot reference non-trait types" );
							
							return kTypeResolutionResult_Failure_NonExistantType;
							
						}
						
					}
					else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
					{
						
						ResolvedCount ++;
						Unresolved = true;
						
					}
					else if ( ResolutionResult == kTypeResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return ResolutionResult;
					
				}
				
			}
			
		}
		
	}
	
	if ( Unresolved )
	{
		
		if ( ResolvedCount > 0 )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilResolveTypes_Constants ( OilNamespaceDefinition & CurrentNS )
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
	
	uint32_t SubNamespaces = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNamespaces; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilResolveTypes_Constants ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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

TypeResolutionResult OilResolveTypes_Bindings ( OilNamespaceDefinition & CurrentNS )
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
	
	uint32_t SubNamespaces = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNamespaces; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilResolveTypes_Bindings ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
		if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return ResolutionResult;
		
		
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

TypeResolutionResult OilResolveTypes_StructDefinitions ( OilNamespaceDefinition & CurrentNS )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t TypeDefCount = CurrentNS.GetTypeDefinitionCount ();
	
	for ( uint32_t I = 0; I < TypeDefCount; I ++ )
	{
		
		OilTypeDefinition * TypeDef = CurrentNS.GetTypeDefinition ( I );
		OilStructDefinition * StructDef = NULL;
		OilTemplateDefinition * TemplateDef = NULL;
		
		if ( TypeDef -> IsBuiltinStructure () )
		{
			
			OilBuiltinStructDefinition * BuiltinStructDef = TypeDef -> GetBuiltinStructDefinition ();
			
			if ( ! BuiltinStructDef -> HasUnderlyingStructure () )
				continue;
			
			StructDef = BuiltinStructDef -> GetUnderlyingStructure ();
			
			if ( BuiltinStructDef -> IsTemplated () )
				TemplateDef = BuiltinStructDef -> GetTemplateDefinition ();
			
		}
		else
			StructDef = TypeDef -> GetStructDefinition ();
		
		if ( StructDef -> IsTemplated () )
			TemplateDef = StructDef -> GetTemplateDefinition ();
		
		TypeResolution_TemplateNameList TemplateNames;
		
		if ( TemplateDef != NULL )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TemplateDefinition ( CurrentNS, * TemplateDef );
			
			if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
				continue;
				
			}
			else if ( ResolutionResult == kTypeResolutionResult_Success_NoProgress )
			{
				
				Unresolved = true;
				
				continue;
				
			}
			else
				return ResolutionResult;
			
			uint32_t NameCount = TemplateDef -> GetTemplateParameterCount ();
			
			TemplateNames.Names = new std :: u32string [ NameCount ];
			TemplateNames.Count = NameCount;
			
			for ( uint32_t J = 0; J < NameCount; J ++ )
				TemplateNames.Names [ J ] = TemplateDef -> GetTemplateParameter ( J ) -> GetName ();
			
		}
		
		uint32_t StructMemberCount = StructDef -> GetBindingCount ();
		
		for ( uint32_t J = 0; J < StructMemberCount; J ++ )
		{
			
			OilStructBinding * Binding = StructDef -> GetBinding ( J );
			OilTypeRef * BindingTypeRef = Binding -> GetTypeRef ();
			
			if ( BindingTypeRef -> IsResolved () )
				continue;
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * BindingTypeRef, & TemplateNames );
			
			if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( ResolutionResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
			{
				
				if ( TemplateDef != NULL )
					delete [] TemplateNames.Names;
				
				return ResolutionResult;
				
			}
			
		}
		
		if ( TemplateDef != NULL )
			delete [] TemplateNames.Names;
		
	}
	
	uint32_t SubNSCount = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilResolveTypes_StructDefinitions ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
		if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( ResolutionResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return ResolutionResult;
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}
