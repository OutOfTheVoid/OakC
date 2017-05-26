#include <OIL/OilTypeDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilBuiltinStructDefinition.h>

#include <iterator>

OilTypeDefinition :: OilTypeDefinition ( const SourceRef & Ref, OilStructDefinition * Structure, bool IsBuiltin ):
	Name ( Structure -> GetID () ),
	IsBuiltin ( IsBuiltin ),
	IsStructBuiltin ( false ),
	StructDefinition ( Structure ),
	PrincipalImplementBlocks (),
	TraitMap ( NULL ),
	Ref ( Ref )
{
}

OilTypeDefinition :: OilTypeDefinition ( const SourceRef & Ref, OilBuiltinStructDefinition * Structure, bool IsBuiltin ):
	Name ( Structure -> GetName () ),
	IsBuiltin ( IsBuiltin ),
	IsStructBuiltin ( true ),
	BuiltinStructDefinition ( Structure ),
	PrincipalImplementBlocks (),
	TraitMap ( NULL ),
	Ref ( Ref )
{
}

OilTypeDefinition :: ~OilTypeDefinition ()
{
	
	if ( IsBuiltin )
		delete BuiltinStructDefinition;
	else
		delete StructDefinition;
	
	for ( uint32_t I = 0; I < PrincipalImplementBlocks.size (); I ++ )
		delete PrincipalImplementBlocks [ I ];
	
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
		
		for ( uint32_t I = 0; I < Element -> TraitElement.Blocks -> size (); I ++ )
			delete ( * Element -> TraitElement.Blocks ) [ I ];
		
		delete Element -> TraitElement.Blocks;
		
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

void OilTypeDefinition :: AddPrincipalImplementBlock ( OilImplementBlock * Implement )
{
	
	PrincipalImplementBlocks.push_back ( Implement );
	
}

void OilTypeDefinition :: GetPrincipalImplementBlocks ( std :: vector <const OilImplementBlock *> & Blocks ) const
{
	
	for ( uint32_t I = 0; I < PrincipalImplementBlocks.size (); I ++ )
		Blocks.push_back ( PrincipalImplementBlocks [ I ] );
	
}

void OilTypeDefinition :: GetPrincipalImplementBlocks ( std :: vector <OilImplementBlock *> & Blocks )
{
	
	for ( uint32_t I = 0; I < PrincipalImplementBlocks.size (); I ++ )
		Blocks.push_back ( PrincipalImplementBlocks [ I ] );
	
}

void OilTypeDefinition :: AddTraitImplementBlock ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, OilImplementBlock * Implement, bool & NameConflict )
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
		
		Iter -> second -> TraitElement.Blocks -> push_back ( Implement );
		
		return;
		
	}
	
	TraitMapElement * New = new TraitMapElement ();
	New -> IsTrait = true;
	New -> TraitElement.Blocks = new std :: vector <OilImplementBlock *> ();
	New -> TraitElement.Blocks -> push_back ( Implement );
	
	( * CurrentElement -> NameMap ) [ AbsoluteNamePath [ PathIndex ] ] = New;
	
}

void OilTypeDefinition :: FindTraitImplementBlocks ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, std :: vector <const OilImplementBlock *> & Out ) const
{
	
	if ( TraitMap == NULL )
		return;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: const_iterator Iter;
	
	while ( PathIndex + 1 < NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return;
		
		PathIndex ++;
		
	}
	
	Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return;
	
	if ( ! Iter -> second -> IsTrait )
		return;
	
	
	for ( uint32_t I = 0; I < Iter -> second -> TraitElement.Blocks -> size (); I ++ )
		Out.push_back ( ( * Iter -> second -> TraitElement.Blocks ) [ I ] );
	
}

void OilTypeDefinition :: FindTraitImplementBlocks ( const std :: u32string * AbsoluteNamePath, uint32_t NamePathSize, std :: vector <OilImplementBlock *> & Out )
{
	
	if ( TraitMap == NULL )
		return;
	
	TraitMapElement * CurrentElement = TraitMap;
	
	uint32_t PathIndex = 0;
	
	std :: map <std :: u32string, struct TraitMapElement_Struct *> :: const_iterator Iter;
	
	while ( PathIndex + 1 < NamePathSize )
	{
		
		Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
		
		if ( Iter == CurrentElement -> NameMap -> end () )
			return;
		
		CurrentElement = Iter -> second;
		
		if ( CurrentElement -> IsTrait )
			return;
		
		PathIndex ++;
		
	}
	
	Iter = CurrentElement -> NameMap -> find ( AbsoluteNamePath [ PathIndex ] );
	
	if ( Iter == CurrentElement -> NameMap -> end () )
		return;
	
	if ( ! Iter -> second -> IsTrait )
		return;
	
	
	for ( uint32_t I = 0; I < Iter -> second -> TraitElement.Blocks -> size (); I ++ )
		Out.push_back ( ( * Iter -> second -> TraitElement.Blocks ) [ I ] );
	
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

const SourceRef & OilTypeDefinition :: GetSourceRef () const
{
	
	return Ref;
	
}

// TEMPORARY
#include <Logging/Logging.h>
#include <Encoding/CodeConversion.h>

void OilTypeDefinition :: GetAllImplementBlocks ( std :: vector <OilImplementBlock *> & Out )
{
	
	for ( uint32_t I = 0; I < PrincipalImplementBlocks.size (); I ++ )
		Out.push_back ( PrincipalImplementBlocks [ I ] );
	
	std :: vector <uint32_t> IndexStack;
	std :: vector <TraitMapElement *> ElementStack;
	IndexStack.push_back ( 0 );
	
	if ( TraitMap == NULL )
		return;
	
	TraitMapElement * Element = TraitMap;
	
	if ( Element -> IsTrait )
	{
		
		for ( uint32_t I = 0; I < Element -> TraitElement.Blocks -> size (); I ++ )
			Out.push_back ( ( * Element -> TraitElement.Blocks ) [ I ] );
		
		return;
		
	}
	
	do
	{
		
		std :: map <std :: u32string, struct TraitMapElement_Struct *> :: iterator Iter = Element -> NameMap -> begin ();
		
		std :: advance ( Iter, IndexStack [ IndexStack.size () - 1 ] );
		
		if ( Iter == Element -> NameMap -> end () )
		{
			
			IndexStack.pop_back ();
			ElementStack.pop_back ();
			
			Element = ElementStack [ ElementStack.size () - 1 ];
			
			continue;
			
		}
		
		if ( Iter -> second -> IsTrait )
		{
			
			for ( uint32_t I = 0; I < Iter -> second -> TraitElement.Blocks -> size (); I ++ )
				Out.push_back ( ( * Iter -> second -> TraitElement.Blocks ) [ I ] );
			
			IndexStack [ IndexStack.size () - 1 ] ++;
			
		}
		else
		{
			
			IndexStack [ IndexStack.size () - 1 ] ++;
			IndexStack.push_back ( 0 );
			ElementStack.push_back ( Element );
			Element = Iter -> second;
			
		}
		
	}
	while ( ElementStack.size () != 0 );
	
}

void OilTypeDefinition :: GetAllImplementBlocks ( std :: vector <const OilImplementBlock *> & Out ) const
{
	
	for ( uint32_t I = 0; I < PrincipalImplementBlocks.size (); I ++ )
		Out.push_back ( PrincipalImplementBlocks [ I ] );
	
	std :: vector <uint32_t> IndexStack;
	std :: vector <TraitMapElement *> ElementStack;
	IndexStack.push_back ( 0 );
	
	if ( TraitMap == NULL )
		return;
	
	TraitMapElement * Element = TraitMap;
	
	if ( Element -> IsTrait )
	{
		
		for ( uint32_t I = 0; I < Element -> TraitElement.Blocks -> size (); I ++ )
			Out.push_back ( ( * Element -> TraitElement.Blocks ) [ I ] );
		
		return;
		
	}
	
	while ( IndexStack.size () != 0 )
	{
		
		std :: map <std :: u32string, struct TraitMapElement_Struct *> :: iterator Iter = Element -> NameMap -> begin ();
		
		std :: advance ( Iter, IndexStack [ IndexStack.size () - 1 ] );
		
		if ( Iter == Element -> NameMap -> end () )
		{
			
			IndexStack.pop_back ();
			
			Element = ElementStack [ ElementStack.size () - 1 ];
			ElementStack.pop_back ();
			
			continue;
			
		}
		
		if ( Iter -> second -> IsTrait )
		{
			
			for ( uint32_t I = 0; I < Iter -> second -> TraitElement.Blocks -> size (); I ++ )
				Out.push_back ( ( * Iter -> second -> TraitElement.Blocks ) [ I ] );
			
			IndexStack [ IndexStack.size () - 1 ] ++;
			
		}
		else
		{
			
			IndexStack [ IndexStack.size () - 1 ] ++;
			IndexStack.push_back ( 0 );
			ElementStack.push_back ( Element );
			Element = Iter -> second;
			
		}
		
	}
	
}
