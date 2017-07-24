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
#include <OIL/OilStatementBody.h>
#include <OIL/IOilStatement.h>
#include <OIL/OilIfElse.h>
#include <OIL/OilLoop.h>
#include <OIL/OilWhileLoop.h>
#include <OIL/OilDoWhileLoop.h>
#include <OIL/OilExpression.h>
#include <OIL/OilReturn.h>
#include <OIL/OilImplicitLocalInitialization.h>
#include <OIL/OilImplicitBindingInitialization.h>
#include <OIL/OilUnaryOperator.h>
#include <OIL/OilBinaryOperator.h>
#include <OIL/IOilPrimary.h>
#include <OIL/OilAllusion.h>
#include <OIL/OilArrayLiteral.h>
#include <OIL/OilFunctionCallParameterList.h>
#include <OIL/OilStructLiteral.h>
#include <OIL/OilStructInitializerValue.h>
#include <OIL/OilTraitFunction.h>
#include <OIL/OilTraitMethod.h>
#include <OIL/OilEnum.h>
#include <OIL/OilMatch.h>
#include <OIL/OilMatchBranch.h>

#include <Logging/Logging.h>
#include <Logging/ErrorUtils.h>
#include <Encoding/CodeConversion.h>

TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef, FlatNameList * TemplateNames, OilTypeDefinition * SelfType, OilTraitDefinition * SelfTrait )
{
	
	if ( TypeRef.IsResolved () )
		return kTypeResolutionResult_Success_Complete;
	
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
	
	if ( VoidType )
		return kTypeResolutionResult_Success_Complete;
	
	if ( Ref -> IsTemplated () )
	{
		
		TypeResolutionResult TemplateResult = OilTypeResolution_TemplateSpecification ( CurrentNS, * Ref -> GetTemplateSpecification (), TemplateNames, SelfType );
		
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
			
			OilTypeAlias * ResolvedAlias = FindTypeAlias ( * Ref, CurrentNS, TemplateMismatch );
			
			if ( TemplateMismatch )
			{
				
				LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Template mismatch: template of reference to " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
				
				return kTypeResolutionResult_Failure_TemplateMismatch;
				
			}
			
			if ( ResolvedAlias != NULL )
			{
				
				OilTypeRef * ResolvedType = ResolvedAlias -> GetAliasedType ();
				
				if ( ! ResolvedType -> IsResolved () )
					return kTypeResolutionResult_Success_NoProgress;
				
				OilTemplateSpecification * NewSpecification = NULL;
				
				if ( ResolvedType -> IsTemplated () )
				{
					
					OilTemplateDefinition * OldDefinition = ResolvedAlias -> GetTemplateDefinition ();
					OilTemplateSpecification * OldSpecification = ResolvedType -> GetTemplateSpecification ();
					
					std :: vector <OilTypeRef *> SpecificationTypes;
					
					for ( uint32_t I = 0; I < OldSpecification -> GetTypeRefCount (); I ++ )
					{
						
						OilTypeRef * OldTemplateParam = OldSpecification -> GetTypeRef ( I );
						
						if ( ! OldTemplateParam -> IsResolved () )
						{
							
							for ( uint32_t J = 0; J < SpecificationTypes.size (); J ++ )
								delete SpecificationTypes [ J ];
							
							return kTypeResolutionResult_Success_NoProgress;
							
						}
						
						if ( OldTemplateParam -> IsResolvedAsTemplateParam () )
						{
							
							uint32_t Index;
							uint32_t ParamCount = OldDefinition -> GetTemplateParameterCount ();
							
							for ( Index = 0; Index < ParamCount; Index ++ )
							{
								
								OilTemplateDefinitionParameter * DefinitionParam = OldDefinition -> GetTemplateParameter ( Index );
								
								if ( OldTemplateParam -> GetName () == DefinitionParam -> GetName () )
								{
									
									SpecificationTypes.push_back ( new OilTypeRef ( OldTemplateParam -> GetSourceRef (), * OldSpecification -> GetTypeRef ( Index ) ) );
									
									break;
									
								}
								
							}
								
						}
						else
						{
							
							SpecificationTypes.push_back ( new OilTypeRef ( OldTemplateParam -> GetSourceRef (), * OldTemplateParam ) );
							
						}
						
					}
					
					NewSpecification = new OilTemplateSpecification ( Ref -> GetSourceRef (), & SpecificationTypes [ 0 ], SpecificationTypes.size () );
					
				}
				
				Ref -> SetResolvedTypeWithTemplateSpec ( ResolvedType -> GetResolvedTypeDefinition (), NewSpecification );
				
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
					
					LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Type not found: " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) );
					
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
	
	OilTypeAlias * ResolvedAlias = FindTypeAlias ( * Ref, CurrentNS, TemplateMismatch );
	
	if ( TemplateMismatch )
	{
		
		LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Template mismatch: template of reference to " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) + " does not match definition." );
		
		return kTypeResolutionResult_Failure_TemplateMismatch;
		
	}
	
	if ( ResolvedAlias != NULL )
	{
		
		OilTypeRef * ResolvedType = ResolvedAlias -> GetAliasedType ();
		
		if ( ! ResolvedType -> IsResolved () )
			return kTypeResolutionResult_Success_NoProgress;
		
		OilTemplateSpecification * NewSpecification = NULL;
		
		if ( ResolvedType -> IsTemplated () )
		{
			
			OilTemplateSpecification * OldSpecification = ResolvedType -> GetTemplateSpecification ();
			
			std :: vector <OilTypeRef *> SpecificationTypes;
			
			for ( uint32_t I = 0; I < OldSpecification -> GetTypeRefCount (); I ++ )
			{
				
				OilTypeRef * OldTemplateParam = OldSpecification -> GetTypeRef ( I );
				
				if ( ! OldTemplateParam -> IsResolved () )
				{
					
					for ( uint32_t J = 0; J < SpecificationTypes.size (); J ++ )
						delete SpecificationTypes [ J ];
						
					return kTypeResolutionResult_Success_NoProgress;
					
				}
				
				SpecificationTypes.push_back ( new OilTypeRef ( OldTemplateParam -> GetSourceRef (), * OldTemplateParam ) );
				
			}
			
			NewSpecification = new OilTemplateSpecification ( Ref -> GetSourceRef (), & SpecificationTypes [ 0 ], SpecificationTypes.size () );
			
		}
		
		Ref -> SetResolvedTypeWithTemplateSpec ( ResolvedType -> GetResolvedTypeDefinition (), NewSpecification );
		
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
			
			if ( ( SelfType != NULL ) || ( SelfTrait != NULL ) )
			{
				
				if ( ( Ref -> GetName () == U"Self" ) && ( ! Ref -> IsNamespaced () ) )
				{
					
					if ( Ref -> IsTemplated () )
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Self type reference cannot have template specification" );
						
						return kTypeResolutionResult_Failure_TemplateMismatch;
						
					}
					
					if ( SelfType != NULL )
						Ref -> SetResolvedAsSelf ( SelfType );
					else
						Ref -> SetResolvedAsSelfAbstract ();
					
					return kTypeResolutionResult_Success_Complete;
					
				}
				
			}
			
			if ( Ref -> GetName () == U"void" )
			{
				
				Ref -> SetResolvedVoid ();
				
				return kTypeResolutionResult_Success_Complete;
				
			}
			
			LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Ref -> GetSourceRef () ) + "Type not found: " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref -> GetName () ) );
			
			return kTypeResolutionResult_Failure_NonExistantType;
			
		}
		
		Ref -> SetResolvedTraitDefinition ( ResolvedTrait );
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_TemplateSpecification ( OilNamespaceDefinition & CurrentNS, OilTemplateSpecification & TemplateSpecification, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Unresolved = false;
	
	uint32_t ResolvedCount = 0;
	uint32_t TypeRefCount = TemplateSpecification.GetTypeRefCount ();
	
	for ( uint32_t I = 0; I < TypeRefCount; I ++ )
	{
		
		OilTypeRef * TypeRef = TemplateSpecification.GetTypeRef ( I );
		
		if ( ! TypeRef -> IsResolved () )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * TypeRef, TemplateNames, SelfType );
			
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

TypeResolutionResult OilTypeResolution_TemplateDefinition ( OilNamespaceDefinition & CurrentNS, OilTemplateDefinition & TemplateDefinition, FlatNameList * TemplateNames )
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

TypeResolutionResult OilTypeResolution_TypeDefinitions ( OilNamespaceDefinition & CurrentNS )
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
		else if ( TypeDef -> IsEnumType () )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_Enum ( CurrentNS, * TypeDef -> GetEnum () );
			
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
			
			continue;
			
		}
		else
			StructDef = TypeDef -> GetStructDefinition ();
		
		if ( StructDef -> IsTemplated () )
			TemplateDef = StructDef -> GetTemplateDefinition ();
		
		FlatNameList TemplateNames;
		
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
			
			MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
			
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
				
				DestroyFlatNameList ( TemplateNames );
				
				return ResolutionResult;
				
			}
			
		}
		
		DestroyFlatNameList ( TemplateNames );
		
	}
	
	uint32_t SubNSCount = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TypeDefinitions ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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
	
	TypeResolutionResult ResolutionResult = OilTypeResolution_StatementBody ( CurrentNS, CurrentNS.GetImplicitInitializationBody (), NULL );
	
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
	
	uint32_t FunctionCount = CurrentNS.GetFunctionDefinitionCount ();
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
	{
		
		OilFunctionDefinition * Definition = CurrentNS.GetFunctionDefinition ( I );
		
		FlatNameList TemplateNames;
		
		if ( Definition -> IsTemplated () )
		{
			
			OilTemplateDefinition * TemplateDef = Definition -> GetTemplateDefinition ();
			
			MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
			
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
			
			DestroyFlatNameList ( TemplateNames );
			
			return ResolutionResult;
			
		}
		
		DestroyFlatNameList ( TemplateNames );
		
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

TypeResolutionResult OilTypeResolution_FunctionDefinition ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Definition, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	if ( ! Definition.GetReturnType () -> IsResolved () )
	{
		
		TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * Definition.GetReturnType (), TemplateNames, SelfType );
		
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
			
			TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * ParamType, TemplateNames, SelfType );
			
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
	
	OilStatementBody * Body = Definition.GetStatementBody ();
	
	TypeResolutionResult BodyTypeResolutionResult = OilTypeResolution_StatementBody ( CurrentNS, * Body, TemplateNames, SelfType );
	
	if ( BodyTypeResolutionResult == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( BodyTypeResolutionResult == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( BodyTypeResolutionResult == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
		return BodyTypeResolutionResult;
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_MethodDefinition ( OilNamespaceDefinition & CurrentNS, OilMethodDefinition & Definition, OilTypeDefinition * SelfType, FlatNameList * TemplateNames )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	if ( ! Definition.GetReturnType () -> IsResolved () )
	{
		
		TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * Definition.GetReturnType (), TemplateNames, SelfType );
		
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
			
			TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * ParamType, TemplateNames, SelfType );
			
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
	
	OilStatementBody * Body = Definition.GetStatementBody ();
	
	TypeResolutionResult BodyTypeResolutionResult = OilTypeResolution_StatementBody ( CurrentNS, * Body, TemplateNames, SelfType );
	
	if ( BodyTypeResolutionResult == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( BodyTypeResolutionResult == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( BodyTypeResolutionResult == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
		return BodyTypeResolutionResult;
	
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
	
	FlatNameList TemplateNames;
	
	if ( Alias.IsTemplated () )
	{
		
		OilTemplateDefinition * TemplateDef = Alias.GetTemplateDefinition ();
		
		MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
		
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
			
			DestroyFlatNameList ( TemplateNames );
			
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
			
			DestroyFlatNameList ( TemplateNames );
			
			return ResolutionResult;
			
		}
		
	}
	
	DestroyFlatNameList ( TemplateNames );
	
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
			
			FlatNameList TemplateNames;
		
			if ( Block -> HasWhereDefinition () )
			{
				
				OilTemplateDefinition * TemplateDef = Block -> GetWhereDefinition ();
				
				MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
				
			}
			
			uint32_t FunctionCount = Block -> GetFunctionCount ();
			
			for ( uint32_t K = 0; K < FunctionCount; K ++ )
			{
				
				OilFunctionDefinition * FunctionDefinition = Block -> GetFunction ( K );
				
				TypeResolutionResult FunctionResolutionResult = OilTypeResolution_FunctionDefinition ( CurrentNS, * FunctionDefinition, Block -> HasWhereDefinition () ? & TemplateNames : NULL, TypeDefinition );
				
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
					
					DestroyFlatNameList ( TemplateNames );
					
					return FunctionResolutionResult;
					
				}
				
			}
			
			uint32_t MethodCount = Block -> GetMethodCount ();
			
			for ( uint32_t K = 0; K < MethodCount; K ++ )
			{
				
				OilMethodDefinition * MethodDefinition = Block -> GetMethod ( K );
				
				TypeResolutionResult MethodResolutionResult = OilTypeResolution_MethodDefinition ( CurrentNS, * MethodDefinition, TypeDefinition, Block -> HasWhereDefinition () ? & TemplateNames : NULL );
				
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
					
					DestroyFlatNameList ( TemplateNames );
					
					return MethodResolutionResult;
					
				}
				
			}
			
			DestroyFlatNameList ( TemplateNames );
			
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

TypeResolutionResult OilTypeResolution_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t LocalCount = Body.GetLocalBindingCount ();
	
	for ( uint32_t I = 0; I < LocalCount; I ++ )
	{
		
		OilBindingStatement * LocalBinding = Body.GetLocalBinding ( I );
		OilTypeRef * BindingType = LocalBinding -> GetType ();
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * BindingType, TemplateNames, SelfType );
		
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
	
	uint32_t StatementCount = Body.GetStatementCount ();
	
	for ( uint32_t I = 0; I < StatementCount; I ++ )
	{
		
		IOilStatement * Statement = Body.GetStatement ( I );
		
		switch ( Statement -> GetStatementType () )
		{
			
			case IOilStatement :: kStatementType_Expression:
			{
				
				TypeResolutionResult TypeResult = OilTypeResolution_Expression ( CurrentNS, * dynamic_cast <OilExpression *> ( Statement ), TemplateNames, SelfType );
				
				if ( TypeResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( TypeResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( TypeResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return TypeResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Return:
			{
				
				OilReturn * Return = dynamic_cast <OilReturn *> ( Statement );
				
				if ( Return -> HasExpression () )
				{
					
					TypeResolutionResult TypeResult = OilTypeResolution_Expression ( CurrentNS, * Return -> GetReturnedExpression (), TemplateNames, SelfType );
					
					if ( TypeResult == kTypeResolutionResult_Success_Complete )
						Progress = true;
					else if ( TypeResult == kTypeResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
					
					}
					else if ( TypeResult == kTypeResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return TypeResult;
					
				}
				
			}
			break;
			
			case IOilStatement :: kStatementType_ImplicitLocalInitialization:
			{
				
				OilImplicitLocalInitialization * Initialization = dynamic_cast <OilImplicitLocalInitialization *> ( Statement );
				OilBindingStatement * Local = Body.GetLocalBinding ( Initialization -> GetLocalIndex () );
				
				TypeResolutionResult Result = OilTypeResolution_Expression ( CurrentNS, * Local -> GetInitializerValue (), TemplateNames, SelfType );
				
				if ( Result == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_ImplicitBindingInitialization:
			{
				
				OilImplicitBindingInitialization * Initialization = dynamic_cast <OilImplicitBindingInitialization *> ( Statement );
				OilBindingStatement * Binding = CurrentNS.FindBindingStatement ( Initialization -> GetBindingID () );
				
				TypeResolutionResult Result = OilTypeResolution_Expression ( CurrentNS, * Binding -> GetInitializerValue (), TemplateNames, SelfType );
				
				if ( Result == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Binding:
			{
				
				OilBindingStatement * Binding = dynamic_cast <OilBindingStatement *> ( Statement );
				
				TypeResolutionResult TypeResult = OilTypeResolution_TypeRef ( CurrentNS, * Binding -> GetType (), TemplateNames, SelfType );
				
				if ( TypeResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( TypeResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( TypeResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return TypeResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Const:
			{
				
				OilConstStatement * Constant = dynamic_cast <OilConstStatement *> ( Statement );
				
				TypeResolutionResult Result = OilTypeResolution_TypeRef ( CurrentNS, * Constant -> GetType (), TemplateNames, SelfType );
				
				if ( Result == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
				Result = OilTypeResolution_Expression ( CurrentNS, * Constant -> GetInitializerValue (), TemplateNames, SelfType );
				
				if ( Result == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Body:
			{
				
				TypeResolutionResult Result = OilTypeResolution_StatementBody ( CurrentNS, * dynamic_cast <OilStatementBody *> ( Statement ), TemplateNames, SelfType );
				
				if ( Result == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_IfElse:
			{
				
				OilIfElse * IfElse = dynamic_cast <OilIfElse *> ( Statement );
				
				TypeResolutionResult BodyResult = OilTypeResolution_StatementBody ( CurrentNS, * IfElse -> GetIfClauseStatementBody (), TemplateNames, SelfType );
				
				if ( BodyResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( BodyResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BodyResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BodyResult;
				
				TypeResolutionResult ConditionResult = OilTypeResolution_Expression ( CurrentNS, * IfElse -> GetIfClauseConditionExpression (), TemplateNames, SelfType );
				
				if ( ConditionResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( ConditionResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( ConditionResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return ConditionResult;
				
				uint32_t ElseIfCount = IfElse -> HasElseIfClauses () ? IfElse -> GetElseIfClauseCount () : 0;
				
				for ( uint32_t K = 0; K < ElseIfCount; K ++ )
				{
					
					BodyResult = OilTypeResolution_StatementBody ( CurrentNS, * IfElse -> GetElseIfClauseStatementBody ( K ), TemplateNames, SelfType );
					
					if ( BodyResult == kTypeResolutionResult_Success_Complete )
						Progress = true;
					else if ( BodyResult == kTypeResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( BodyResult == kTypeResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return BodyResult;
					
					ConditionResult = OilTypeResolution_Expression ( CurrentNS, * IfElse -> GetElseIfClauseConditionExpression ( K ), TemplateNames, SelfType );
					
					if ( ConditionResult == kTypeResolutionResult_Success_Complete )
						Progress = true;
					else if ( ConditionResult == kTypeResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( ConditionResult == kTypeResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return ConditionResult;
					
				}
				
				if ( IfElse -> HasElseClause () )
				{
					
					BodyResult = OilTypeResolution_StatementBody ( CurrentNS, * IfElse -> GetElseClauseStatementBody (), TemplateNames, SelfType );
					
					if ( BodyResult == kTypeResolutionResult_Success_Complete )
						Progress = true;
					else if ( BodyResult == kTypeResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( BodyResult == kTypeResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return BodyResult;
					
				}
				
			}
			break;
			
			case IOilStatement :: kStatementType_Loop:
			{
				
				OilLoop * Loop = dynamic_cast <OilLoop *> ( Statement );
				
				TypeResolutionResult BodyResult = OilTypeResolution_StatementBody ( CurrentNS, * Loop -> GetStatementBody (), TemplateNames, SelfType );
				
				if ( BodyResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( BodyResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BodyResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BodyResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_WhileLoop:
			{
				
				OilWhileLoop * WhileLoop = dynamic_cast <OilWhileLoop *> ( Statement );
				
				TypeResolutionResult BodyResult = OilTypeResolution_StatementBody ( CurrentNS, * WhileLoop -> GetStatementBody (), TemplateNames, SelfType );
				
				if ( BodyResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( BodyResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BodyResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BodyResult;
				
				TypeResolutionResult ConditionResult = OilTypeResolution_Expression ( CurrentNS, * WhileLoop -> GetConditionExpression (), TemplateNames, SelfType );
				
				if ( ConditionResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( ConditionResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( ConditionResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return ConditionResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_DoWhileLoop:
			{
				
				OilDoWhileLoop * DoWhileLoop = dynamic_cast <OilDoWhileLoop *> ( Statement );
				
				TypeResolutionResult BodyResult = OilTypeResolution_StatementBody ( CurrentNS, * DoWhileLoop -> GetStatementBody (), TemplateNames, SelfType );
				
				if ( BodyResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( BodyResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BodyResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BodyResult;
				
				TypeResolutionResult ConditionResult = OilTypeResolution_Expression ( CurrentNS, * DoWhileLoop -> GetConditionExpression (), TemplateNames, SelfType );
				
				if ( ConditionResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( ConditionResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( ConditionResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return ConditionResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Match:
			{
				
				OilMatch * Match = dynamic_cast <OilMatch *> ( Statement );
				
				TypeResolutionResult MatcheeResult = OilTypeResolution_Expression ( CurrentNS, * Match -> GetMatcheeExpression (), TemplateNames, SelfType );
				
				if ( MatcheeResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( MatcheeResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( MatcheeResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return MatcheeResult;
				
				uint32_t BranchCount = Match -> GetBranchCount ();
				
				for ( uint32_t I = 0; I < BranchCount; I ++ )
				{
					
					OilMatchBranch * Branch = Match -> GetBranch ( I );
					
					TypeResolutionResult BranchResult = OilTypeResolution_MatchBranch ( CurrentNS, * Branch, TemplateNames, SelfType );
					
					if ( BranchResult == kTypeResolutionResult_Success_Complete )
						Progress = true;
					else if ( BranchResult == kTypeResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( BranchResult == kTypeResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return BranchResult;
					
				}
				
			}
			break;
			
			case IOilStatement :: kStatementType_Break:
			break;
			
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

TypeResolutionResult OilTypeResolution_MatchBranch ( OilNamespaceDefinition & CurrentNS, OilMatchBranch & Branch, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	TypeResolutionResult BodyResult = OilTypeResolution_StatementBody ( CurrentNS, * Branch.GetStatementBody (), TemplateNames, SelfType );
	
	if ( BodyResult == kTypeResolutionResult_Success_Complete )
		Progress = true;
	else if ( BodyResult == kTypeResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( BodyResult == kTypeResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
		return BodyResult;
	
	switch ( Branch.GetMatchType () )
	{
		
		case OilMatchBranch :: kMatchType_Constant:
		{
			
			TypeResolutionResult PrimaryResult = OilTypeResolution_Primary ( CurrentNS, Branch.GetConstantPrimary (), TemplateNames, SelfType );
			
			if ( PrimaryResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( PrimaryResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( PrimaryResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return PrimaryResult;
			
		}
		break;
		
		case OilMatchBranch :: kMatchType_Allusion:
		case OilMatchBranch :: kMatchType_AllusionValue:
		{
			
			TypeResolutionResult AllusionResult = OilTypeResolution_Allusion ( CurrentNS, * Branch.GetMatchAllusion (), TemplateNames, SelfType );
			
			if ( AllusionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( AllusionResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( AllusionResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return AllusionResult;
			
		}
		break;
		
		case OilMatchBranch :: kMatchType_Destructure:
		{
			
			// TODO: Implement
			
			OilAllusion * BranchAllusion = Branch.GetMatchAllusion ();
			
			TypeResolutionResult AllusionResult = OilTypeResolution_Allusion ( CurrentNS, * BranchAllusion, TemplateNames, SelfType );
			
			if ( AllusionResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( AllusionResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( AllusionResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return AllusionResult;
			
			if ( ! BranchAllusion -> IsResolved () )
				Unresolved = true;
			else
			{
				
				
				
			}
			
		}
		break;
		
		case OilMatchBranch :: kMatchType_Other:
		break;
		
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

TypeResolutionResult OilTypeResolution_Expression ( OilNamespaceDefinition & CurrentNS, OilExpression & Expression, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	if ( Expression.IsPrimary () )
	{
		
		IOilPrimary * Primary = Expression.GetTermAsPrimary ();
		
		return OilTypeResolution_Primary ( CurrentNS, Primary, TemplateNames, SelfType );
		
	}
	
	IOilOperator * Operator = Expression.GetTermAsOperator ();
	
	switch ( Operator -> GetOperatorType () )
	{
		
		case IOilOperator :: kOperatorType_Unary:
			return OilTypeResolution_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( Operator ), TemplateNames, SelfType );
			
		case IOilOperator :: kOperatorType_Binary:
			return OilTypeResolution_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( Operator ), TemplateNames, SelfType );
		
	}
	
	// Unreachable
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_UnaryOperator ( OilNamespaceDefinition & CurrentNS, OilUnaryOperator & Operator, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	if ( Operator.GetOp () == OilUnaryOperator :: kOperator_FunctionCall )
	{
		
		OilFunctionCallParameterList * ParameterList = Operator.GetFunctionCallParameterList ();
		
		uint32_t ParamCount = ParameterList -> GetParameterCount ();
		
		for ( uint32_t I = 0; I < ParamCount; I ++ )
		{
			
			TypeResolutionResult ParamResult = OilTypeResolution_Expression ( CurrentNS, * ParameterList -> GetParameter ( I ), TemplateNames, SelfType );
			
			if ( ParamResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ParamResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
					
			}
			else if ( ParamResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ParamResult;
			
		}
		
	}
	else if ( Operator.GetOp () == OilUnaryOperator :: kOperator_MemberAccess )
	{
		
		if ( Operator.IsMemberAccessTempalted () )
		{
			
			TypeResolutionResult ParamResult = OilTypeResolution_TemplateSpecification ( CurrentNS, * Operator.GetTemplateSpecificationForMemberAccess (), TemplateNames, SelfType );
			
			if ( ParamResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ParamResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
					
			}
			else if ( ParamResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ParamResult;
			
		}
		
	}
	else if ( Operator.GetOp () == OilUnaryOperator :: kOperator_TraitCast )
	{
		
		OilTypeRef * CastTraitRef = Operator.GetCastTraitRef ();
		
		if ( ! CastTraitRef -> IsResolved () )
		{
			
			TypeResolutionResult TraitResult = OilTypeResolution_TypeRef ( CurrentNS, * CastTraitRef, TemplateNames, SelfType );
			
			if ( TraitResult == kTypeResolutionResult_Success_Complete )
			{
				
				if ( ! CastTraitRef -> IsResolvedAsTrait () )
				{
					
					LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( CastTraitRef -> GetSourceRef () ) + "trait cast operator refers to non-trait type" );
					
					return kTypeResolutionResult_Failure_NonTrait;
					
				}
				
				Progress = true;
				
			}
			else if ( TraitResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
					
			}
			else if ( TraitResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return TraitResult;
			
		}
		
	}
	
	if ( Operator.IsTermPrimary () )
	{
		
		TypeResolutionResult PrimaryResult = OilTypeResolution_Primary ( CurrentNS, Operator.GetTermAsPrimary (), TemplateNames, SelfType );
		
		if ( PrimaryResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( PrimaryResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
				
		}
		else if ( PrimaryResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return PrimaryResult;
		
	}
	else
	{
		
		IOilOperator * TermOperator = Operator.GetTermAsOperator ();
		
		switch ( TermOperator -> GetOperatorType () )
		{
			
			case IOilOperator :: kOperatorType_Unary:
			{
				
				TypeResolutionResult UnaryResult = OilTypeResolution_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( TermOperator ), TemplateNames, SelfType );
				
				if ( UnaryResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( UnaryResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
						
				}
				else if ( UnaryResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return UnaryResult;
				
			}
			break;
			
			case IOilOperator :: kOperatorType_Binary:
			{
				
				TypeResolutionResult BinaryResult = OilTypeResolution_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( TermOperator ), TemplateNames, SelfType );
				
				if ( BinaryResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( BinaryResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
						
				}
				else if ( BinaryResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BinaryResult;
				
			}
			break;
			
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

TypeResolutionResult OilTypeResolution_BinaryOperator ( OilNamespaceDefinition & CurrentNS, OilBinaryOperator & Operator, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	if ( Operator.IsLeftPrimary () )
	{
		
		TypeResolutionResult PrimaryResult = OilTypeResolution_Primary ( CurrentNS, Operator.GetLeftTermAsPrimary (), TemplateNames, SelfType );
		
		if ( PrimaryResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( PrimaryResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
				
		}
		else if ( PrimaryResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return PrimaryResult;
		
	}
	else
	{
		
		IOilOperator * TermOperator = Operator.GetLeftTermAsOperator ();
		
		switch ( TermOperator -> GetOperatorType () )
		{
			
			case IOilOperator :: kOperatorType_Unary:
			{
				
				TypeResolutionResult UnaryResult = OilTypeResolution_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( TermOperator ), TemplateNames, SelfType );
				
				if ( UnaryResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( UnaryResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
						
				}
				else if ( UnaryResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return UnaryResult;
				
			}
			break;
			
			case IOilOperator :: kOperatorType_Binary:
			{
				
				TypeResolutionResult BinaryResult = OilTypeResolution_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( TermOperator ), TemplateNames, SelfType );
				
				if ( BinaryResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( BinaryResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
						
				}
				else if ( BinaryResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BinaryResult;
				
			}
			break;
			
		}
		
	}
	
	if ( Operator.IsRightPrimary () )
	{
		
		TypeResolutionResult PrimaryResult = OilTypeResolution_Primary ( CurrentNS, Operator.GetRightTermAsPrimary (), TemplateNames, SelfType );
		
		if ( PrimaryResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( PrimaryResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
				
		}
		else if ( PrimaryResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return PrimaryResult;
		
	}
	else
	{
		
		IOilOperator * TermOperator = Operator.GetRightTermAsOperator ();
		
		switch ( TermOperator -> GetOperatorType () )
		{
			
			case IOilOperator :: kOperatorType_Unary:
			{
				
				TypeResolutionResult UnaryResult = OilTypeResolution_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( TermOperator ), TemplateNames, SelfType );
				
				if ( UnaryResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( UnaryResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
						
				}
				else if ( UnaryResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return UnaryResult;
				
			}
			break;
			
			case IOilOperator :: kOperatorType_Binary:
			{
				
				TypeResolutionResult BinaryResult = OilTypeResolution_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( TermOperator ), TemplateNames, SelfType );
				
				if ( BinaryResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( BinaryResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
						
				}
				else if ( BinaryResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BinaryResult;
				
			}
			break;
			
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

TypeResolutionResult OilTypeResolution_Primary ( OilNamespaceDefinition & CurrentNS, IOilPrimary * Primary, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	switch ( Primary -> GetPrimaryType () )
	{
		
		case IOilPrimary :: kPrimaryType_Expression:
			return OilTypeResolution_Expression ( CurrentNS, * dynamic_cast <OilExpression *> ( Primary ), TemplateNames, SelfType );
			
		case IOilPrimary :: kPrimaryType_ArrayLiteral:
		{
			
			OilArrayLiteral * Array = dynamic_cast <OilArrayLiteral *> ( Primary );
			
			if ( Array -> HasTypeSpecifier () )
			{
				
				TypeResolutionResult TypeSpecifierResult = OilTypeResolution_TypeRef ( CurrentNS, * Array -> GetTypeSpecifier (), TemplateNames, SelfType );
				
				if ( TypeSpecifierResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( TypeSpecifierResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( TypeSpecifierResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return TypeSpecifierResult;
				
			}
			
			if ( Array -> HasSpecificCount () )
			{
				
				TypeResolutionResult CountResult = OilTypeResolution_Primary ( CurrentNS, Array -> GetCountExpression (), TemplateNames, SelfType );
				
				if ( CountResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( CountResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( CountResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return CountResult;
				
			}
			
			if ( Array -> HasMemberInitiailizers () )
			{
				
				uint32_t InitializerCount = Array -> GetMemberInitializerCount ();
				
				for ( uint32_t I = 0; I < InitializerCount; I ++ )
				{
					
					TypeResolutionResult InitializerResult = OilTypeResolution_Primary ( CurrentNS, Array -> GetMemberInitializer ( I ), TemplateNames, SelfType );
					
					if ( InitializerResult == kTypeResolutionResult_Success_Complete )
						Progress = true;
					else if ( InitializerResult == kTypeResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( InitializerResult == kTypeResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return InitializerResult;
					
				}
				
			}
			
		}
		break;
		
		case IOilPrimary :: kPrimaryType_StructLiteral:
		{
			
			OilStructLiteral * StructLiteral = dynamic_cast <OilStructLiteral *> ( Primary );
			
			TypeResolutionResult StructTypeResult = OilTypeResolution_TypeRef ( CurrentNS, * StructLiteral -> GetLiteralType (), TemplateNames, SelfType );
			
			if ( StructTypeResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( StructTypeResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( StructTypeResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return StructTypeResult;
			
			uint32_t MemberValueCount = StructLiteral -> GetMemberValueCount ();
			
			for ( uint32_t I = 0; I < MemberValueCount; I ++ )
			{
				
				OilStructInitializerValue * MemberValue = StructLiteral -> GetInitializerValue ( I );
				
				TypeResolutionResult MemberValueResult = OilTypeResolution_Expression ( CurrentNS, * MemberValue -> GetValueExpression (), TemplateNames, SelfType );
				
				if ( MemberValueResult == kTypeResolutionResult_Success_Complete )
					Progress = true;
				else if ( MemberValueResult == kTypeResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( MemberValueResult == kTypeResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return MemberValueResult;
				
			}
			
		}
		break;
		
		case IOilPrimary :: kPrimaryType_Allusion:
			return OilTypeResolution_Allusion ( CurrentNS, * dynamic_cast <OilAllusion *> ( Primary ), TemplateNames, SelfType );
		
		default:
		break;
		
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

TypeResolutionResult OilTypeResolution_Allusion ( OilNamespaceDefinition & CurrentNS, OilAllusion & Allusion, FlatNameList * TemplateNames, OilTypeDefinition * SelfType )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	if ( Allusion.IsDirectlyTemplated () )
	{
		
		TypeResolutionResult Result = OilTypeResolution_TemplateSpecification ( CurrentNS, * Allusion.GetDirectTemplateSpecification (), TemplateNames, SelfType );
		
		if ( Result == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( Result == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( Result == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
		else
			return Result;
		
	}
	
	if ( Allusion.IsIndirectlyTemplated () )
	{
		
		TypeResolutionResult Result = OilTypeResolution_TemplateSpecification ( CurrentNS, * Allusion.GetIndirectTemplateSpecification (), TemplateNames, SelfType );
		
		if ( Result == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( Result == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( Result == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
		else
			return Result;
		
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

TypeResolutionResult OilTypeResolution_Traits ( OilNamespaceDefinition & CurrentNS )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t TraitCount = CurrentNS.GetTraitDefinitionCount ();
	
	for ( uint32_t I = 0; I < TraitCount; I ++ )
	{
		
		TypeResolutionResult TraitResult = OilTypeResolution_Trait ( CurrentNS, * CurrentNS.GetTraitDefinition ( I ) );
		
		if ( TraitResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( TraitResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( TraitResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return TraitResult;
		
	}
	
	uint32_t SubNSCount = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		TypeResolutionResult SubNSResult = OilTypeResolution_Traits ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
		if ( SubNSResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( SubNSResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( SubNSResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return SubNSResult;
		
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

TypeResolutionResult OilTypeResolution_Trait ( OilNamespaceDefinition & CurrentNS, OilTraitDefinition & TraitDef )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	OilTemplateDefinition * TemplateDef = NULL;
	
	if ( TraitDef.IsTemplated () )
		TemplateDef = TraitDef.GetTemplateDefinition ();
	
	FlatNameList TemplateNames;
	
	if ( TemplateDef != NULL )
	{
		
		TypeResolutionResult ResolutionResult = OilTypeResolution_TemplateDefinition ( CurrentNS, * TemplateDef );
		
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
		
		MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
		
	}
	
	uint32_t RequiredTraitCount = TraitDef.GetRequiredTraitCount ();
	
	for ( uint32_t I = 0; I < RequiredTraitCount; I ++ )
	{
		
		TypeResolutionResult RequirementResult = OilTypeResolution_TypeRef ( CurrentNS, * TraitDef.GetRequiredTrait ( I ), TraitDef.IsTemplated () ? & TemplateNames : NULL );
		
		if ( RequirementResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( RequirementResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( RequirementResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
		{
			
			DestroyFlatNameList ( TemplateNames );
			
			return RequirementResult;
			
		}
		
	}
	
	uint32_t FunctionCount = TraitDef.GetFunctionCount ();
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
	{
		
		TypeResolutionResult FunctionResult = OilTypeResolution_TraitFunction ( CurrentNS, * TraitDef.GetTraitFunction ( I ), & TraitDef, TraitDef.IsTemplated () ? & TemplateNames : NULL );
		
		if ( FunctionResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( FunctionResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( FunctionResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
		{
			
			DestroyFlatNameList ( TemplateNames );
			
			return FunctionResult;
			
		}
		
	}
	
	uint32_t MethodCount = TraitDef.GetMethodCount ();
	
	for ( uint32_t I = 0; I < MethodCount; I ++ )
	{
		
		TypeResolutionResult MethodResult = OilTypeResolution_TraitMethod ( CurrentNS, * TraitDef.GetTraitMethod ( I ), & TraitDef, TraitDef.IsTemplated () ? & TemplateNames : NULL );
		
		if ( MethodResult == kTypeResolutionResult_Success_Complete )
			Progress = true;
		else if ( MethodResult == kTypeResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( MethodResult == kTypeResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
		{
			
			DestroyFlatNameList ( TemplateNames );
			
			return MethodResult;
			
		}
		
	}
	
	DestroyFlatNameList ( TemplateNames );
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_TraitFunction ( OilNamespaceDefinition & CurrentNS, OilTraitFunction & Function, OilTraitDefinition * SelfTrait, FlatNameList * TemplateNames )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	OilTemplateDefinition * TemplateDef = Function.IsTemplated () ? Function.GetTemplateDefinition () : NULL;
	
	FlatNameList AllTemplateNames;
	
	if ( TemplateDef != NULL )
		MakeNameList_TemplateDefinition ( * TemplateDef, AllTemplateNames, TemplateNames );
	
	if ( ! Function.GetReturnType () -> IsResolved () )
	{
		
		TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * Function.GetReturnType (), TemplateNames, NULL, SelfTrait );
		
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
	
	OilFunctionParameterList * ParameterList = Function.GetParameterList ();
	
	uint32_t ParamCount = ParameterList -> GetParameterCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OilFunctionParameter * Parameter = ParameterList -> GetFunctionParameter ( I );
		OilTypeRef * ParamType = Parameter -> GetType ();
		
		if ( ! ParamType -> IsResolved () )
		{
			
			TypeResolutionResult ParameterTypeResult = OilTypeResolution_TypeRef ( CurrentNS, * ParamType, TemplateNames, NULL, SelfTrait );
			
			if ( ParameterTypeResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ParameterTypeResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( ParameterTypeResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ParameterTypeResult;
			
		}
		
	}
	
	DestroyFlatNameList ( AllTemplateNames );
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_TraitMethod ( OilNamespaceDefinition & CurrentNS, OilTraitMethod & Method, OilTraitDefinition * SelfTrait, FlatNameList * TemplateNames )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	OilTemplateDefinition * TemplateDef = Method.IsTemplated () ? Method.GetTemplateDefinition () : NULL;
	
	FlatNameList AllTemplateNames;
	
	if ( TemplateDef != NULL )
		MakeNameList_TemplateDefinition ( * TemplateDef, AllTemplateNames, TemplateNames );
	
	if ( ! Method.GetReturnType () -> IsResolved () )
	{
		
		TypeResolutionResult ReturnTypeResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * Method.GetReturnType (), TemplateNames, NULL, SelfTrait );
		
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
	
	OilMethodParameterList * ParameterList = Method.GetParameterList ();
	
	uint32_t ParamCount = ParameterList -> GetParameterCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OilFunctionParameter * Parameter = ParameterList -> GetFunctionParameter ( I );
		OilTypeRef * ParamType = Parameter -> GetType ();
		
		if ( ! ParamType -> IsResolved () )
		{
			
			TypeResolutionResult ParameterTypeResult = OilTypeResolution_TypeRef ( CurrentNS, * ParamType, TemplateNames, NULL, SelfTrait );
			
			if ( ParameterTypeResult == kTypeResolutionResult_Success_Complete )
				Progress = true;
			else if ( ParameterTypeResult == kTypeResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( ParameterTypeResult == kTypeResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ParameterTypeResult;
			
		}
		
	}
	
	DestroyFlatNameList ( AllTemplateNames );
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}

TypeResolutionResult OilTypeResolution_Enum ( OilNamespaceDefinition & CurrentNS, OilEnum & Enum )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	OilTemplateDefinition * TemplateDef = Enum.IsTemplated () ? Enum.GetTemplateDefinition () : NULL;
	
	FlatNameList TemplateNames;
	
	if ( TemplateDef != NULL )
		MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
	
	uint32_t BranchCount = Enum.GetBranchCount ();
	
	for ( uint32_t I = 0; I < BranchCount; I ++ )
	{
		
		OilTypeRef * BranchType = Enum.BranchHasData ( I ) ? Enum.GetBranchDataType ( I ) : NULL;
		
		if ( BranchType )
		{
			
			TypeResolutionResult ResolutionResult = OilTypeResolution_TypeRef ( CurrentNS, * BranchType, ( TemplateDef != NULL ) ? & TemplateNames : NULL );
			
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
		
	}
	
	DestroyFlatNameList ( TemplateNames );
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kTypeResolutionResult_Success_Progress;
		else
			return kTypeResolutionResult_Success_NoProgress;
		
	}
	
	return kTypeResolutionResult_Success_Complete;
	
}
