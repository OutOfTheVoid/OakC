#ifndef OIL_OILTYPENAME_H
#define OIL_OILTYPENAME_H

#include <string>

class OilTemplateSpecification;

class OilTypeRef
{
public:
	
	typedef enum
	{
		
		kReference
		
	} ReferenceMarkerType;
	
	typedef enum
	{
		
		kPointer
		
	} PointerMarkerType;
	
	typedef uint32_t RefFlag;
	
	static const RefFlag kRefFlag_None = 0;
	static const RefFlag kRefFlag_Trait = 1;
	
	OilTypeRef ( const std :: u32string & Name, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( ReferenceMarkerType RMType, OilTypeRef * SubType, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( PointerMarkerType PTType, OilTypeRef * SubType, RefFlag Flags = kRefFlag_None );
	~OilTypeRef ();
	
	bool IsDirectType () const;
	bool IsReference () const;
	
	bool IsNamespaced () const;
	bool IsTemplated () const;
	
	const std :: u32string & GetName () const;
	
	uint32_t GetNamespaceNameCount () const;
	const std :: u32string & GetNamespaceName ( uint32_t Index ) const;
	
	OilTemplateSpecification * GetTemplateSpecification ();
	const OilTemplateSpecification * GetTemplateSpecification () const;
	
	OilTypeRef * GetSubType ();
	const OilTypeRef * GetSubType () const;
	
	RefFlag GetFlags () const;
	
private:
	
	typedef enum
	{
		
		kTypeMode_Pointer,
		kTypeMode_Reference,
		kTypeMode_Direct
		
	} TypeMode;
	
	TypeMode Mode;
	
	const std :: u32string Name;
	
	std :: u32string * NamespaceNameList;
	const uint32_t NamespaceNameCount;
	
	OilTemplateSpecification * TemplateSpecification;
	
	OilTypeRef * SubType;
	
	RefFlag Flags;
	
};

#endif
