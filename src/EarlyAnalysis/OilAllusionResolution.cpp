#include <EarlyAnalysis/OilAllusionResolution.h>

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

AllusionResolutionResult OilResolveAllusions_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, bool MethodContext, OilAllusionResolution_NameList * ParameterNameList, OilAllusionResolution_NameList * TemplateNameList )
{
	
	(void) CurrentNS;
	(void) Body;
	(void) MethodContext;
	(void) ParameterNameList;
	(void) TemplateNameList;
	
	// TODO: Implement
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilResolveAllusions_Function ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function )
{
	
	bool Progress = false;
	bool Unresolved = false;
	
	if ( Function.IsNative () )
		return kAllusionResolutionResult_Success_Complete;
	
	OilStatementBody * Body = Function.GetStatementBody ();
	OilFunctionParameterList * ParamList = Function.GetParameterList ();
	
	OilAllusionResolution_NameList ParameterNames;
	
	uint32_t ParamCount = ParamList -> GetParameterCount ();
	
	if ( ParamCount != 0 )
	{
		
		ParameterNames.Names = new std :: u32string [ ParamCount ];
		ParameterNames.Count = ParamCount;
		
		for ( uint32_t I = 0; I < ParamCount; I ++ )
			ParameterNames.Names [ I ] = ParamList -> GetFunctionParameter ( I ) -> GetName ();
		
	}
	
	OilTemplateDefinition * TemplateDef = Function.IsTemplated () ? Function.GetTemplateDefinition () : NULL;
	
	OilAllusionResolution_NameList TemplateNames;
	
	if ( TemplateDef != NULL )
	{
		
		uint32_t TemplateNameCount = TemplateDef -> GetTemplateParameterCount ();
		
		TemplateNames.Names = new std :: u32string [ TemplateNameCount ];
		TemplateNames.Count = TemplateNameCount;
		
		for ( uint32_t I = 0; I < TemplateNameCount; I ++ )
			TemplateNames.Names [ I ] = TemplateDef -> GetTemplateParameter ( I ) -> GetName ();
		
	}
	
	AllusionResolutionResult Result = OilResolveAllusions_StatementBody ( CurrentNS, * Body, false, ( ParamCount != 0 ) ? & ParameterNames : NULL, ( TemplateDef != NULL ) ? & TemplateNames : NULL );
	
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
	{
		
		if ( ParamCount != 0 )
			delete [] ParameterNames.Names;
		
		return Result;
		
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


AllusionResolutionResult OilResolveAllusions_Type ( OilNamespaceDefinition & CurrentNS, OilTypeDefinition & Type )
{
	
	(void) CurrentNS;
	(void) Type;
	
	// TODO: Implement
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilResolveAllusions ( OilNamespaceDefinition & CurrentNS )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	uint32_t FunctionCount = CurrentNS.GetFunctionDefinitionCount ();
	
	for ( uint32_t I = 0; I < FunctionCount; I ++ )
	{
		
		OilFunctionDefinition * Function = CurrentNS.GetFunctionDefinition ( I );
		
		AllusionResolutionResult Result = OilResolveAllusions_Function ( CurrentNS, * Function );
		
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
		
		AllusionResolutionResult Result = OilResolveAllusions_Type ( CurrentNS, * Type );
		
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
		
		AllusionResolutionResult SubResult = OilResolveAllusions ( * CurrentNS.GetNamespaceDefinition ( I ) );
		
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
