#ifndef EARLYANALYSIS_OILANALYSISTOOLS_H
#define EARLYANALYSIS_OILANALYSISTOOLS_H

#include <string>

class OilTemplateDefinition;
class OilFunctionParameterList;
class OilFunctionParameter;
class OilMethodParameterList;

typedef struct FlatNameList_Struct
{
	
	inline FlatNameList_Struct ():
		Names ( NULL ),
		Count ( 0 )
	{
	}
	
	std :: u32string * Names;
	uint32_t Count;
	
} FlatNameList;

typedef struct FunctionParamList_Struct
{
	
	inline FunctionParamList_Struct ():
		Params ( NULL ),
		Count ( 0 )
	{
	}
	
	OilFunctionParameter ** Params;
	uint32_t Count;
	
} FunctionParamList;

void MakeNameList_TemplateDefinition ( OilTemplateDefinition & Template, FlatNameList & NameList, FlatNameList * BaseList = NULL );
void MakeNameList_FunctionParameters ( OilFunctionParameterList & ParamList, FunctionParamList & List, bool & NotEmpty );
void MakeNameList_MethodParameters ( OilMethodParameterList & ParamList, FunctionParamList & List, bool & NotEmpty );

void DestroyFlatNameList ( FlatNameList & NameList );
void DestroyFunctionParamList ( FunctionParamList & List );

#endif
