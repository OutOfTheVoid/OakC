#ifndef OIL_OILFILEBLOCK_H
#define OIL_OILFILEBLOCK_H

class OILNamespaceDefinitionBlock;

class OILFileBlock
{
public:
	
	OILFileBlock ( const std :: u32string & SourceFileName );
	~OILFileBlock ();
	
	void AddNamespaceDefinitionBlock ( OILNamespaceDefinitionBlock * Block );
	
	const std :: u32string & GetSourceFileName () const;
	
	const uint32_t GetNamespaceDefinitionBlockCount ();
	
	AddNamespaceDefinitionBlock * GetNamespaceDefinitionBlock ( uint32_t Index );
	const AddNamespaceDefinitionBlock * GetNamespaceDefinitionBlock ( uint32_t Index ) const;
	
private:
	
	
	
}

#endif
