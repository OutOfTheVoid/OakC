#ifndef EARLYANALYSIS_OILTYPERESOLUTION_H
#define EARLYANALYSIS_OILTYPERESOLUTION_H

#include <EarlyAnalysis/OilAnalysisTools.h>

#include <string>

enum TypeResolutionResult
{
	
	kTypeResolutionResult_Success_Complete,
	kTypeResolutionResult_Success_Progress,
	kTypeResolutionResult_Success_NoProgress,
	kTypeResolutionResult_Failure_TemplateMismatch,
	kTypeResolutionResult_Failure_NonExistantType,
	
};

class OilNamespaceDefinition;
class OilConstStatement;
class OilBindingStatement;
class OilTypeRef;
class OilTemplateSpecification;
class OilStructDefinition;
class OilTemplateDefinition;
class OilFunctionDefinition;
class OilMethodDefinition;
class OilTypeDefinition;
class OilTypeAlias;
class OilStatementBody;
class OilExpression;

TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL, OilTemplateSpecification * SelfTemplateSpec = NULL );
TypeResolutionResult OilTypeResolution_TemplateSpecification ( OilNamespaceDefinition & CurrentNS, OilTemplateSpecification & TemplateSpecification, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_TemplateDefinition ( OilNamespaceDefinition & CurrentNS, OilTemplateDefinition & TemplateDefinition, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_FunctionDefinition ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL, OilTemplateSpecification * SelfTemplateSpec = NULL );
TypeResolutionResult OilTypeResolution_MethodDefinition ( OilNamespaceDefinition & CurrentNS, OilMethodDefinition & Method, OilTypeDefinition & SelfType, OilTemplateSpecification * SelfTemplateSpec, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_TypeAlias ( OilNamespaceDefinition & CurrentNS, OilTypeAlias & Alias );
TypeResolutionResult OilTypeResolution_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL, OilTemplateSpecification * SelfTemplateSpec = NULL );
TypeResolutionResult OilTypeResolution_Expression ( OilNamespaceDefinition & CurrentNS, OilExpression & Expression, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL, OilTemplateSpecification * SelfTemplateSpec = NULL );

TypeResolutionResult OilTypeResolution_StructDefinitions ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Constants ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Bindings ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Functions ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_ImplementMembers ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_TypeAliases ( OilNamespaceDefinition & RootNS );

#endif
