#include <EarlyAnalysis/OilAllusionResolution.h>
#include <EarlyAnalysis/OilTypeResolution.h>

#include <Logging/Logging.h>
#include <Logging/ErrorUtils.h>

#include <Encoding/CodeConversion.h>

#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilExpression.h>
#include <OIL/IOilPrimary.h>
#include <OIL/IOilStatement.h>
#include <OIL/IOilOperator.h>
#include <OIL/OilStatementBody.h>
#include <OIL/OilBinaryOperator.h>
#include <OIL/OilUnaryOperator.h>
#include <OIL/OilAllusion.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilMethodDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateSpecification.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilReturn.h>
#include <OIL/OilIfElse.h>
#include <OIL/OilWhileLoop.h>
#include <OIL/OilDoWhileLoop.h>
#include <OIL/OilLoop.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilMethodDefinition.h>
#include <OIL/OilMethodParameterList.h>
#include <OIL/OilImplicitLocalInitialization.h>
#include <OIL/OilImplicitBindingInitialization.h>

AllusionResolutionResult OilResolveAllusions_Allusion ( OilNamespaceDefinition & CurrentNS, OilAllusion & Allusion, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion )
{
	
	(void) TemplateNameList;
	(void) FirstUnresolvedAllusion;
	(void) SelfType;
	
	if ( Allusion.IsResolved () )
		return kAllusionResolutionResult_Success_Complete;
	
	//TODO: Write
	
	switch ( Allusion.GetTarget () )
	{
		
		case OilAllusion :: kAllusionTarget_Parameter:
		case OilAllusion :: kAllusionTarget_Function:
		case OilAllusion :: kAllusionTarget_LocalBinding:
		case OilAllusion :: kAllusionTarget_Binding:
		case OilAllusion :: kAllusionTarget_Constant:
		return kAllusionResolutionResult_Success_Complete;
		
		case OilAllusion :: kAllusionTarget_Self_Unchecked:
		{
			
			if ( ! MethodContext )
			{
				
				LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"self\" cannot be used outside of methods." );
				
				return kAllusionResolutionResult_Failure_NonMethodAllusionToSelf;
				
			}
			
			Allusion.SetTargetAsSelf ();
			
			return kAllusionResolutionResult_Success_Complete;
			
		}
		break;
		
		case OilAllusion :: kAllusionTarget_Indeterminate:
		{
			
			const std :: u32string & Name = Allusion.GetName ();
			
			if ( Name == U"Self" )
			{
				
				LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "type Self " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
				
				FirstUnresolvedAllusion = & Allusion;
				return kAllusionResolutionResult_Failure_AllusionToType;
				
			}
			
			OilStatementBody * LocalBody = & ContainerBody;
			uint64_t ThisStatementIndex = StatementRootIndex;
			
			while ( LocalBody != NULL )
			{
				
				uint64_t I = 0;
				
				IOilStatement * PotentialBinding = LocalBody -> GetStatement ( I );
				OilBindingStatement * LatestScopedBinding = NULL;
				
				uint64_t StatementCount = LocalBody -> GetStatementCount ();
				
				while ( I < ThisStatementIndex )
				{
					
					if ( PotentialBinding -> GetStatementType () == IOilStatement :: kStatementType_ImplicitLocalInitialization )
					{
						
						OilBindingStatement * Binding = LocalBody -> GetLocalBinding ( dynamic_cast <OilImplicitLocalInitialization *> ( PotentialBinding ) -> GetLocalIndex () );
						
						if ( Binding -> GetName () == Name )
							LatestScopedBinding = Binding;
						
					}
					
					I ++;
					
					if ( I > StatementCount )
						break;
					
					PotentialBinding = LocalBody -> GetStatement ( I );
					
				}
				
				if ( LatestScopedBinding != NULL )
				{
					
					Allusion.SetTargetAsLocalBinding ( LatestScopedBinding );
					
					return kAllusionResolutionResult_Success_Complete;
					
				}
				
				ThisStatementIndex = LocalBody -> GetParentBodySelfIndex ();
				LocalBody = LocalBody -> GetParentBody ();
				
			}
			
			if ( ParameterList != NULL )
			{
				
				for ( uint32_t I = 0; I < ParameterList -> Count; I ++ )
				{
					
					if ( Name == ParameterList -> Params [ I ] -> GetName () )
					{
						
						Allusion.SetTargetAsParameter ( ParameterList -> Params [ I ] );
						
						return kAllusionResolutionResult_Success_Complete;
						
					}
					
				}
				
			}
			
			// Search namespaces upward for name...
			OilNamespaceDefinition * LocalNS = & CurrentNS;
			
			OilNamespaceDefinition :: NameSearchResult SearchResult;
			
			while ( LocalNS != NULL )
			{
				
				LocalNS -> SearchName ( Name, SearchResult );
				
				switch ( SearchResult.Type )
				{
					
					case OilNamespaceDefinition :: kNameSearchResultType_SubNamespace:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "namespace " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToNamespace;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_TypeDefinition:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "type " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToType;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_FunctionDefinition:
					{
						
						OilFunctionDefinition * Function = SearchResult.FunctionDefinition;
						
						if ( Function -> IsTemplated () )
						{
							
							LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "function " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " requires template, but none was specified." );
							
							return kAllusionResolutionResult_Failure_TemplateMismatch;
							
						}
						
						Allusion.SetTargetAsFunction ( SearchResult.FunctionDefinition );
						
						return kAllusionResolutionResult_Success_Complete;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_BindingStatement:
					{
						
						Allusion.SetTargetAsBinding ( SearchResult.BindingStatement );
						
						return kAllusionResolutionResult_Success_Complete;
						
					}
					
					case OilNamespaceDefinition :: kNameSearchResultType_ConstStatement:
					{
						
						Allusion.SetTargetAsConstant ( SearchResult.ConstStatement );
						
						return kAllusionResolutionResult_Success_Complete;
						
					}
					
					case OilNamespaceDefinition :: kNameSearchResultType_TraitDefinition:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "trait " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToType;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_TypeAlias:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "type " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToType;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_None:
					break;
					
				}
				
				LocalNS = LocalNS -> GetParent ();
				
			}
			
			LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "cannot find " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + "." );
			
			FirstUnresolvedAllusion = & Allusion;
			return kAllusionResolutionResult_Failure_AllusionNotFound;
			
		}
		break;
		
		case OilAllusion :: kAllusionTarget_Indeterminate_Templated:
		{
			
			const std :: u32string Name = Allusion.GetName ();
			OilTemplateSpecification * AllusionTemplate = Allusion.GetDirectTemplateSpecification ();
			
			while ( true )
			{
				
				TypeResolutionResult TemplateResult = OilTypeResolution_TemplateSpecification ( CurrentNS, * AllusionTemplate, TemplateNameList );
				
				if ( TemplateResult == kTypeResolutionResult_Success_Complete )
					break;
				
				if ( TemplateResult != kTypeResolutionResult_Success_Progress )
					return kAllusionResolutionResult_Failure_TemplateTypeResolution;
				
			}
			
			OilNamespaceDefinition * LocalNS = & CurrentNS;
			
			OilNamespaceDefinition :: NameSearchResult SearchResult;
			
			while ( LocalNS != NULL )
			{
				
				LocalNS -> SearchName ( Name, SearchResult );
				
				switch ( SearchResult.Type )
				{
					
					case OilNamespaceDefinition :: kNameSearchResultType_SubNamespace:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "namespace " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToNamespace;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_TypeDefinition:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "type " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToType;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_FunctionDefinition:
					{
						
						OilFunctionDefinition * Function = SearchResult.FunctionDefinition;
						
						if ( ! Function -> IsTemplated () )
						{
							
							LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "function " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " does not have a template, one was specified." );
							
							return kAllusionResolutionResult_Failure_TemplateMismatch;
							
						}
						
						OilTemplateDefinition * FunctionTemplate = Function -> GetTemplateDefinition ();
						
						if ( FunctionTemplate -> GetTemplateParameterCount () != AllusionTemplate -> GetTypeRefCount () )
						{
							
							LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "function " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " has template requiring " + std :: to_string ( FunctionTemplate -> GetTemplateParameterCount () ) + " parameters, but " + std :: to_string ( AllusionTemplate -> GetTypeRefCount () ) + " were specified." );
							
							return kAllusionResolutionResult_Failure_TemplateMismatch;
							
						}
						
						Allusion.SetTargetAsTemplatedFunction ( SearchResult.FunctionDefinition );
						
						return kAllusionResolutionResult_Success_Complete;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_BindingStatement:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "binding " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot have a template, one was specified." );
						
						return kAllusionResolutionResult_Failure_TemplateMismatch;
						
					}
					
					case OilNamespaceDefinition :: kNameSearchResultType_ConstStatement:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "constant " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot have a template, one was specified." );
						
						return kAllusionResolutionResult_Failure_TemplateMismatch;
						
					}
					
					case OilNamespaceDefinition :: kNameSearchResultType_TraitDefinition:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "trait " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToType;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_TypeAlias:
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "type " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + " cannot be used as object or function." );
						
						FirstUnresolvedAllusion = & Allusion;
						return kAllusionResolutionResult_Failure_AllusionToType;
						
					}
					break;
					
					case OilNamespaceDefinition :: kNameSearchResultType_None:
					break;
					
				}
				
				LocalNS = LocalNS -> GetParent ();
				
			}
			
			LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "cannot find " + CodeConversion :: ConvertUTF32ToUTF8 ( Name ) + "." );
			
			FirstUnresolvedAllusion = & Allusion;
			return kAllusionResolutionResult_Failure_AllusionNotFound;
			
		}
		
		// TODO: Implement all cases and get rid of this!
		default:
		break;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilResolveAllusions_BinaryOperator ( OilNamespaceDefinition & CurrentNS, OilBinaryOperator & BinaryOperator, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	if ( BinaryOperator.IsLeftPrimary () )
	{
		
		IOilPrimary * Primary = BinaryOperator.GetLeftTermAsPrimary ();
		
		switch ( Primary -> GetPrimaryType () )
		{
			
			case IOilPrimary :: kPrimaryType_Expression:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * dynamic_cast <OilExpression *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilPrimary :: kPrimaryType_Allusion:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_Allusion ( CurrentNS, * dynamic_cast <OilAllusion *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			
			default:
			break;
			
		}
		
	}
	else
	{
		
		IOilOperator * Operator = BinaryOperator.GetLeftTermAsOperator ();
		
		switch ( Operator -> GetOperatorType () )
		{
			
			case IOilOperator :: kOperatorType_Unary:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			
			case IOilOperator :: kOperatorType_Binary:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			
		}
		
	}
	
	if ( BinaryOperator.IsRightPrimary () )
	{
		
		IOilPrimary * Primary = BinaryOperator.GetRightTermAsPrimary ();
		
		switch ( Primary -> GetPrimaryType () )
		{
			
			case IOilPrimary :: kPrimaryType_Expression:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * dynamic_cast <OilExpression *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilPrimary :: kPrimaryType_Allusion:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_Allusion ( CurrentNS, * dynamic_cast <OilAllusion *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			
			default:
			break;
			
		}
		
	}
	else
	{
		
		IOilOperator * Operator = BinaryOperator.GetRightTermAsOperator ();
		
		switch ( Operator -> GetOperatorType () )
		{
			
			case IOilOperator :: kOperatorType_Unary:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			
			case IOilOperator :: kOperatorType_Binary:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			
		}
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		else
			return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilResolveAllusions_UnaryOperator ( OilNamespaceDefinition & CurrentNS, OilUnaryOperator & UnaryOperator, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion )
{
	
	if ( UnaryOperator.IsTermPrimary () )
	{
		
		IOilPrimary * Primary = UnaryOperator.GetTermAsPrimary ();
		
		switch ( Primary -> GetPrimaryType () )
		{
			
			case IOilPrimary :: kPrimaryType_Expression:
				return OilResolveAllusions_Expression ( CurrentNS, * dynamic_cast <OilExpression *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
			case IOilPrimary :: kPrimaryType_Allusion:
				return OilResolveAllusions_Allusion ( CurrentNS, * dynamic_cast <OilAllusion *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
			default:
			break;
			
		}
		
	}
	else
	{
		
		IOilOperator * Operator = UnaryOperator.GetTermAsOperator ();
		
		switch ( Operator -> GetOperatorType () )
		{
			
			case IOilOperator :: kOperatorType_Unary:
				return OilResolveAllusions_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
			case IOilOperator :: kOperatorType_Binary:
				return OilResolveAllusions_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
		}
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}


AllusionResolutionResult OilResolveAllusions_Expression ( OilNamespaceDefinition & CurrentNS, OilExpression & Expression, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion )
{
	
	if ( Expression.IsPrimary () )
	{
		
		IOilPrimary * Primary = Expression.GetTermAsPrimary ();
		
		switch ( Primary -> GetPrimaryType () )
		{
			
			case IOilPrimary :: kPrimaryType_Expression:
				return OilResolveAllusions_Expression ( CurrentNS, * dynamic_cast <OilExpression *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
			case IOilPrimary :: kPrimaryType_Allusion:
				return OilResolveAllusions_Allusion ( CurrentNS, * dynamic_cast <OilAllusion *> ( Primary ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
			default:
			break;
			
		}
		
	}
	else
	{
		
		IOilOperator * Operator = Expression.GetTermAsOperator ();
		
		switch ( Operator -> GetOperatorType () )
		{
			
			case IOilOperator :: kOperatorType_Unary:
				return OilResolveAllusions_UnaryOperator ( CurrentNS, * dynamic_cast <OilUnaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
			case IOilOperator :: kOperatorType_Binary:
				return OilResolveAllusions_BinaryOperator ( CurrentNS, * dynamic_cast <OilBinaryOperator *> ( Operator ), StatementRootIndex, ContainerBody, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
			
		}
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilResolveAllusions_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	(void) CurrentNS;
	(void) MethodContext;
	(void) ParameterNameList;
	(void) TemplateNameList;
	(void) FirstUnresolvedAllusion;
	
	uint32_t StatementCount = Body.GetStatementCount ();
	
	for ( uint32_t I = 0; I < StatementCount; I ++ )
	{
		
		IOilStatement * Statement = Body.GetStatement ( I );
		
		switch ( Statement -> GetStatementType () )
		{
			
			case IOilStatement :: kStatementType_Body:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_StatementBody ( CurrentNS, * dynamic_cast <OilStatementBody *> ( Statement ), MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Const:
			case IOilStatement :: kStatementType_Binding:
			// This shouldn't ever occur, since local bindings and constants are added to a seperate list from the statement list
			break;
			
			case IOilStatement :: kStatementType_Expression:
			{
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * dynamic_cast <OilExpression *> ( Statement ), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Return:
			{
				
				OilReturn * Return = dynamic_cast <OilReturn *> ( Statement );
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * Return -> GetReturnedExpression (), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_IfElse:
			{
				
				OilIfElse * IfElse = dynamic_cast <OilIfElse *> ( Statement );
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * IfElse -> GetIfClauseConditionExpression (), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
				Result = OilResolveAllusions_StatementBody ( CurrentNS, * IfElse -> GetIfClauseStatementBody (), MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
				uint32_t ElseIfCount = IfElse -> GetElseIfClauseCount ();
				
				for ( uint32_t I = 0; I < ElseIfCount; I ++ )
				{
					
					Result = OilResolveAllusions_Expression ( CurrentNS, * IfElse -> GetElseIfClauseConditionExpression ( I ), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
					
					if ( Result == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( Result == kAllusionResolutionResult_Success_Progress )
					{
				
						Progress = true;
						Unresolved = true;
						
					}
					else if ( Result == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return Result;
					
					Result = OilResolveAllusions_StatementBody ( CurrentNS, * IfElse -> GetElseIfClauseStatementBody ( I ), MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
					
					if ( Result == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( Result == kAllusionResolutionResult_Success_Progress )
					{
				
						Progress = true;
						Unresolved = true;
						
					}
					else if ( Result == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return Result;
					
				}
				
				if ( IfElse -> HasElseClause () )
				{
					
					Result = OilResolveAllusions_StatementBody ( CurrentNS, * IfElse -> GetElseClauseStatementBody (), MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
					
					if ( Result == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( Result == kAllusionResolutionResult_Success_Progress )
					{
				
						Progress = true;
						Unresolved = true;
						
					}
					else if ( Result == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return Result;
					
				}
				
			}
			break;
			
			case IOilStatement :: kStatementType_WhileLoop:
			{
				
				OilWhileLoop * WhileLoop = dynamic_cast <OilWhileLoop *> ( Statement );
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * WhileLoop -> GetConditionExpression (), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
				Result = OilResolveAllusions_StatementBody ( CurrentNS, * WhileLoop -> GetStatementBody (), MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_DoWhileLoop:
			{
				
				OilDoWhileLoop * DoWhileLoop = dynamic_cast <OilDoWhileLoop *> ( Statement );
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * DoWhileLoop -> GetConditionExpression (), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
				Result = OilResolveAllusions_StatementBody ( CurrentNS, * DoWhileLoop -> GetStatementBody (), MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Loop:
			{
				
				OilLoop * Loop = dynamic_cast <OilLoop *> ( Statement );
				
				AllusionResolutionResult Result = OilResolveAllusions_StatementBody ( CurrentNS, * Loop -> GetStatementBody (), MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Break:
			break;
			
			case IOilStatement :: kStatementType_ImplicitLocalInitialization:
			{
				
				OilImplicitLocalInitialization * Initialization = dynamic_cast <OilImplicitLocalInitialization *> ( Statement );
				OilBindingStatement * Binding = Body.GetLocalBinding ( Initialization -> GetLocalIndex () );
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * Binding -> GetInitializerValue (), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
			case IOilStatement :: kStatementType_ImplicitBindingInitialization:
			{
				
				OilImplicitBindingInitialization * Initialization = dynamic_cast <OilImplicitBindingInitialization *> ( Statement );
				OilBindingStatement * Binding = CurrentNS.FindBindingStatement ( Initialization -> GetBindingID () );
				
				AllusionResolutionResult Result = OilResolveAllusions_Expression ( CurrentNS, * Binding -> GetInitializerValue (), I, Body, MethodContext, ParameterNameList, TemplateNameList, SelfType, FirstUnresolvedAllusion );
				
				if ( Result == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( Result == kAllusionResolutionResult_Success_Progress )
				{
			
					Progress = true;
					Unresolved = true;
					
				}
				else if ( Result == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return Result;
				
			}
			break;
			
		}
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		else
			return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilResolveAllusions_Function ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function, OilAllusion *& FirstUnresolvedAllusion, OilTypeRef * SelfType )
{
	
	if ( Function.IsNative () )
		return kAllusionResolutionResult_Success_Complete;
	
	OilStatementBody * Body = Function.GetStatementBody ();
	OilFunctionParameterList * Parameters = Function.GetParameterList ();
	
	FunctionParamList ParameterList;
	bool UseParamNames = false;
	
	MakeNameList_FunctionParameters ( * Parameters, ParameterList, UseParamNames );
	
	OilTemplateDefinition * TemplateDef = Function.IsTemplated () ? Function.GetTemplateDefinition () : NULL;
	
	FlatNameList TemplateNames;
	
	if ( TemplateDef != NULL )
		MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
	
	AllusionResolutionResult Result = OilResolveAllusions_StatementBody ( CurrentNS, * Body, false, UseParamNames ? & ParameterList : NULL, ( TemplateDef != NULL ) ? & TemplateNames : NULL, SelfType, FirstUnresolvedAllusion );
	
	DestroyFunctionParamList ( ParameterList );
	DestroyFlatNameList ( TemplateNames );
	
	return Result;
	
}

AllusionResolutionResult OilResolveAllusions_Method ( OilNamespaceDefinition & CurrentNS, OilMethodDefinition & Method, OilAllusion *& FirstUnresolvedAllusion, OilTypeRef * SelfType )
{
	
	// TODO: Uncomment when native methods are supported
	
	/*if ( Method.IsNative () )
		return kAllusionResolutionResult_Success_Complete;*/
	
	OilStatementBody * Body = Method.GetStatementBody ();
	OilMethodParameterList * Parameters = Method.GetParameterList ();
	
	FunctionParamList ParameterList;
	bool UseParamNames = false;
	
	MakeNameList_MethodParameters ( * Parameters, ParameterList, UseParamNames );
	
	OilTemplateDefinition * TemplateDef = Method.IsTemplated () ? Method.GetTemplateDefinition () : NULL;
	
	FlatNameList TemplateNames;
	
	if ( TemplateDef != NULL )
		MakeNameList_TemplateDefinition ( * TemplateDef, TemplateNames );
	
	AllusionResolutionResult Result = OilResolveAllusions_StatementBody ( CurrentNS, * Body, true, UseParamNames ? & ParameterList : NULL, ( TemplateDef != NULL ) ? & TemplateNames : NULL, SelfType, FirstUnresolvedAllusion );
	
	DestroyFunctionParamList ( ParameterList );
	DestroyFlatNameList ( TemplateNames );
	
	return Result;
	
}


AllusionResolutionResult OilResolveAllusions_Type ( OilNamespaceDefinition & CurrentNS, OilTypeDefinition & Type, OilAllusion *& FirstUnresolvedAllusion )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	(void) CurrentNS;
	(void) Type;
	(void) FirstUnresolvedAllusion;
	
	// TODO: Implement
	
	std :: vector <OilImplementBlock *> Blocks;
	
	Type.GetAllImplementBlocks ( Blocks );
	
	for ( uint32_t I = 0; I < Blocks.size (); I ++ )
	{
		
		OilImplementBlock * Block = Blocks [ I ];
		
		uint32_t FunctionCount = Block -> GetFunctionCount ();
		
		for ( uint32_t J = 0; J < FunctionCount; J ++ )
		{
			
			AllusionResolutionResult Result = OilResolveAllusions_Function ( CurrentNS, * Block -> GetFunction ( J ), FirstUnresolvedAllusion, Block -> GetImplementedType () );
			
			if ( Result == kAllusionResolutionResult_Success_Complete )
				Progress = true;
			else if ( Result == kAllusionResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( Result == kAllusionResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return Result;
			
		}
		
		uint32_t MethodCount = Block -> GetMethodCount ();
		
		for ( uint32_t J = 0; J < MethodCount; J ++ )
		{
			
			AllusionResolutionResult Result = OilResolveAllusions_Method ( CurrentNS, * Block -> GetMethod ( J ), FirstUnresolvedAllusion, Block -> GetImplementedType () );
			
			if ( Result == kAllusionResolutionResult_Success_Complete )
				Progress = true;
			else if ( Result == kAllusionResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( Result == kAllusionResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return Result;
			
		}
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilResolveAllusions ( OilNamespaceDefinition & CurrentNS, OilAllusion *& FirstUnresolvedAllusion )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t FunctionCount = CurrentNS.GetFunctionDefinitionCount ();
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
	{
		
		OilFunctionDefinition * Function = CurrentNS.GetFunctionDefinition ( I );
		
		AllusionResolutionResult Result = OilResolveAllusions_Function ( CurrentNS, * Function, FirstUnresolvedAllusion );
		
		if ( Result == kAllusionResolutionResult_Success_Complete )
			Progress = true;
		else if ( Result == kAllusionResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( Result == kAllusionResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return Result;
		
	}
	
	uint32_t TypeCount = CurrentNS.GetTypeDefinitionCount ();
	
	for ( uint32_t I = 0; I < TypeCount; I ++ )
	{
		
		OilTypeDefinition * Type = CurrentNS.GetTypeDefinition ( I );
		
		AllusionResolutionResult Result = OilResolveAllusions_Type ( CurrentNS, * Type, FirstUnresolvedAllusion );
		
		if ( Result == kAllusionResolutionResult_Success_Complete )
			Progress = true;
		else if ( Result == kAllusionResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( Result == kAllusionResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return Result;
	}
	
	uint32_t NamespaceCount = CurrentNS.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < NamespaceCount; I ++ )
	{
		
		AllusionResolutionResult SubResult = OilResolveAllusions ( * CurrentNS.GetNamespaceDefinition ( I ), FirstUnresolvedAllusion );
		
		if ( SubResult == kAllusionResolutionResult_Success_Complete )
			Progress = true;
		else if ( SubResult == kAllusionResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( SubResult == kAllusionResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return SubResult;
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		else
			return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}
