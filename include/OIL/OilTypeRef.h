#ifndef OIL_OILTYPENAME_H
#define OIL_OILTYPENAME_H

#include <string>

class OilTemplateSpecification;

class OilTypeRef
{
public:
	
	typedef uint32_t RefFlag;
	
	static const RefFlag kRefFlag_None = 0;
	static const RefFlag kRefFlag_Trait = 1;
	
	OilTypeRef ( const std :: u32string & Name, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	~OilTypeRef ();
	
	bool IsNamespaced ();
	bool IsTemplated ();
	
	const std :: u32string & GetName ();
	
	uint32_t GetNamespaceNameCount ();
	const std :: u32string & GetNamespaceName ( uint32_t Index );
	
	OilTemplateSpecification * GetTemplateSpecification ();
	
	RefFlag GetFlags ();
	
private:
	
	const std :: u32string Name;
	
	std :: u32string * NamespaceNameList;
	const uint32_t NamespaceNameCount;
	
	OilTemplateSpecification * TemplateSpecification;
	
	RefFlag Flags;
	
};

#endif
