#ifndef OIL_OILTYPEDEFINITION_H
#define OIL_OILTYPEDEFINITION_H

#include <string>
#include <map>
#include <vector>

#include <Tokenization/SourceRef.h>

class OilImplementBlock;
class OilTraitDefinition;
class OilStructDefinition;
class OilBuiltinStructDefinition;
class OilTemplateDefinition;
class OilNamespaceDefinition;
class OilEnum;

class OilTypeDefinition
{
public:
	
	OilTypeDefinition ( const SourceRef & Ref, OilStructDefinition * Structure, bool IsBuiltin = false );
	OilTypeDefinition ( const SourceRef & Ref, OilEnum * Enum, bool IsBuiltin = false );
	OilTypeDefinition ( const SourceRef & Ref, OilBuiltinStructDefinition * BuiltinStructure, bool IsBuiltin = false );
	
	~OilTypeDefinition ();
	
	const std :: u32string & GetName () const;
	
	bool IsBuiltinType () const;
	bool IsEnumType () const;
	
	bool IsBuiltinStructure () const;
	
	bool IsTemplated () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	const OilBuiltinStructDefinition * GetBuiltinStructDefinition () const;
	OilBuiltinStructDefinition * GetBuiltinStructDefinition ();
	
	const OilStructDefinition * GetStructDefinition () const;
	OilStructDefinition * GetStructDefinition ();
	
	const OilEnum * GetEnum () const;
	OilEnum * GetEnum ();
	
	void AddPrincipalImplementBlock ( OilImplementBlock * Implement );
	
	void GetPrincipalImplementBlocks ( std :: vector <const OilImplementBlock *> & Out ) const;
	void GetPrincipalImplementBlocks ( std :: vector <OilImplementBlock *> & Out );
	
	void AddTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, OilImplementBlock * Implement, bool & NameConflict );
	
	void FindTraitImplementBlocks ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, std :: vector <const OilImplementBlock *> & Out ) const;
	void FindTraitImplementBlocks ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, std :: vector <OilImplementBlock *> & Out );
	
	uint32_t GetNamespaceCountAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize ) const;
	const std :: u32string GetImplementNamespaceAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, uint32_t Index ) const;
	
	void GetAllImplementBlocks ( std :: vector <OilImplementBlock *> & Out );
	void GetAllImplementBlocks ( std :: vector <const OilImplementBlock *> & Out ) const;
	
	const SourceRef & GetSourceRef () const;
	
	const OilNamespaceDefinition * GetParentNamespace () const;
	OilNamespaceDefinition * GetParentNamespace ();
	
private:
	
	friend class OilNamespaceDefinition;
	
	static const std :: u32string NullString;
	
	const std :: u32string Name;
	
	bool IsBuiltin;
	
	bool IsStructBuiltin;
	bool IsEnum;
	
	union
	{
		
		OilStructDefinition * StructDefinition;
		OilBuiltinStructDefinition * BuiltinStructDefinition;
		OilEnum * Enum;
		
	};
		
	std :: vector <OilImplementBlock *> PrincipalImplementBlocks;
	
	typedef struct
	{
		
		OilTraitDefinition * Trait;
		std :: vector <OilImplementBlock *> * Blocks;
		
	} ImplementedTraitElement;
	
	typedef struct TraitMapElement_Struct
	{
		
		bool IsTrait;
		
		union
		{
			
			std :: map <std :: u32string, struct TraitMapElement_Struct *> * NameMap;
			ImplementedTraitElement TraitElement;
			
		};
			
	} TraitMapElement;
	
	static void DeleteTraitMap ( TraitMapElement * Element );
	
	TraitMapElement * TraitMap;
	
	SourceRef Ref;
	
	OilNamespaceDefinition * ParentNamespace;
	
};

#endif
