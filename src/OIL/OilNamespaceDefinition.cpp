#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilFunctionDefinition.h>

#include <map>
#include <iterator>

OilNamespaceDefinition :: OilNamespaceDefinition ( const std :: u32string & ID ):
	ID ( ID ),
	SubNamespaces (),
	StructDefs (),
	FuncDefs ()
{
}

OilNamespaceDefinition :: ~OilNamespaceDefinition ()
{
	
	std :: map <std :: u32string, OilNamespaceDefinition *> :: iterator FindIterator_NS = SubNamespaces.begin ();
	
	while ( FindIterator_NS != SubNamespaces.end () )
	{
		
		delete FindIterator_NS -> second;
		
		FindIterator_NS ++;
		
	}
	
	std :: map <std :: u32string, OilStructDefinition *> :: iterator FindIterator_SD = StructDefs.begin ();
	
	while ( FindIterator_SD != StructDefs.end () )
	{
		
		delete FindIterator_SD -> second;
		
		FindIterator_SD ++;
		
	}
	
}

const uint32_t OilNamespaceDefinition :: GetSubNamespaceDefinitionCount () const
{
	
	return SubNamespaces.size ();
	
}

OilNamespaceDefinition * OilNamespaceDefinition :: GetNamespaceDefinition ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilNamespaceDefinition *> :: iterator IndexIter = SubNamespaces.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == SubNamespaces.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

const OilNamespaceDefinition * OilNamespaceDefinition :: GetNamespaceDefinition ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilNamespaceDefinition *> :: const_iterator IndexIter = SubNamespaces.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == SubNamespaces.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

OilNamespaceDefinition * OilNamespaceDefinition :: FindOrCreateNamespaceDefinition ( const std :: u32string & ID )
{
	
	std :: map <std :: u32string, OilNamespaceDefinition *> :: iterator FindIterator = SubNamespaces.find ( ID );
	
	if ( FindIterator != SubNamespaces.end () )
		return FindIterator -> second;
	
	OilNamespaceDefinition * NewNamespace = new OilNamespaceDefinition ( ID );
	SubNamespaces [ ID ] = NewNamespace;
	
	return NewNamespace;
	
}

const OilNamespaceDefinition * OilNamespaceDefinition :: FindNamespaceDefinition ( const std :: u32string & ID ) const
{
	
	std :: map <std :: u32string, OilNamespaceDefinition *> :: const_iterator FindIterator = SubNamespaces.find ( ID );
	
	if ( FindIterator != SubNamespaces.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

void OilNamespaceDefinition :: AddStructDefinition ( OilStructDefinition * StructDef )
{
	
	StructDefs [ StructDef -> GetID () ] = StructDef;
	
}

const uint32_t OilNamespaceDefinition :: GetStructDefinitionCount () const
{
	
	return StructDefs.size ();
	
}

OilStructDefinition * OilNamespaceDefinition :: GetStructDefinition ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilStructDefinition *> :: iterator IndexIter = StructDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == StructDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

const OilStructDefinition * OilNamespaceDefinition :: GetStructDefinition ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilStructDefinition *> :: const_iterator IndexIter = StructDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == StructDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

OilStructDefinition * OilNamespaceDefinition :: FindStructDefinition ( const std :: u32string & ID )
{
	
	std :: map <std :: u32string, OilStructDefinition *> :: iterator FindIterator = StructDefs.find ( ID );
	
	if ( FindIterator != StructDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

const OilStructDefinition * OilNamespaceDefinition :: FindStructDefinition ( const std :: u32string & ID ) const
{
	
	std :: map <std :: u32string, OilStructDefinition *> :: const_iterator FindIterator = StructDefs.find ( ID );
	
	if ( FindIterator != StructDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

void OilNamespaceDefinition :: AddFunctionDefinition ( OilFunctionDefinition * FuncDef )
{
	
	FuncDefs [ FuncDef -> GetName () ] = FuncDef;
	
}

OilFunctionDefinition * OilNamespaceDefinition :: GetFunctionDefinition ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: iterator IndexIter = FuncDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == FuncDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

const OilFunctionDefinition * OilNamespaceDefinition :: GetFunctionDefinition ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: const_iterator IndexIter = FuncDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == FuncDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

OilFunctionDefinition * OilNamespaceDefinition :: FindFunctionDefinition ( const std :: u32string & ID )
{
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: iterator FindIterator = FuncDefs.find ( ID );
	
	if ( FindIterator != FuncDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}


const OilFunctionDefinition * OilNamespaceDefinition :: FindFunctionDefinition ( const std :: u32string & ID ) const
{
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: const_iterator FindIterator = FuncDefs.find ( ID );
	
	if ( FindIterator != FuncDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

const std :: u32string OilNamespaceDefinition :: GetID () const
{
	
	return ID;
	
}