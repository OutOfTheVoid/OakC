#ifndef OIL_OILOBJECTBLOCK_H
#define OIL_OILOBJECTBLOCK_H

class OilNamespaceDefinitionBlock;

class OilObjectBlock
{
public:
	
	OilObjectBlock ();
	~OilObjectBlock ();
	
	const uint32_t GetNamespaceDefinitionBlockCount () const;
	
	AddNamespaceDefinitionBlock * GetNamespaceDefinitionBlock ( uint32_t Index );
	const AddNamespaceDefinitionBlock * FindNamespaceDefinitionBlock ( uint32_t Index ) const;
	
	AddNamespaceDefinitionBlock * FindOrCreateNamespaceDefinitionBlock ( const std :: u32string & ID );
	const AddNamespaceDefinitionBlock * FindNamespaceDefinitionBlock ( const std :: u32string & ID ) const;
	
	OilNamespaceDefinitionBlock & GetGlobalNamespace ();
	const OilNamespaceDefinitionBlock & GetGlobalNamespace () const;
	
private:
	
	std :: map <std :: u32string, OilNamespaceDefinitionBlock *> GlobalNamespaces;
	OilNamespaceDefinitionBlock GlobalNamespace;
	
};

#endif
