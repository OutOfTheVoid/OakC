#include <OIL/OilTypeDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTraitDefinition.h>

OilTypeDefinition :: OilTypeDefinition ( OilStructDefinition * Structure ):
	Name ( Structure -> GetID () ),
	StructDefinition ( Structure ),
	PrincipalImplementBlock ( NULL ),
	TraitMap ( NULL )
{
}

OilTypeDefinition :: ~OilTypeDefinition ()
{
	
	if ( StructDefinition != NULL )
		delete StructDefinition;
	
	if ( PrincipalImplementBlock != NULL )
		delete PrincipalImplementBlock;
	
	if ( TraitMap != NULL )
		DeleteTraitMap ( TraitMap );
	
}

const std :: u32string & OilTypeDefinition :: GetName () const
{
	
	return Name;
	
}

void OilTypeDefinition :: DeleteTraitMap ( TraitMapElement * Element )
{
	
	if ( Element -> IsTrait )
	{
		
		if ( Element -> TraitElement.Trait != NULL )
			delete Element -> TraitElement.Trait;
		
		delete Element -> TraitElement.Block;
		
	}
	else
	{
		
		std :: map <std :: u32string, struct TraitMapElement_Struct *> :: iterator Iter = Element -> NameMap -> begin ();
		
		while ( Iter != Element -> NameMap -> end () )
		{
			
			DeleteTraitMap ( Iter -> second );
			
			Iter ++;
			
		}
		
		delete Element -> NameMap;
		
	}
	
	delete Element;
	
}

const OilStructDefinition * OilTypeDefinition :: GetStructDefinition () const
{
	
	return StructDefinition;
	
}

OilStructDefinition * OilTypeDefinition :: GetStructDefinition ()
{
	
	return StructDefinition;
	
}

void OilTypeDefinition :: SetPrincipalImplementBlock ( OilImplementBlock * Implement )
{
	
	this -> PrincipalImplementBlock = Implement;
	
}

const OilImplementBlock * OilTypeDefinition :: GetPrincipalImplementBlock () const
{
	
	return PrincipalImplementBlock;
	
}

OilImplementBlock * OilTypeDefinition :: GetPrincipalImplementBlock ()
{
	
	return PrincipalImplementBlock;
	
}

void OilTypeDefinition :: AddTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, OilImplementBlock * Implement, bool & NameConflict, bool & RedefinitionConflict )
{
	
	if ( TraitMap == NULL )
	{
		
		TraitMap = new TraitMapElement ();
		TraitMap -> IsTrait = false;
		
		TraitMap -> NameMap = new std :: map <std :: u32string, struct TraitMapElement_Struct *> ();
		
	}
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: iterator Iter;
	
	while ( PathIndex + 1 != NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
		{
			
			CurrentElement = ( * CurrentElement -> NameMap ) [ AbsoluteNamePath [ PathIndex ] ] = new TraitMapElement ();
			CurrentElement -> IsTrait  = false;
			CurrentElement -> NameMap = new std :: map <std :: u32string, struct TraitMapElement_Struct *> ();
			
		}
		else
			CurrentElement = Iter -> second;
		
		if ( ! CurrentElement -> IsTrait )
		{
			
			NameConflict = true;
			
			return;
			
		}
		
	}
	
	Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
	
	if ( Iter != CurrentElement -> NameMap -> end () )
	{
		
		RedefinitionConflict = true;
			
		return;
		
	}
	
	CurrentElement = ( * CurrentElement -> NameMap ) [ AbsoluteNamePath [ PathIndex ] ] = new TraitMapElement ();
	
	CurrentElement -> IsTrait = true;
	CurrentElement -> TraitElement.Block = Implement;
	
}

const OilImplementBlock * OilTypeDefinition :: FindTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize ) const
{
	
	if ( TraitMap == NULL )
		return NULL;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: const_iterator Iter;
	
	while ( PathIndex + 1 != NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return NULL;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return NULL;
		
	}
	
	Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return NULL;
	
	if ( ! Iter -> second -> IsTrait )
		return NULL;
	
	return Iter -> second -> TraitElement.Block;
	
}

OilImplementBlock * OilTypeDefinition :: FindTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize )
{
	
	if ( TraitMap == NULL )
		return NULL;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: iterator Iter;
	
	while ( PathIndex + 1 != NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return NULL;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return NULL;
		
	}
	
	Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return NULL;
	
	if ( ! Iter -> second -> IsTrait )
		return NULL;
	
	return Iter -> second -> TraitElement.Block;
	
}
