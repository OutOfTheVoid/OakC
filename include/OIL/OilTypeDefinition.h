#ifndef OIL_OILTYPEDEFINITION_H
#define OIL_OILTYPEDEFINITION_H

#include <string>
#include <map>

class OilImplementBlock;
class OilTraitDefinition;
class OilStructDefinition;
class OilBuiltinStructDefinition;

class OilTypeDefinition
{
public:
	
	OilTypeDefinition ( OilStructDefinition * Structure, bool IsBuiltin = false );
	OilTypeDefinition ( OilBuiltinStructDefinition * BuiltinStructure, bool IsBuiltin = false );
	
	~OilTypeDefinition ();
	
	const std :: u32string & GetName () const;
	
	bool IsBuiltinType () const;
	
	bool IsBuiltinStructure () const;
	
	const OilBuiltinStructDefinition * GetBuiltinStructDefinition () const;
	OilBuiltinStructDefinition * GetBuiltinStructDefinition ();
	
	const OilStructDefinition * GetStructDefinition () const;
	OilStructDefinition * GetStructDefinition ();
	
	void SetPrincipalImplementBlock ( OilImplementBlock * Implement );
	
	const OilImplementBlock * GetPrincipalImplementBlock () const;
	OilImplementBlock * GetPrincipalImplementBlock ();
	
	void AddTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, OilImplementBlock * Implement, bool & NameConflict, bool & RedefinitionConflict );
	
	const OilImplementBlock * FindTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize ) const;
	OilImplementBlock * FindTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize );
	
	uint32_t GetNamespaceCountAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize ) const;
	const std :: u32string GetImplementNamespaceAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, uint32_t Index ) const;
	
	const OilImplementBlock * GetImplementBlockAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, uint32_t Index ) const;
	OilImplementBlock * GetImplementBlockAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, uint32_t Index );
	
private:
	
	static const std :: u32string NullString;
	
	const std :: u32string Name;
	
	bool IsBuiltin;
	
	bool IsStructBuiltin;
	
	union
	{
		
		OilStructDefinition * StructDefinition;
		OilBuiltinStructDefinition * BuiltinStructDefinition;
		
	};
		
	OilImplementBlock * PrincipalImplementBlock;
	
	typedef struct
	{
		
		OilTraitDefinition * Trait;
		OilImplementBlock * Block;
		
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
	
};

#endif
