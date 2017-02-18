#ifndef OIL_OILOBJECTBLOCK_H
#define OIL_OILOBJECTBLOCK_H

class OILNamespaceDefinitionBlock;

class OILObjectBlock
{
public:
	
	OILObjectBlock ( const std :: u32string & SourceFileName );
	~OILObjectBlock ();
	
	void AddNamespaceDefinitionBlock ( OILNamespaceDefinitionBlock * Block );
	
	const uint32_t GetNamespaceDefinitionBlockCount ();
	
	AddNamespaceDefinitionBlock * GetNamespaceDefinitionBlock ( uint32_t Index );
	const AddNamespaceDefinitionBlock * GetNamespaceDefinitionBlock ( uint32_t Index ) const;
	
private:
	
	
	
};

#endif
