#include <OIL/OilImplementBlock.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilMethodDefinition.h>
#include <OIL/OilTypeRef.h>

#include <algorithm>

#ifndef NULL
	#define NULL nullptr
#endif

OilImplementBlock :: OilImplementBlock ( OilTypeRef * ImplementedType ):
	ImplementedType ( ImplementedType ),
	ForTrait ( NULL ),
	Functions (),
	Methods ()
{
}

OilImplementBlock :: OilImplementBlock ( OilTypeRef * ImplementedType, OilTypeRef * ForTrait ):
	ImplementedType ( ImplementedType ),
	ForTrait ( ForTrait ),
	Functions (),
	Methods ()
{
}

const OilTypeRef * OilImplementBlock :: GetForTrait () const
{
	
	return ForTrait;
	
}

OilTypeRef * OilImplementBlock :: GetForTrait ()
{
	
	return ForTrait;
	
}

bool OilImplementBlock :: IsForTrait () const
{
	
	return ForTrait != NULL;
	
}

OilImplementBlock :: ~OilImplementBlock ()
{
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: iterator FIter = Functions.begin ();
	
	while ( FIter != Functions.end () )
	{
		
		delete FIter -> second;
		
		FIter ++;
		
	}
	
	std :: map <std :: u32string, OilMethodDefinition *> :: iterator MIter = Methods.begin ();
	
	while ( MIter != Methods.end () )
	{
		
		delete MIter -> second;
		
		MIter ++;
		
	}
	
	delete ImplementedType;
	
}

const OilTypeRef * OilImplementBlock :: GetImplementedType () const
{
	
	return ImplementedType;
	
}

OilTypeRef * OilImplementBlock :: GetImplementedType ()
{
	
	return ImplementedType;
	
}

void OilImplementBlock :: AddFunction ( OilFunctionDefinition * Function )
{
	
	Functions [ Function -> GetName () ] = Function;
	
}

uint32_t OilImplementBlock :: GetFunctionCount () const
{
	
	return Functions.size ();
	
}

const OilFunctionDefinition * OilImplementBlock :: GetFunction ( uint32_t Index ) const
{
	
	if ( Index >= Functions.size () )
		return NULL;
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: const_iterator FIter = Functions.begin ();
	
	std :: advance ( FIter, Index );
	
	if ( FIter == Functions.end () )
		return NULL;
	
	return FIter -> second;
	
}

OilFunctionDefinition * OilImplementBlock :: GetFunction ( uint32_t Index )
{
	
	if ( Index >= Functions.size () )
		return NULL;
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: iterator FIter = Functions.begin ();
	
	std :: advance ( FIter, Index );
	
	if ( FIter == Functions.end () )
		return NULL;
	
	return FIter -> second;
	
}

const OilFunctionDefinition * OilImplementBlock :: FindFunction ( const std :: u32string & Name ) const
{
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: const_iterator FIter = Functions.find ( Name );
	
	if ( FIter == Functions.end () )
		return NULL;
	
	return FIter -> second;
	
}

OilFunctionDefinition * OilImplementBlock :: FindFunction ( const std :: u32string & Name )
{
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: iterator FIter = Functions.find ( Name );
	
	if ( FIter == Functions.end () )
		return NULL;
	
	return FIter -> second;
	
}

void OilImplementBlock :: AddMethod ( OilMethodDefinition * Method )
{
	
	Methods [ Method -> GetName () ] = Method;
	
}

uint32_t OilImplementBlock :: GetMethodCount () const
{
	
	return Methods.size ();
	
}

const OilMethodDefinition * OilImplementBlock :: GetMethod ( uint32_t Index ) const
{
	
	if ( Index >= Methods.size () )
		return NULL;
	
	std :: map <std :: u32string, OilMethodDefinition *> :: const_iterator MIter = Methods.begin ();
	
	std :: advance ( MIter, Index );
	
	if ( MIter == Methods.end () )
		return NULL;
	
	return MIter -> second;
	
}

OilMethodDefinition * OilImplementBlock :: GetMethod ( uint32_t Index )
{
	
	if ( Index >= Methods.size () )
		return NULL;
	
	std :: map <std :: u32string, OilMethodDefinition *> :: iterator MIter = Methods.begin ();
	
	std :: advance ( MIter, Index );
	
	if ( MIter == Methods.end () )
		return NULL;
	
	return MIter -> second;
	
}

const OilMethodDefinition * OilImplementBlock :: FindMethod ( const std :: u32string & Name ) const
{
	
	std :: map <std :: u32string, OilMethodDefinition *> :: const_iterator MIter = Methods.find ( Name );
	
	if ( MIter == Methods.end () )
		return NULL;
	
	return MIter -> second;
	
}

OilMethodDefinition * OilImplementBlock :: FindMethod ( const std :: u32string & Name )
{
	
	std :: map <std :: u32string, OilMethodDefinition *> :: iterator MIter = Methods.find ( Name );
	
	if ( MIter == Methods.end () )
		return NULL;
	
	return MIter -> second;
	
}
