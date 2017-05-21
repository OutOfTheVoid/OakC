#include <OIL/OilImplementBlock.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilMethodDefinition.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateDefinition.h>

#include <algorithm>

#ifndef NULL
	#define NULL nullptr
#endif

OilImplementBlock :: OilImplementBlock ( const SourceRef & Ref, OilTypeRef * ImplementedType ):
	ImplementedType ( ImplementedType ),
	ForTrait ( NULL ),
	WhereDefinition ( NULL ),
	Functions (),
	Methods (),
	Ref ( Ref )
{
}

OilImplementBlock :: OilImplementBlock ( const SourceRef & Ref, OilTypeRef * ImplementedType, OilTemplateDefinition * WhereDefinition ):
	ImplementedType ( ImplementedType ),
	ForTrait ( NULL ),
	WhereDefinition ( WhereDefinition ),
	Functions (),
	Methods (),
	Ref ( Ref )
{
}

OilImplementBlock :: OilImplementBlock ( const SourceRef & Ref, OilTypeRef * ImplementedType, OilTypeRef * ForTrait ):
	ImplementedType ( ImplementedType ),
	ForTrait ( ForTrait ),
	WhereDefinition ( NULL ),
	Functions (),
	Methods (),
	Ref ( Ref )
{
}

OilImplementBlock :: OilImplementBlock ( const SourceRef & Ref, OilTypeRef * ImplementedType, OilTypeRef * ForTrait, OilTemplateDefinition * WhereDefinition ):
	ImplementedType ( ImplementedType ),
	ForTrait ( ForTrait ),
	WhereDefinition ( WhereDefinition ),
	Functions (),
	Methods (),
	Ref ( Ref )
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
	
	if ( ForTrait != NULL )
		delete ForTrait;
	
	if ( WhereDefinition != NULL )
		delete WhereDefinition;
	
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

const OilTemplateDefinition * OilImplementBlock :: GetWhereDefinition () const
{
	
	return WhereDefinition;
	
}

OilTemplateDefinition * OilImplementBlock :: GetWhereDefinition ()
{
	
	return WhereDefinition;
	
}

bool OilImplementBlock :: HasWhereDefinition () const
{
	
	return WhereDefinition != NULL;
	
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

bool OilImplementBlock :: AreBlocksAmbiguous ( const OilImplementBlock & A, const OilImplementBlock & B )
{
		
	if ( ( A.GetImplementedType () -> GetResolvedTypeDefinition () == NULL ) || ( B.GetImplementedType () -> GetResolvedTypeDefinition () == NULL ) )
		return false;
	
	if ( A.GetImplementedType () -> GetResolvedTypeDefinition () != B.GetImplementedType () -> GetResolvedTypeDefinition () )
			return false;
	
	if ( A.IsForTrait () )
	{
		
		if ( ! B.IsForTrait () )
			return false;
		
		if ( ( A.GetForTrait () -> GetResolvedTraitDefinition () == NULL ) || ( B.GetForTrait () -> GetResolvedTraitDefinition () == NULL ) )
			return false;
		
		if ( A.GetForTrait () -> GetResolvedTraitDefinition () != B.GetForTrait () -> GetResolvedTraitDefinition () )
			return false;
		
	}
	else
	{
		
		if ( B.IsForTrait () )
			return false;
		
	}
	
	if ( A.HasWhereDefinition () )
	{
		
		if ( B.HasWhereDefinition () )
		{
			
			//const OilTemplateDefinition * WhereA = A.GetWhereDefinition ();
			//const OilTemplateDefinition * WhereB = B.GetWhereDefinition ();
			
			//if ( WhereA )
			
		}
		
	}
	
	return true;
	
}

const SourceRef & OilImplementBlock :: GetSourceRef () const
{
	
	return Ref;
	
}
