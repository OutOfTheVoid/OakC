#ifndef EARLYANALYSIS_OILTYPERESOLUTION_H
#define EARLYANALYSIS_OILTYPERESOLUTION_H

enum TypeResolutionResult
{
	
	kTypeResolutionResult_Success,
	kTypeResolutionResult_Failure_TemplateMismatch,
	kTypeResolutionResult_Failure_NonExistantType,
	
};

class OilNamespaceDefinition;
class OilConstStatement;
class OilBindingStatement;

TypeResolutionResult OilResolveTypes_Constants ( OilNamespaceDefinition & RootNS, OilConstStatement *& FailedStatement );
TypeResolutionResult OilResolveTypes_Bindings ( OilNamespaceDefinition & RootNS, OilBindingStatement *& FailedStatement );

#endif
