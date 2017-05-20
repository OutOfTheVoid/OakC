#include <OIL/OilTypeDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilBuiltinStructDefinition.h>

OilTypeDefinition :: OilTypeDefinition ( OilStructDefinition * Structure, bool IsBuiltin ):
	Name ( Structure -> GetID () ),
	IsBuiltin ( IsBuiltin ),
	IsStructBuiltin ( false ),
	StructDefinition ( Structure ),
	PrincipalImplementBlock ( NULL ),
	TraitMap ( NULL )
{
}

OilTypeDefinition :: OilTypeDefinition ( OilBuiltinStructDefinition * Structure, bool IsBuiltin ):
	Name ( Structure -> GetName () ),
	IsBuiltin ( IsBuiltin ),
	IsStructBuiltin ( true ),
	BuiltinStructDefinition ( Structure ),
	PrincipalImplementBlock ( NULL ),
	TraitMap ( NULL )
{
}

OilTypeDefinition :: ~OilTypeDefinition ()
{
	
	if ( IsBuiltin )
		delete BuiltinStructDefinition;
	else
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

bool OilTypeDefinition :: IsBuiltinType () const
{
	
	return IsBuiltin;
	
}

bool OilTypeDefinition :: IsBuiltinStructure () const
{
	
	return IsStructBuiltin;
	
}

const OilBuiltinStructDefinition * OilTypeDefinition :: GetBuiltinStructDefinition () const
{
	
	return BuiltinStructDefinition;
	
}

OilBuiltinStructDefinition * OilTypeDefinition :: GetBuiltinStructDefinition ()
{
	
	return BuiltinStructDefinition;
	
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
		TraitMap -> NameMap = new std :: map <std :: u32string, TraitMapElement *> ();
		
	}
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, TraitMapElement *> :: iterator Iter;
	
	while ( PathIndex + 1 < NamePathSize )
	{
		
		if ( CurrentElement -> IsTrait )
		{
			
			NameConflict = true;
			
			return;
			
		}
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
		{
			
			TraitMapElement * New = new TraitMapElement ();
			New -> IsTrait  = false;
			New -> NameMap = new std :: map <std :: u32string, TraitMapElement *> ();
			
			( * CurrentElement -> NameMap ) [ AbsoluteNamePath [ PathIndex ] ] = New;
			CurrentElement = New;
			
		}
		else
			CurrentElement = Iter -> second;
		
		PathIndex ++;
		
	}
	
	Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
	
	if ( Iter != CurrentElement -> NameMap -> end () )
	{
		
		RedefinitionConflict = true;
		
		return;
		
	}
	
	TraitMapElement * New = new TraitMapElement ();
	New -> IsTrait = true;
	New -> TraitElement.Block = Implement;
	
	( * CurrentElement -> NameMap ) [ AbsoluteNamePath [ PathIndex ] ] = New;
	
}

const OilImplementBlock * OilTypeDefinition :: FindTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize ) const
{
	
	if ( TraitMap == NULL )
		return NULL;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: const_iterator Iter;
	
	while ( PathIndex + 1 < NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return NULL;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return NULL;
		
		PathIndex ++;
		
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
		
		PathIndex ++;
		
	}
	
	Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return NULL;
	
	if ( ! Iter -> second -> IsTrait )
		return NULL;
	
	return Iter -> second -> TraitElement.Block;
	
}

const std :: u32string OilTypeDefinition :: NullString ( U"" );

uint32_t OilTypeDefinition :: GetNamespaceCountAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize ) const
{
	
	if ( TraitMap == NULL )
		return 0;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: const_iterator Iter;
	
	while ( PathIndex != NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return 0;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return 0;
		
		PathIndex ++;
		
	}
	
	return CurrentElement -> NameMap -> size ();
	
}

const std :: u32string OilTypeDefinition :: GetImplementNamespaceAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, uint32_t Index ) const
{
	
	if ( TraitMap == NULL )
		return NullString;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: const_iterator Iter;
	
	while ( PathIndex != NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return NullString;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return NullString;
		
		PathIndex ++;
		
	}
	
	Iter = CurrentElement -> NameMap -> begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return NullString;
	
	return Iter -> first;
	
}

const OilImplementBlock * OilTypeDefinition :: GetImplementBlockAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, uint32_t Index ) const
{
	
	if ( TraitMap == NULL )
		return NULL;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: const_iterator Iter;
	
	while ( PathIndex != NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return NULL;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return NULL;
		
		PathIndex ++;
		
	}
	
	Iter = CurrentElement -> NameMap -> begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return NULL;
	
	if ( ! Iter -> second -> IsTrait )
		return NULL;
	
	return Iter -> second -> TraitElement.Block;
	
}

OilImplementBlock * OilTypeDefinition :: GetImplementBlockAt ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, uint32_t Index )
{
	
	if ( TraitMap == NULL )
		return NULL;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: iterator Iter;
	
	while ( PathIndex != NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return NULL;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return NULL;
		
		PathIndex ++;
		
	}
	
	Iter = CurrentElement -> NameMap -> begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return NULL;
	
	if ( ! Iter -> second -> IsTrait )
		return NULL;
	
	return Iter -> second -> TraitElement.Block;
	
}

bool OilTypeDefinition :: IsTemplated () const
{
	
	return IsStructBuiltin ? BuiltinStructDefinition -> IsTemplated () : StructDefinition -> IsTemplated ();
	
}

const OilTemplateDefinition * OilTypeDefinition :: GetTemplateDefinition () const
{
	
	return IsStructBuiltin ? BuiltinStructDefinition -> GetTemplateDefinition () : StructDefinition -> GetTemplateDefinition ();
	
}

OilTemplateDefinition * OilTypeDefinition :: GetTemplateDefinition ()
{
	
	return IsStructBuiltin ? BuiltinStructDefinition -> GetTemplateDefinition () : StructDefinition -> GetTemplateDefinition ();
	
}
