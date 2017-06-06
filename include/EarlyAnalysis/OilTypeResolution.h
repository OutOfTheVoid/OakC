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
class OilUnaryOperator;
class OilBinaryOperator;
class IOilPrimary;
class OilAllusion;
class OilTraitDefinition;
class OilTraitFunction;
class OilTraitMethod;


TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_TemplateSpecification ( OilNamespaceDefinition & CurrentNS, OilTemplateSpecification & TemplateSpecification, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_TemplateDefinition ( OilNamespaceDefinition & CurrentNS, OilTemplateDefinition & TemplateDefinition, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_FunctionDefinition ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_MethodDefinition ( OilNamespaceDefinition & CurrentNS, OilMethodDefinition & Method, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_TypeAlias ( OilNamespaceDefinition & CurrentNS, OilTypeAlias & Alias );
TypeResolutionResult OilTypeResolution_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_Expression ( OilNamespaceDefinition & CurrentNS, OilExpression & Expression, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_UnaryOperator ( OilNamespaceDefinition & CurrentNS, OilUnaryOperator & Operator, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_BinaryOperator ( OilNamespaceDefinition & CurrentNS, OilBinaryOperator & Operator, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_Primary ( OilNamespaceDefinition & CurrentNS, IOilPrimary * Primary, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_Allusion ( OilNamespaceDefinition & CurrentNS, OilAllusion & Allusion, FlatNameList * TemplateNames = NULL, bool AllowSelfType = false );
TypeResolutionResult OilTypeResolution_Trait ( OilNamespaceDefinition & CurrentNS, OilTraitDefinition & Trait );
TypeResolutionResult OilTypeResolution_TraitFunction ( OilNamespaceDefinition & CurrentNS, OilTraitFunction & Function, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_TraitMethod ( OilNamespaceDefinition & CurrentNS, OilTraitMethod & Method, FlatNameList * TemplateNames = NULL );

TypeResolutionResult OilTypeResolution_StructDefinitions ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Constants ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Bindings ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Functions ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_ImplementMembers ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_TypeAliases ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Traits ( OilNamespaceDefinition & RootNS );

#endif
