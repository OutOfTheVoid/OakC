#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>
#include <OIL/OilTemplateDefinition.h>

OilStructDefinition :: OilStructDefinition ( const std :: u32string & ID ):
	ID ( ID ),
	TemplateDefinition ( NULL ),
	Bindings ()
{
};

OilStructDefinition :: OilStructDefinition ( const std :: u32string & ID, OilTemplateDefinition * TemplateDefinition ):
	ID ( ID ),
	TemplateDefinition ( TemplateDefinition ),
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
	
	if ( TemplateDefinition != NULL )
		delete TemplateDefinition;
	
}

void OilStructDefinition :: AddBinding ( OilStructBinding * Binding )
{
	
	Bindings [ Binding -> GetName () ] = Binding;
	
}

uint32_t OilStructDefinition :: GetBindingCount () const
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

const OilStructBinding * OilStructDefinition :: GetBinding ( const std :: u32string Name ) const
{
	
	std :: map <std :: u32string, OilStructBinding *> :: const_iterator Iter = Bindings.find ( Name );
	
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

const OilStructBinding * OilStructDefinition :: GetBinding ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilStructBinding *> :: const_iterator Iter = Bindings.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == Bindings.end () )
		return NULL;
	
	return Iter -> second;
	
}

const std :: u32string OilStructDefinition :: GetID () const
{
	
	return ID;
	
}

const OilTemplateDefinition * OilStructDefinition :: GetTemplateDefinition () const
{
	
	return TemplateDefinition;
	
}

OilTemplateDefinition * OilStructDefinition :: GetTemplateDefinition ()
{
	
	return TemplateDefinition;
	
}

bool OilStructDefinition :: IsTemplated () const
{
	
	return TemplateDefinition != NULL;
	
}
