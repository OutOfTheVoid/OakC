#ifndef EARLYANALYSIS_OILALLUSIONRESOLUTION_H
#define EARLYANALYSIS_OILALLUSIONRESOLUTION_H

#include <stdint.h>
#include <string>

#include <EarlyAnalysis/OilAnalysisTools.h>

class OilNamespaceDefinition;
class OilFunctionDefinition;
class OilTypeDefinition;
class OilStatementBody;
class OilAllusion;
class OilExpression;
class OilTypeRef;

enum AllusionResolutionResult
{
	
	kAllusionResolutionResult_Success_Complete,
	kAllusionResolutionResult_Success_Progress,
	kAllusionResolutionResult_Success_NoProgress,
	kAllusionResolutionResult_Failure_AllusionNotFound,
	kAllusionResolutionResult_Failure_WritesImmutable,
	
};

AllusionResolutionResult OilResolveAllusions_Expression ( OilNamespaceDefinition & CurrentNS, OilExpression & Expression, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion );

AllusionResolutionResult OilResolveAllusions_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion );

AllusionResolutionResult OilResolveAllusions_Function ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function, OilAllusion *& FirstUnresolvedAllusion, OilTypeRef * SelfType = NULL );
AllusionResolutionResult OilResolveAllusions_Type ( OilNamespaceDefinition & CurrentNS, OilTypeDefinition & Type, OilAllusion *& FirstUnresolvedAllusion );

AllusionResolutionResult OilResolveAllusions ( OilNamespaceDefinition & RootNS, OilAllusion *& FirstUnresolvedAllusion );

#endif
