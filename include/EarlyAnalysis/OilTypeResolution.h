#ifndef EARLYANALYSIS_OILTYPERESOLUTION_H
#define EARLYANALYSIS_OILTYPERESOLUTION_H

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

TypeResolutionResult OilTypeResolution_TypeRef ( OilNamespaceDefinition & CurrentNS, OilTypeRef & TypeRef );
TypeResolutionResult OilTypeResolution_TemplateSpecification ( OilNamespaceDefinition & CurrentNS, OilTemplateSpecification & TemplateSpecification );

TypeResolutionResult OilResolveTypes_Constants ( OilNamespaceDefinition & RootNS, OilConstStatement *& FailedStatement );
TypeResolutionResult OilResolveTypes_Bindings ( OilNamespaceDefinition & RootNS, OilBindingStatement *& FailedStatement );
//TypeResolutionResult OilResolveTypes_StructBindings ( OilNamespaceDefinition & RootNS, OilStructDefinition *& FailedStruct, std :: u32string & FailedBindingName );

#endif
