#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>

OilStructDefinition :: OilStructDefinition ( const std :: u32string & ID ):
	ID ( ID ),
	Bindings ()
{
};

OilStructDefinition :: ~OilStructDefinition ()
{
	
	std :: map <std :: u32string, OilStructBinding *> :: iterator Iter = Bindings.begin ();
	
	while ( Iter != Bindings.end () )
	{
		
		delete Iter -> second;
		
		Iter ++;
		
	}
	
}

void OilStructDefinition :: AddBinding ( OilStructBinding * Binding )
{
	
	Bindings [ Binding -> GetName () ] = Binding;
	
}

uint32_t OilStructDefinition :: GetBindingCount ()
{
	
	return Bindings.size ();
	
}

OilStructBinding * OilStructDefinition :: GetBinding ( const std :: u32string Name )
{
	
	std :: map <std :: u32string, OilStructBinding *> :: iterator Iter = Bindings.find ( Name );
	
	if ( Iter == Bindings.end () )
		return NULL;
	
	return Iter -> second;
	
}

OilStructBinding * OilStructDefinition :: GetBinding ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilStructBinding *> :: iterator Iter = Bindings.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == Bindings.end () )
		return NULL;
	
	return Iter -> second;
	
}

const std :: u32string OilStructDefinition :: GetID () const
{
	
	return ID;
	
}
