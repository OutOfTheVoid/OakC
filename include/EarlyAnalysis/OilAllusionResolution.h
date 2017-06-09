#ifndef EARLYANALYSIS_OILALLUSIONRESOLUTION_H
#define EARLYANALYSIS_OILALLUSIONRESOLUTION_H

class OilNamespaceDefinition;

enum AllusionResolutionResult
{
	
	kAllusionResolutionResult_Success_Complete,
	kAllusionResolutionResult_Success_Progress,
	kAllusionResolutionResult_Success_NoProgress
	
};

AllusionResolutionResult OilAllusionResolution_Namespace ( OilNamespaceDefinition & NS );

#endif
