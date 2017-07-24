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
	kTypeResolutionResult_Failure_NonTrait,
	
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
class OilEnum;
class OilMatchBranch;
class OilTraitDefinition;

TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL, OilTraitDefinition * SelfTrait = NULL );
TypeResolutionResult OilTypeResolution_TemplateSpecification ( OilNamespaceDefinition & CurrentNS, OilTemplateSpecification & TemplateSpecification, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_TemplateDefinition ( OilNamespaceDefinition & CurrentNS, OilTemplateDefinition & TemplateDefinition, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_FunctionDefinition ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_MethodDefinition ( OilNamespaceDefinition & CurrentNS, OilMethodDefinition & Method, OilTypeDefinition * SelfType, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_TypeAlias ( OilNamespaceDefinition & CurrentNS, OilTypeAlias & Alias );
TypeResolutionResult OilTypeResolution_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_Expression ( OilNamespaceDefinition & CurrentNS, OilExpression & Expression, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_UnaryOperator ( OilNamespaceDefinition & CurrentNS, OilUnaryOperator & Operator, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_BinaryOperator ( OilNamespaceDefinition & CurrentNS, OilBinaryOperator & Operator, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_Primary ( OilNamespaceDefinition & CurrentNS, IOilPrimary * Primary, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_Allusion ( OilNamespaceDefinition & CurrentNS, OilAllusion & Allusion, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );
TypeResolutionResult OilTypeResolution_Trait ( OilNamespaceDefinition & CurrentNS, OilTraitDefinition & Trait );
TypeResolutionResult OilTypeResolution_TraitFunction ( OilNamespaceDefinition & CurrentNS, OilTraitFunction & Function, OilTraitDefinition * SelfTrait, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_TraitMethod ( OilNamespaceDefinition & CurrentNS, OilTraitMethod & Method, OilTraitDefinition * SelfTrait, FlatNameList * TemplateNames = NULL );
TypeResolutionResult OilTypeResolution_Enum ( OilNamespaceDefinition & CurrentNS, OilEnum & Enum );
TypeResolutionResult OilTypeResolution_MatchBranch ( OilNamespaceDefinition & CurrentNS, OilMatchBranch & Branch, FlatNameList * TemplateNames = NULL, OilTypeDefinition * SelfType = NULL );

TypeResolutionResult OilTypeResolution_TypeDefinitions ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Constants ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Bindings ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Functions ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_ImplementMembers ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_TypeAliases ( OilNamespaceDefinition & RootNS );
TypeResolutionResult OilTypeResolution_Traits ( OilNamespaceDefinition & RootNS );

#endif
