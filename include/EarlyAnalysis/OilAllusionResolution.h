#ifndef EARLYANALYSIS_OILALLUSIONRESOLUTION_H
#define EARLYANALYSIS_OILALLUSIONRESOLUTION_H

#include <stdint.h>
#include <string>

#include <EarlyAnalysis/OilAnalysisTools.h>

class OilNamespaceDefinition;
class OilFunctionDefinition;
class OilMethodDefinition;
class OilTypeDefinition;
class OilStatementBody;
class OilAllusion;
class OilExpression;
class OilTypeRef;
class OilBinaryOperator;
class OilUnaryOperator;
class IOilStatement;

enum AllusionResolutionResult
{
	
	kAllusionResolutionResult_Success,
	kAllusionResolutionResult_Failure_AllusionNotFound,
	kAllusionResolutionResult_Failure_AllusionToNamespace,
	kAllusionResolutionResult_Failure_AllusionToType,
	kAllusionResolutionResult_Failure_NonMethodAllusionToSelf,
	kAllusionResolutionResult_Failure_TemplateMismatch,
	kAllusionResolutionResult_Failure_TemplateTypeResolution,
	
};

AllusionResolutionResult OilResolveAllusions_Allusion ( OilNamespaceDefinition & CurrentNS, OilAllusion & Allusion, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion );

AllusionResolutionResult OilResolveAllusions_UnaryOperator ( OilNamespaceDefinition & CurrentNS, OilUnaryOperator & Allusion, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion );
AllusionResolutionResult OilResolveAllusions_BinaryOperator ( OilNamespaceDefinition & CurrentNS, OilBinaryOperator & Allusion, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion );
AllusionResolutionResult OilResolveAllusions_Expression ( OilNamespaceDefinition & CurrentNS, OilExpression & Expression, uint64_t StatementRootIndex, OilStatementBody & ContainerBody, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion );

AllusionResolutionResult OilResolveAllusions_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, bool MethodContext, FunctionParamList * ParameterNameList, FlatNameList * TemplateNameList, OilTypeRef * SelfType, OilAllusion *& FirstUnresolvedAllusion );

AllusionResolutionResult OilResolveAllusions_Function ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function, OilAllusion *& FirstUnresolvedAllusion, OilTypeRef * SelfType = NULL );
AllusionResolutionResult OilResolveAllusions_Method ( OilNamespaceDefinition & CurrentNS, OilMethodDefinition & Method, OilAllusion *& FirstUnresolvedAllusion, OilTypeRef * SelfType );
AllusionResolutionResult OilResolveAllusions_Type ( OilNamespaceDefinition & CurrentNS, OilTypeDefinition & Type, OilAllusion *& FirstUnresolvedAllusion );

AllusionResolutionResult OilResolveAllusions ( OilNamespaceDefinition & RootNS, OilAllusion *& FirstUnresolvedAllusion );

#endif
