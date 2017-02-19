#ifndef OIL_OILNAMESPACEDEFINITIONBLOCK_H
#define OIL_OILNAMESPACEDEFINITIONBLOCK_H

#include <string>

class OilNamespaceDefinitionBlock
{
public:
		
	OilNamespaceDefinitionBlock ( const std :: u32string & ID );
	~OilNamespaceDefinitionBlock ();
	
private:
	
	const std :: u32string ID;
	
	std :: map <std :: u32string, OilNamespaceDefinitionBlock *> ChildNamespaces;
	
};

#endif
