#include <EarlyAnalysis/OilAnalysisTools.h>

#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilMethodParameterList.h>

void MakeNameList_TemplateDefinition ( OilTemplateDefinition & Template, FlatNameList & List, FlatNameList * BaseList )
{
	
	uint32_t Count = Template.GetTemplateParameterCount () + ( ( BaseList != NULL ) ? BaseList -> Count : 0 );
	
	List.Count = Count;
	List.Names = new std :: u32string [ Count ];
	
	if ( BaseList != NULL )
	{
		
		for ( uint32_t I = 0; I < BaseList -> Count; I ++ )
			List.Names [ I ] = BaseList -> Names [ I ];
		
	}
	
	for ( uint32_t I = ( BaseList != NULL ) ? BaseList -> Count : 0; I < Count; I ++ )
		List.Names [ I ] = Template.GetTemplateParameter ( I - ( ( BaseList != NULL ) ? BaseList -> Count : 0 ) ) -> GetName ();
	
}

void MakeNameList_FunctionParameters ( OilFunctionParameterList & ParamList, FunctionParamList & List, bool & NotEmpty )
{
	
	uint32_t Count = ParamList.GetParameterCount ();
	
	if ( Count == 0 )
	{
		
		NotEmpty = false;
		return;
		
	}
	
	NotEmpty = true;
	
	List.Count = Count;
	List.Params = new OilFunctionParameter * [ Count ];
	
	for ( uint32_t I = 0; I < Count; I ++ )
		List.Params [ I ] = ParamList.GetFunctionParameter ( I );
	
}


void MakeNameList_MethodParameters ( OilMethodParameterList & ParamList, FunctionParamList & List, bool & NotEmpty )
{
	
	uint32_t Count = ParamList.GetParameterCount ();
	
	if ( Count == 0 )
	{
		
		NotEmpty = false;
		return;
		
	}
	
	NotEmpty = true;
	
	List.Count = Count;
	List.Params = new OilFunctionParameter * [ Count ];
	
	for ( uint32_t I = 0; I < Count; I ++ )
		List.Params [ I ] = ParamList.GetFunctionParameter ( I );
	
}

void DestroyFlatNameList ( FlatNameList & List )
{
	
	if ( List.Names == NULL )
		return;
	
	delete [] List.Names;
	List.Names = NULL;
	
}

void DestroyFunctionParamList ( FunctionParamList & List )
{
	
	if ( List.Params == NULL )
		return;
	
	delete [] List.Params;
	List.Params = NULL;
	
}
