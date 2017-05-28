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
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilMethodDefinition.h>
#include <OIL/OilMethodParameterList.h>
#include <OIL/OilTypeAlias.h>

#include <Logging/Logging.h>
#include <Logging/ErrorUtils.h>
#include <Encoding/CodeConversion.h>

TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef, TypeResolution_TemplateNameList * TemplateNames, OilTypeDefinition * SelfType, OilTemplateSpecification * SelfTemplateSpec )
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
				
				LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Template mismatch: template of reference to " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
				
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
					
					LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Template mismatch: reference to template of " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
					
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
		
		LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Template mismatch: template of reference to " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
		
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
			
			LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Template mismatch: template of reference to " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
			
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
			
			if ( SelfType != NULL )
			{
				
				// TODO: Localize Self
				if ( ( Ref -> GetName () == U"Self" ) && ( ! Ref -> IsNamespaced () ) )
				{
					
					if ( Ref -> IsTemplated () )
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Self type reference cannot have template specification" );
						
						return kTypeResolutionResult_Failure_TemplateMismatch;
						
					}
					
					Ref -> SetResolvedTypeDefinition ( SelfType );
					Ref -> SetTemplateSpecification ( SelfTemplateSpec );
					
					return kTypeResolutionResult_Success_Complete;
					
				}
				
			}
			
			LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Type not found: " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) );
			
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

TypeResolutionResult OilTypeResolution_TemplateDefinition ( OilNamespaceDefinition & CurrentNS, OilTemplateDefinition & TemplateDefinition, TypeResolution_TemplateNameList * TemplateNames )
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
					
					TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * RestrictType, TemplateNames );
					
					if ( ResolutionResult == kTypeResolutionResult_Success_Complete )
					{
						
						ResolvedCount ++;
						
						if ( ! RestrictType -> IsResolvedAsTrait () )
						{
							
							LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( RestrictType -> GetSourceRef () ) + "Template restrictions cannot reference non-trait types" );
							
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

TypeResolutionResult OilTypeResolution_Constants ( OilNamespaceDefinition & CurrentNS )
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
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_Constants ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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

TypeResolutionResult OilTypeResolution_Bindings ( OilNamespaceDefinition & CurrentNS )
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
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_Bindings ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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

TypeResolutionResult OilTypeResolution_StructDefinitions ( OilNamespaceDefinition & CurrentNS )
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
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_StructDefinitions ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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

TypeResolutionResult OilTypeResolution_Functions ( OilNamespaceDefinition & CurrentNS )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t FunctionCount = CurrentNS.GetFunctionDefinitionCount ();
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
	{
		
		OilFunctionDefinition * Definition = CurrentNS.GetFunctionDefinition ( I );
		
		TypeResolution_TemplateNameList TemplateNames;
		
		if ( Definition -> IsTemplated () )
		{
			
			OilTemplateDefinition * TemplateDef = Definition -> GetTemplateDefinition ();
			
			uint32_t TemplateParamCount = TemplateDef -> GetTemplateParameterCount ();
			
			TemplateNames.Names = new std :: u32string [ TemplateParamCount ];
			TemplateNames.Count = TemplateParamCount;
			
			for ( uint32_t J = 0; J < TemplateParamCount; J ++ )
				TemplateNames.Names [ J ] = TemplateDef -> GetTemplateParameter ( J ) -> GetName ();
			
		}
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_FunctionDefinition ( CurrentNS, * Definition, Definition -> IsTemplated () ? & TemplateNames : NULL );
		
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
			
			if ( Definition -> IsTemplated () )
				delete [] TemplateNames.Names;
			
			return ResolutionResult;
			
		}
		
	}
	
	uint32_t SubNSCount = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_Functions ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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

TypeResolutionResult OilTypeResolution_FunctionDefinition ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Definition, TypeResolution_TemplateNameList * TemplateNames, OilTypeDefinition * SelfType, OilTemplateSpecification * SelfTemplateSpec )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	if ( ! Definition.GetReturnType () -> IsResolved () )
	{
		
		TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * Definition.GetReturnType (), TemplateNames, SelfType, SelfTemplateSpec );
		
		if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return ReturnTypeResolutionResult;
			
	}
		
	OilFunctionParameterList * ParameterList = Definition.GetParameterList ();
	
	uint32_t ParamCount = ParameterList -> GetParameterCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OilFunctionParameter * Parameter = ParameterList -> GetFunctionParameter ( I );
		OilTypeRef * ParamType = Parameter -> GetType ();
		
		if ( ! ParamType -> IsResolved () )
		{
			
			TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * ParamType, TemplateNames, SelfType, SelfTemplateSpec );
			
			if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ReturnTypeResolutionResult;
			
		}
		
	}
	
	// TODO: try and resolve struct bodies
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_MethodDefinition ( OilNamespaceDefinition & CurrentNS, OilMethodDefinition & Definition, OilTypeDefinition & SelfType, OilTemplateSpecification * SelfTemplateSpec, TypeResolution_TemplateNameList * TemplateNames )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	if ( ! Definition.GetReturnType () -> IsResolved () )
	{
		
		TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * Definition.GetReturnType (), TemplateNames, & SelfType, SelfTemplateSpec );
		
		if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return ReturnTypeResolutionResult;
			
	}
		
	OilMethodParameterList * ParameterList = Definition.GetParameterList ();
	
	uint32_t ParamCount = ParameterList -> GetParameterCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OilFunctionParameter * Parameter = ParameterList -> GetFunctionParameter ( I );
		OilTypeRef * ParamType = Parameter -> GetType ();
		
		if ( ! ParamType -> IsResolved () )
		{
			
			TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * ParamType, TemplateNames, & SelfType, SelfTemplateSpec );
			
			if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( ReturnTypeResolutionResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ReturnTypeResolutionResult;
			
		}
		
	}
	
	// TODO: try and resolve struct bodies
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_TypeAlias ( OilNamespaceDefinition & CurrentNS, OilTypeAlias & Alias )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	TypeResolution_TemplateNameList TemplateNames;
	
	if ( Alias.IsTemplated () )
	{
		
		OilTemplateDefinition * TemplateDef = Alias.GetTemplateDefinition ();
		
		uint32_t TemplateParamCount = TemplateDef -> GetTemplateParameterCount ();
		
		TemplateNames.Names = new std :: u32string [ TemplateParamCount ];
		TemplateNames.Count = TemplateParamCount;
		
		for ( uint32_t I = 0; I < TemplateParamCount; I ++ )
			TemplateNames.Names [ I ] = TemplateDef -> GetTemplateParameter ( I ) -> GetName ();
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TemplateDefinition ( CurrentNS, * TemplateDef, & TemplateNames );
		
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
			
			if ( Alias.IsTemplated () )
				delete [] TemplateNames.Names;
			
			return ResolutionResult;
			
		}
		
	}
	
	if ( ! Alias.GetAliasedType () -> IsResolved () )
	{
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * Alias.GetAliasedType (), Alias.IsTemplated () ? & TemplateNames : NULL );
		
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
			
			if ( Alias.IsTemplated () )
				delete [] TemplateNames.Names;
			
			return ResolutionResult;
			
		}
		
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

TypeResolutionResult OilTypeResolution_ImplementMembers ( OilNamespaceDefinition & CurrentNS )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t TypeCount = CurrentNS.GetTypeDefinitionCount ();
	
	for ( uint32_t I = 0; I < TypeCount; I ++ )
	{
		
		OilTypeDefinition * TypeDefinition = CurrentNS.GetTypeDefinition ( I );
		
		std :: vector <OilImplementBlock *> ImplementBlocks;
		TypeDefinition -> GetAllImplementBlocks ( ImplementBlocks );
		
		uint32_t BlockCount = ImplementBlocks.size ();
		
		for ( uint32_t J = 0; J < BlockCount; J ++ )
		{
			
			OilImplementBlock * Block = ImplementBlocks [ J ];
			
			TypeResolution_TemplateNameList TemplateNames;
		
			if ( Block -> HasWhereDefinition () )
			{
				
				OilTemplateDefinition * TemplateDef = Block -> GetWhereDefinition ();
				
				uint32_t TemplateParamCount = TemplateDef -> GetTemplateParameterCount ();
				
				TemplateNames.Names = new std :: u32string [ TemplateParamCount ];
				TemplateNames.Count = TemplateParamCount;
				
				for ( uint32_t K = 0; K < TemplateParamCount; K ++ )
					TemplateNames.Names [ K ] = TemplateDef -> GetTemplateParameter ( K ) -> GetName ();
				
			}
			
			uint32_t FunctionCount = Block -> GetFunctionCount ();
			
			for ( uint32_t K = 0; K < FunctionCount; K ++ )
			{
				
				OilFunctionDefinition * FunctionDefinition = Block -> GetFunction ( K );
				
				TypeResolutionResult FunctionResolutionResult = OilTypeResolution_FunctionDefinition ( CurrentNS, * FunctionDefinition, Block -> HasWhereDefinition () ? & TemplateNames : NULL, TypeDefinition, Block -> GetImplementedType () -> GetTemplateSpecification () );
				
				if ( FunctionResolutionResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( FunctionResolutionResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( FunctionResolutionResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
				{
					
					if ( Block -> HasWhereDefinition () )
						delete [] TemplateNames.Names;
					
					return FunctionResolutionResult;
					
				}
				
			}
			
			uint32_t MethodCount = Block -> GetMethodCount ();
			
			for ( uint32_t K = 0; K < MethodCount; K ++ )
			{
				
				OilMethodDefinition * MethodDefinition = Block -> GetMethod ( K );
				
				TypeResolutionResult MethodResolutionResult = OilTypeResolution_MethodDefinition ( CurrentNS, * MethodDefinition, * TypeDefinition, Block -> GetImplementedType () -> GetTemplateSpecification (), Block -> HasWhereDefinition () ? & TemplateNames : NULL );
				
				if ( MethodResolutionResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( MethodResolutionResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( MethodResolutionResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
				{
					
					if ( Block -> HasWhereDefinition () )
						delete [] TemplateNames.Names;
					
					return MethodResolutionResult;
					
				}
				
			}
			
		}
		
	}
	
	uint32_t SubNSCount = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_ImplementMembers ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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

TypeResolutionResult OilTypeResolution_TypeAliases ( OilNamespaceDefinition & CurrentNS )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t AliasCount = CurrentNS.GetTypeAliasCount ();
	
	for ( uint32_t I = 0; I < AliasCount; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TypeAlias ( CurrentNS, * CurrentNS.GetTypeAlias ( I ) );
		
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
	
	uint32_t SubNSCount = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TypeAliases ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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
