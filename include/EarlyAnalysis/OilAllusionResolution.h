#ifndef EARLYANALYSIS_OILALLUSIONRESOLUTION_H
#define EARLYANALYSIS_OILALLUSIONRESOLUTION_H

#include <vector>
#include <map>
#include <string>

class OilNamespaceDefinition;
class OilBindingStatement;
class OilConstStatement;
class OilTypeDefinition;

class OilAllusionResolution_NameMapStack
{
public:
	
	enum NameContextType
	{
		
		kNameContext_Namespace,
		kNameContext_Function,
		kNameContext_Template,
		kNameContext_Match,
		kNameContext_MatchBranch,
		kNameContext_StatementBlock
		
	};
	
	enum MappingType
	{
		
		kMappingType_None,
		kMappingType_Namespace,
		kMappingType_BindingStatement,
		kMappingType_ConstantStatement,
		kMappingType_TypeDefinition,
		
	};
	
	typedef struct NameMapping_Struct
	{
		
		NameMapping_Struct ();
		NameMapping_Struct ( OilNamespaceDefinition * Namespace );
		NameMapping_Struct ( OilBindingStatement * BindingStatement );
		NameMapping_Struct ( OilConstStatement * ConstantStatement );
		NameMapping_Struct ( OilTypeDefinition * TypeDefinition );
		
		MappingType Type;
		
		union
		{
			
			OilNamespaceDefinition * Namespace;
			OilBindingStatement * BindingStatement;
			OilConstStatement * ConstantStatement;
			OilTypeDefinition * TypeDefinition;
			
		};
		
	} NameMapping;
	
	OilAllusionResolution_NameMapStack ();
	~OilAllusionResolution_NameMapStack ();
	
	void PushContext ( NameContextType Context );
	void PopContext ();
	
	void AddNamespaceMapping ( const std :: u32string Name, OilNamespaceDefinition * Namespace );
	void AddBindingStatementMapping ( const std :: u32string Name, OilBindingStatement * BindingStatement );
	void AddConstStatementMapping ( const std :: u32string Name, OilBindingStatement * ConstantStatement );
	void AddTypeMapping ( const std :: u32string Name, OilTypeDefinition * TypeMapping );
	
	NameMapping LookupName ( const std :: u32string Name );
	
private:
	
	typedef struct NameContext_Struct
	{
		
		NameContext_Struct ( NameContextType Type );
		~NameContext_Struct ();
		
		NameContextType Type;
		
		std :: vector <std :: u32string> Names;
		
	} NameContext;
	
	std :: vector <NameContext *> Contexts;
	std :: map <std :: u32string, std :: vector <NameMapping>> NameMap;
	
};

enum AllusionResolutionResult
{
	
	kAllusionResolutionResult_Success_Complete,
	kAllusionResolutionResult_Success_Progress,
	kAllusionResolutionResult_Success_NoProgress,
	kAllusionResolutionResult_Error
	
};

AllusionResolutionResult OilAllusionResolution_Root ( OilNamespaceDefinition & RootNS );

#endif
