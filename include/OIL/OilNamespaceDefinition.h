#ifndef OIL_OILNAMESPACEDEFINITION_H
#define OIL_OILNAMESPACEDEFINITION_H

#include <string>
#include <map>

class OilStructDefinition;

class OilNamespaceDefinition
{
public:
		
	OilNamespaceDefinition ( const std :: u32string & ID );
	~OilNamespaceDefinition ();
	
	const uint32_t GetSubNamespaceDefinitionCount () const;
	
	OilNamespaceDefinition * GetNamespaceDefinition ( uint32_t Index );
	const OilNamespaceDefinition * GetNamespaceDefinition ( uint32_t Index ) const;
	
	OilNamespaceDefinition * FindOrCreateNamespaceDefinition ( const std :: u32string & ID );
	const OilNamespaceDefinition * FindNamespaceDefinition ( const std :: u32string & ID ) const;
	
	const uint32_t GetStructDefinitionCount () const;
	
	OilStructDefinition * GetStructDefinition ( uint32_t Index );
	const OilStructDefinition * GetStructDefinition ( uint32_t Index ) const;
	const OilStructDefinition * FindStructDefinition ( const std :: u32string & ID ) const;
	
	const std :: u32string GetID () const;
	
private:
	
	const std :: u32string ID;
	
	std :: map <std :: u32string, OilNamespaceDefinition *> SubNamespaces;
	std :: map <std :: u32string, OilStructDefinition *> StructDefs;
	
};

#endif
