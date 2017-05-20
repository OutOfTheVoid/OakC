#ifndef OIL_OILTYPENAME_H
#define OIL_OILTYPENAME_H

#include <string>

class OilTemplateSpecification;
class OilTypeDefinition;
class OilTraitDefinition;

class OilTypeRef
{
public:
	
	typedef enum
	{
		
		kReference
		
	} ReferenceMarkerType;
	
	typedef enum
	{
		
		kVoid
		
	} VoidMarkerType;
	
	typedef uint32_t RefFlag;
	
	static const RefFlag kRefFlag_None = 0;
	static const RefFlag kRefFlag_Trait = 1;
	static const RefFlag kRefFlag_Absolute = 2;
	
	OilTypeRef ( const std :: u32string & Name, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( ReferenceMarkerType RMType, OilTypeRef * SubType, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( VoidMarkerType VType );
	~OilTypeRef ();
	
	bool IsDirectType () const;
	bool IsVoid () const;
	
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
	
	bool IsResolved () const;
	bool IsResolvedAsTrait () const;
	bool IsResolvedAsTemplateParam () const;
	
	void SetResolvedTypeDefinition ( OilTypeDefinition * TypeDefinition );
	void SetResolvedTraitDefinition ( OilTraitDefinition * TraitDefinition );
	void SetResolvedTemplateParamName ();
	
	OilTypeDefinition * GetResolvedTypeDefinition () const;
	OilTypeDefinition * GetResolvedTypeDefinition ();
	
	OilTraitDefinition * GetResolvedTraitDefinition () const;
	OilTraitDefinition * GetResolvedTraitDefinition ();
	
	const std :: u32string & GetResolvedTemplateParamName () const;
	
private:
	
	typedef enum
	{
		
		kTypeMode_Reference,
		kTypeMode_Void,
		kTypeMode_Direct
		
	} TypeMode;
	
	TypeMode Mode;
	
	const std :: u32string Name;
	
	std :: u32string * NamespaceNameList;
	const uint32_t NamespaceNameCount;
	
	OilTemplateSpecification * TemplateSpecification;
	
	OilTypeRef * SubType;
	
	RefFlag Flags;
	
	bool ResolvedAsTrait;
	bool ResolvedAsTemplateParam;
	
	union
	{
		
		OilTypeDefinition * ResolvedType;
		OilTraitDefinition * ResolvedTrait;
		
	};
	
};

#endif
