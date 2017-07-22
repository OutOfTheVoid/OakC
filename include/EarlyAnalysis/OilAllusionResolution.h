#ifndef EARLYANALYSIS_OILALLUSIONRESOLUTION_H
#define EARLYANALYSIS_OILALLUSIONRESOLUTION_H

#include <vector>
#include <unordered_map>
#include <string>

class OilNamespaceDefinition;
class OilBindingStatement;
class OilConstStatement;
class OilTypeDefinition;
class OilFunctionDefinition;
class OilTraitDefinition;
class OilTypeAlias;

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
		kMappingType_FunctionDefinition,
		kMappingType_TraitDefinition,
		kMappingType_TypeAlias,
		
	};
	
	typedef struct NameMapping_Struct
	{
		
		NameMapping_Struct ();
		NameMapping_Struct ( OilNamespaceDefinition * Namespace );
		NameMapping_Struct ( OilBindingStatement * BindingStatement );
		NameMapping_Struct ( OilConstStatement * ConstantStatement );
		NameMapping_Struct ( OilTypeDefinition * TypeDefinition );
		NameMapping_Struct ( OilFunctionDefinition * FunctionDefintiion );
		NameMapping_Struct ( OilTraitDefinition * TraitDefinition );
		NameMapping_Struct ( OilTypeAlias * TypeAlias );
		
		~NameMapping_Struct ();
		
		MappingType Type;
		
		union
		{
			
			OilNamespaceDefinition * Namespace;
			OilBindingStatement * BindingStatement;
			OilConstStatement * ConstantStatement;
			OilTypeDefinition * TypeDefinition;
			OilFunctionDefinition * FunctionDefintiion;
			OilTraitDefinition * TraitDefinition;
			OilTypeAlias * TypeAlias;
			
		};
		
	} NameMapping;
	
	OilAllusionResolution_NameMapStack ();
	~OilAllusionResolution_NameMapStack ();
	
	void PushContext ( NameContextType Context );
	void PopContext ();
	
	void AddNamespaceMapping ( const std :: u32string & Name, OilNamespaceDefinition * Namespace );
	void AddBindingStatementMapping ( const std :: u32string & Name, OilBindingStatement * BindingStatement );
	void AddConstStatementMapping ( const std :: u32string & Name, OilConstStatement * ConstantStatement );
	void AddTypeMapping ( const std :: u32string & Name, OilTypeDefinition * TypeDefinition );
	void AddFunctionMapping ( const std :: u32string & Name, OilFunctionDefinition * FunctionDefintiion );
	void AddTraitMapping ( const std :: u32string & Name, OilTraitDefinition * TraitDefinition );
	void AddTypeAliasMapping ( const std :: u32string & Name, OilTypeAlias * TypeAlias );
	
	NameMapping LookupName ( const std :: u32string Name );
	void ReadInScopeNames ( std :: vector <std :: u32string> & Out );
	
private:
	
	typedef struct NameContext_Struct
	{
		
		NameContext_Struct ( NameContextType Type );
		NameContext_Struct ( const NameContext_Struct & CopyFrom );
		~NameContext_Struct ();
		
		NameContextType Type;
		
		std :: vector <std :: u32string> Names;
		
	} NameContext;
	
	std :: vector <NameContext *> Contexts;
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> NameMap;
	
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
