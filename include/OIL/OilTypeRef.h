#ifndef OIL_OILTYPENAME_H
#define OIL_OILTYPENAME_H

#include <string>

class OilTemplateSpecification;

class OilTypeRef
{
public:
	
	OilTypeRef ( const std :: u32string & Name );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount );
	OilTypeRef ( const std :: u32string & Name, OilTemplateSpecification * OilTemplateSpecification );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * OilTemplateSpecification );
	~OilTypeRef ();
	
	bool IsNamespaced ();
	bool IsTemplated ();
	
	const std :: u32string & GetName ();
	
	uint32_t GetNamespaceNameCount ();
	const std :: u32string & GetNamespaceName ( uint32_t Index );
	
	OilTemplateSpecification * GetTemplateSpecification ();
	
private:
	
	const std :: u32string Name;
	std :: u32string * NamespaceNameList;
	const uint32_t NamespaceNameCount;
	OilTemplateSpecification * TemplateSpecification;
	
};

#endif
