#ifndef OIL_OILTYPENAME_H
#define OIL_OILTYPENAME_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilTemplateSpecification;
class OilTypeDefinition;
class OilTraitDefinition;
class OilTypeAlias;

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
	
	
	OilTypeRef ( const SourceRef & Ref, const OilTypeRef & CopyFrom );
	OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const SourceRef & Ref, const std :: u32string & Name, const std :: u32string * NamespaceNameList, uint32_t NamespaceNameCount, OilTemplateSpecification * OilTemplateSpecification, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const SourceRef & Ref, ReferenceMarkerType RMType, OilTypeRef * SubType, RefFlag Flags = kRefFlag_None );
	OilTypeRef ( const SourceRef & Ref, VoidMarkerType VType );
	~OilTypeRef ();
	
	bool IsDirectType () const;
	bool IsVoid () const;
	
	bool IsNamespaced () const;
	bool IsTemplated () const;
	
	const std :: u32string & GetName () const;
	
	uint32_t GetNamespaceNameCount () const;
	const std :: u32string & GetNamespaceName ( uint32_t Index ) const;
	
	void SetTemplateSpecification ( OilTemplateSpecification * TemplateSpecification );
	
	OilTemplateSpecification * GetTemplateSpecification ();
	const OilTemplateSpecification * GetTemplateSpecification () const;
	
	OilTypeRef * GetSubType ();
	const OilTypeRef * GetSubType () const;
	
	RefFlag GetFlags () const;
	
	bool IsResolved () const;
	bool IsResolvedAsType () const;
	bool IsResolvedAsTrait () const;
	bool IsResolvedAsTemplateParam () const;
	bool IsResolvedAsSelf () const;
	
	void SetResolvedTypeDefinition ( OilTypeDefinition * TypeDefinition );
	void SetResolvedTraitDefinition ( OilTraitDefinition * TraitDefinition );
	void SetResolvedTypeWithTemplateSpec ( OilTypeDefinition * Type, OilTemplateSpecification * Spec );
	void SetResolvedTemplateParamName ();
	void SetResolvedVoid ();
	void SetResolvedAsSelf ();
	
	const OilTypeDefinition * GetResolvedTypeDefinition () const;
	OilTypeDefinition * GetResolvedTypeDefinition ();
	
	const OilTraitDefinition * GetResolvedTraitDefinition () const;
	OilTraitDefinition * GetResolvedTraitDefinition ();
	
	const OilTypeAlias * GetResolvedTypeAlias () const;
	OilTypeAlias * GetResolvedTypeAlias ();
	
	const SourceRef & GetSourceRef () const;
	
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
	bool ResolvedAsSelf;
	
	union
	{
		
		OilTypeDefinition * ResolvedType;
		OilTraitDefinition * ResolvedTrait;
		
	};
	
	SourceRef Ref;
	
};

#endif
