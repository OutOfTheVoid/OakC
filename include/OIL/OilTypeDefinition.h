#ifndef OIL_OILTYPEDEFINITION_H
#define OIL_OILTYPEDEFINITION_H

#include <string>
#include <map>

class OilImplementBlock;
class OilTraitDefinition;
class OilStructDefinition;

class OilTypeDefinition
{
public:
	
	OilTypeDefinition ( const std :: u32string & Name );
	OilTypeDefinition ( OilStructDefinition * Structure );
	
	~OilTypeDefinition ();
	
	const std :: u32string & GetName () const;
	
	void SetStructDefinition ( OilStructDefinition * StructDefinition );
	
	const OilStructDefinition * GetStructDefinition () const;
	OilStructDefinition * GetStructDefinition ();
	
	void SetPrincipalImplementBlock ( OilImplementBlock * Implement );
	
	const OilImplementBlock * GetPrincipalImplementBlock () const;
	OilImplementBlock * GetPrincipalImplementBlock ();
	
	void AddTraitImplementBlock ( const std :: u32string ** AbsoluteNamePath, uint32_t NamePathSize, OilImplementBlock * Implement, bool & NameConflict, bool RedefinitionConflict );
	
	const OilImplementBlock * FindTraitImplementBlock ( const std :: u32string ** AbsoluteNamePath, uint32_t NamePathSize ) const;
	OilImplementBlock * FindTraitImplementBlock ( const std :: u32string ** AbsoluteNamePath, uint32_t NamePathSize );
	
private:
	
	const std :: u32string Name;
	
	OilStructDefinition * StructDefinition;
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
