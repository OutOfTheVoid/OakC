#ifndef OIL_OILNAMESPACEDEFINITION_H
#define OIL_OILNAMESPACEDEFINITION_H

#include <OIL/OilStatementBody.h>

#include <stdint.h>

#include <string>
#include <map>

#include <Tokenization/SourceRef.h>

class OilStructDefinition;
class OilTypeDefinition;
class OilFunctionDefinition;
class OilBindingStatement;
class OilTraitDefinition;
class OilImplementBlock;
class OilConstStatement;
class OilTypeAlias;

class OilNamespaceDefinition
{
public:
	
	enum NameSearchResultType
	{
		
		kNameSearchResultType_None,
		kNameSearchResultType_SubNamespace,
		kNameSearchResultType_TypeDefinition,
		kNameSearchResultType_FunctionDefinition,
		kNameSearchResultType_BindingStatement,
		kNameSearchResultType_ConstStatement,
		kNameSearchResultType_TraitDefinition,
		kNameSearchResultType_TypeAlias,
		
	};
	
	typedef struct
	{
		
		NameSearchResultType Type;
		
		union
		{
			
			OilNamespaceDefinition * NamespaceDefinition;
			OilTypeDefinition * TypeDefinition;
			OilFunctionDefinition * FunctionDefinition;
			OilBindingStatement * BindingStatement;
			OilConstStatement * ConstStatement;
			OilTraitDefinition * TraitDefinition;
			OilTypeAlias * Alias;
			
		};
		
		
	} NameSearchResult;
	
	typedef struct
	{
		
		NameSearchResultType Type;
		
		union
		{
			
			const OilNamespaceDefinition * NamespaceDefinition;
			const OilTypeDefinition * TypeDefinition;
			const OilFunctionDefinition * FunctionDefinition;
			const OilBindingStatement * BindingStatement;
			const OilConstStatement * ConstStatement;
			const OilTraitDefinition * TraitDefinition;
			
		};
		
		
	} NameSearchResultConst;
		
	OilNamespaceDefinition ( const SourceRef & Ref, const std :: u32string & ID );
	~OilNamespaceDefinition ();
	
	void SearchName ( const std :: u32string & Name, NameSearchResult & Result );
	void SearchName ( const std :: u32string & Name, NameSearchResultConst & Result ) const;
	
	uint32_t GetSubNamespaceDefinitionCount () const;
	
	OilNamespaceDefinition * GetNamespaceDefinition ( uint32_t Index );
	const OilNamespaceDefinition * GetNamespaceDefinition ( uint32_t Index ) const;
	
	OilNamespaceDefinition * FindOrCreateNamespaceDefinition ( const SourceRef & Ref, const std :: u32string & ID );
	
	OilNamespaceDefinition * FindNamespaceDefinition ( const std :: u32string & ID );
	const OilNamespaceDefinition * FindNamespaceDefinition ( const std :: u32string & ID ) const;
	
	uint32_t GetTypeDefinitionCount () const;
	
	void AddTypeDefinition ( OilTypeDefinition * TypeDef );
	
	OilTypeDefinition * GetTypeDefinition ( uint32_t Index );
	const OilTypeDefinition * GetTypeDefinition ( uint32_t Index ) const;
	
	OilTypeDefinition * FindTypeDefinition ( const std :: u32string & ID );
	const OilTypeDefinition * FindTypeDefinition ( const std :: u32string & ID ) const;
	
	uint32_t GetFunctionDefinitionCount () const;
	
	void AddFunctionDefinition ( OilFunctionDefinition * FuncDef );
	
	OilFunctionDefinition * GetFunctionDefinition ( uint32_t Index );
	const OilFunctionDefinition * GetFunctionDefinition ( uint32_t Index ) const;
	
	OilFunctionDefinition * FindFunctionDefinition ( const std :: u32string & ID );
	const OilFunctionDefinition * FindFunctionDefinition ( const std :: u32string & ID ) const;
	
	void AddBindingStatement ( OilBindingStatement * BindingStatement );
	
	uint32_t GetBindingStatementCount () const;
	
	OilBindingStatement * GetBindingStatement ( uint32_t Index );
	const OilBindingStatement * GetBindingStatement ( uint32_t Index ) const;
	
	OilBindingStatement * FindBindingStatement ( const std :: u32string & ID );
	const OilBindingStatement * FindBindingStatement ( const std :: u32string & ID ) const;
	
	void AddConstStatement ( OilConstStatement * ConstStatement );
	
	uint32_t GetConstStatementCount () const;
	
	OilConstStatement * GetConstStatement ( uint32_t Index );
	const OilConstStatement * GetConstStatement ( uint32_t Index ) const;
	
	OilConstStatement * FindConstStatement ( const std :: u32string & ID );
	const OilConstStatement * FindConstStatement ( const std :: u32string & ID ) const;
	
	OilStatementBody & GetImplicitInitializationBody ();
	const OilStatementBody & GetImplicitInitializationBody () const;
	
	uint32_t GetTraitDefinitionCount () const;
	
	void AddTraitDefinition ( OilTraitDefinition * TraitDef );
	
	OilTraitDefinition * GetTraitDefinition ( uint32_t Index );
	const OilTraitDefinition * GetTraitDefinition ( uint32_t Index ) const;
	
	OilTraitDefinition * FindTraitDefinition ( const std :: u32string & ID );
	const OilTraitDefinition * FindTraitDefinition ( const std :: u32string & ID ) const;
	
	const std :: u32string GetID () const;
	
	OilNamespaceDefinition * GetParent ();
	const OilNamespaceDefinition * GetParent () const;
	
	uint32_t GetUnresolvedImplementBlockCount () const;
	
	void AddUnresolvedImplementBlock ( OilImplementBlock * Block );
	
	OilImplementBlock * GetUnresolvedImplementBlock ( uint32_t Index );
	const OilImplementBlock * GetUnresolvedImplementBlock ( uint32_t Index ) const;
	
	void RemoveUnresolvedImplementBlock ( uint32_t Index );
	
	const SourceRef & GetSourceRef () const;
	
	uint32_t GetTypeAliasCount () const;
	
	void AddTypeAlias ( OilTypeAlias * Alias );
	
	OilTypeAlias * GetTypeAlias ( uint32_t Index );
	const OilTypeAlias * GetTypeAlias ( uint32_t Index ) const;
	
	OilTypeAlias * FindTypeAlias ( const std :: u32string & Name );
	const OilTypeAlias * FindTypeAlias ( const std :: u32string & Name ) const;
	
private:
	
	OilNamespaceDefinition * Parent;
	
	const std :: u32string ID;
	
	std :: map <std :: u32string, OilNamespaceDefinition *> SubNamespaces;
	std :: map <std :: u32string, OilTypeDefinition *> TypeDefs;
	std :: map <std :: u32string, OilFunctionDefinition *> FuncDefs;
	std :: map <std :: u32string, OilTraitDefinition *> TraitDefs;
	
	std :: map <std :: u32string, OilBindingStatement *> Bindings;
	OilStatementBody ImplicitIntiailizationBody;
	
	std :: map <std :: u32string, OilConstStatement *> Constants;
	
	std :: vector <OilImplementBlock *> UnresImplBlocks;
	
	std :: map <std :: u32string, OilTypeAlias *> Aliases;
	
	SourceRef Ref;
	
};

#endif
