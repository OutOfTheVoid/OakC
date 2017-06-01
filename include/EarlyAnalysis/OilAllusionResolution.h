#ifndef EARLYANALYSIS_OILALLUSIONRESOLUTION_H
#define EARLYANALYSIS_OILALLUSIONRESOLUTION_H

#include <stdint.h>
#include <string>

class OilNamespaceDefinition;
class OilFunctionDefinition;
class OilTypeDefinition;
class OilStatementBody;

enum AllusionResolutionResult
{
	
	kAllusionResolutionResult_Success_Complete,
	kAllusionResolutionResult_Success_Progress,
	kAllusionResolutionResult_Success_NoProgress,
	kAllusionResolutionResult_Failure_AllusionNotFound,
	kAllusionResolutionResult_Failure_WritesImmutable,
	
};

typedef struct
{
	
	std :: u32string * Names;
	uint32_t Count;
	
} OilAllusionResolution_NameList;

AllusionResolutionResult OilResolveAllusions_StatementBody ( OilNamespaceDefinition & CurrentNS, OilStatementBody & Body, bool MethodContext, OilAllusionResolution_NameList * ParameterNameList, OilAllusionResolution_NameList * TemplateNameList );

AllusionResolutionResult OilResolveAllusions_Function ( OilNamespaceDefinition & CurrentNS, OilFunctionDefinition & Function );
AllusionResolutionResult OilResolveAllusions_Type ( OilNamespaceDefinition & CurrentNS, OilTypeDefinition & Type );

AllusionResolutionResult OilResolveAllusions ( OilNamespaceDefinition & RootNS );

#endif
