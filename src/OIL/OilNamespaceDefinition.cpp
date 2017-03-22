#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilImplicitBindingInitialization.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilImplementBlock.h>

#include <map>
#include <iterator>

OilNamespaceDefinition :: OilNamespaceDefinition ( const std :: u32string & ID ):
	Parent (),
	ID ( ID ),
	SubNamespaces (),
	TypeDefs (),
	FuncDefs (),
	TraitDefs (),
	Bindings (),
	ImplicitIntiailizationBody (),
	UnresImplBlocks ()
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
	
	std :: map <std :: u32string, OilTypeDefinition *> :: iterator FindIterator_SD = TypeDefs.begin ();
	
	while ( FindIterator_SD != TypeDefs.end () )
	{
		
		delete FindIterator_SD -> second;
		
		FindIterator_SD ++;
		
	}
	
	std :: map <std :: u32string, OilFunctionDefinition *> :: iterator FindIterator_FD = FuncDefs.begin ();
	
	while ( FindIterator_FD != FuncDefs.end () )
	{
		
		delete FindIterator_FD -> second;
		
		FindIterator_FD ++;
		
	}
	
	std :: map <std :: u32string, OilTraitDefinition *> :: iterator FindIterator_TD = TraitDefs.begin ();
	
	while ( FindIterator_TD != TraitDefs.end () )
	{
		
		delete FindIterator_TD -> second;
		
		FindIterator_TD ++;
		
	}
	
	std :: map <std :: u32string, OilBindingStatement *> :: iterator FindIterator_B = Bindings.begin ();
	
	while ( FindIterator_B != Bindings.end () )
	{
		
		delete FindIterator_B -> second;
		
		FindIterator_B ++;
		
	}
	
	std :: vector <OilImplementBlock *> :: iterator Iter_UIB = UnresImplBlocks.begin ();
	
	while ( Iter_UIB != UnresImplBlocks.end () )
	{
		
		delete * Iter_UIB;
		
		Iter_UIB ++;
		
	} 
	
}

uint32_t OilNamespaceDefinition :: GetSubNamespaceDefinitionCount () const
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
	NewNamespace -> Parent = this;
	SubNamespaces [ ID ] = NewNamespace;
	
	return NewNamespace;
	
}

OilNamespaceDefinition * OilNamespaceDefinition :: FindNamespaceDefinition ( const std :: u32string & ID )
{
	
	std :: map <std :: u32string, OilNamespaceDefinition *> :: iterator FindIterator = SubNamespaces.find ( ID );
	
	if ( FindIterator != SubNamespaces.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

const OilNamespaceDefinition * OilNamespaceDefinition :: FindNamespaceDefinition ( const std :: u32string & ID ) const
{
	
	std :: map <std :: u32string, OilNamespaceDefinition *> :: const_iterator FindIterator = SubNamespaces.find ( ID );
	
	if ( FindIterator != SubNamespaces.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

void OilNamespaceDefinition :: AddTypeDefinition ( OilTypeDefinition * TypeDef )
{
	
	TypeDefs [ TypeDef -> GetName () ] = TypeDef;
	
	
}

uint32_t OilNamespaceDefinition :: GetTypeDefinitionCount () const
{
	
	return TypeDefs.size ();
	
}

OilTypeDefinition * OilNamespaceDefinition :: GetTypeDefinition ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilTypeDefinition *> :: iterator IndexIter = TypeDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == TypeDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

const OilTypeDefinition * OilNamespaceDefinition :: GetTypeDefinition ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilTypeDefinition *> :: const_iterator IndexIter = TypeDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == TypeDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

OilTypeDefinition * OilNamespaceDefinition :: FindTypeDefinition ( const std :: u32string & ID )
{
	
	std :: map <std :: u32string, OilTypeDefinition *> :: iterator FindIterator = TypeDefs.find ( ID );
	
	if ( FindIterator != TypeDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

const OilTypeDefinition * OilNamespaceDefinition :: FindTypeDefinition ( const std :: u32string & ID ) const
{
	
	std :: map <std :: u32string, OilTypeDefinition *> :: const_iterator FindIterator = TypeDefs.find ( ID );
	
	if ( FindIterator != TypeDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

uint32_t OilNamespaceDefinition :: GetFunctionDefinitionCount () const
{
	
	return FuncDefs.size ();
	
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

void OilNamespaceDefinition :: AddBindingStatement ( OilBindingStatement * BindingStatement )
{
	
	Bindings [ BindingStatement -> GetName () ] = BindingStatement;
	
	if ( BindingStatement -> HasInitializer () )
		ImplicitIntiailizationBody.AddStatement ( new OilImplicitBindingInitialization ( BindingStatement -> GetName () ) );
	
}

uint32_t OilNamespaceDefinition :: GetBindingStatementCount () const
{
	
	return Bindings.size ();
	
}

OilBindingStatement * OilNamespaceDefinition :: GetBindingStatement ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilBindingStatement *> :: iterator IndexIter = Bindings.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == Bindings.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

const OilBindingStatement * OilNamespaceDefinition :: GetBindingStatement ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilBindingStatement *> :: const_iterator IndexIter = Bindings.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == Bindings.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

OilBindingStatement * OilNamespaceDefinition :: FindBindingStatement ( const std :: u32string & ID )
{
	
	std :: map <std :: u32string, OilBindingStatement *> :: iterator FindIterator = Bindings.find ( ID );
	
	if ( FindIterator != Bindings.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

const OilBindingStatement * OilNamespaceDefinition :: FindBindingStatement ( const std :: u32string & ID ) const
{
	
	std :: map <std :: u32string, OilBindingStatement *> :: const_iterator FindIterator = Bindings.find ( ID );
	
	if ( FindIterator != Bindings.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

uint32_t OilNamespaceDefinition :: GetTraitDefinitionCount () const
{
	
	return TraitDefs.size ();
	
}

void OilNamespaceDefinition :: AddTraitDefinition ( OilTraitDefinition * TraitDef )
{
	
	TraitDefs [ TraitDef -> GetName () ] = TraitDef;
	
}

OilTraitDefinition * OilNamespaceDefinition :: GetTraitDefinition ( uint32_t Index )
{
	
	std :: map <std :: u32string, OilTraitDefinition *> :: iterator IndexIter = TraitDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == TraitDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

const OilTraitDefinition * OilNamespaceDefinition :: GetTraitDefinition ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, OilTraitDefinition *> :: const_iterator IndexIter = TraitDefs.begin ();
	
	std :: advance ( IndexIter, Index );
	
	if ( IndexIter == TraitDefs.end () )
		return NULL;
	
	return IndexIter -> second;
	
}

OilTraitDefinition * OilNamespaceDefinition :: FindTraitDefinition ( const std :: u32string & ID )
{
	
	std :: map <std :: u32string, OilTraitDefinition *> :: iterator FindIterator = TraitDefs.find ( ID );
	
	if ( FindIterator != TraitDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

const OilTraitDefinition * OilNamespaceDefinition :: FindTraitDefinition ( const std :: u32string & ID ) const
{
	
	std :: map <std :: u32string, OilTraitDefinition *> :: const_iterator FindIterator = TraitDefs.find ( ID );
	
	if ( FindIterator != TraitDefs.end () )
		return FindIterator -> second;
	
	return NULL;
	
}

OilStatementBody & OilNamespaceDefinition :: GetImplicitInitializationBody ()
{
	
	return ImplicitIntiailizationBody;
	
}

const OilStatementBody & OilNamespaceDefinition :: GetImplicitInitializationBody () const
{
	
	return ImplicitIntiailizationBody;
	
}

const std :: u32string OilNamespaceDefinition :: GetID () const
{
	
	return ID;
	
}

OilNamespaceDefinition * OilNamespaceDefinition :: GetParent ()
{
	
	return Parent;
	
}

const OilNamespaceDefinition * OilNamespaceDefinition :: GetParent () const
{
	
	return Parent;
	
}

uint32_t OilNamespaceDefinition :: GetUnresolvedImplementBlockCount () const
{
	
	return UnresImplBlocks.size ();
	
}

void OilNamespaceDefinition :: AddUnresolvedImplementBlock ( OilImplementBlock * Block )
{
	
	UnresImplBlocks.push_back ( Block );
	
}

OilImplementBlock * OilNamespaceDefinition :: GetUnresolvedImplementBlock ( uint32_t Index )
{
	
	if ( Index >= UnresImplBlocks.size () )
		return NULL;
	
	return UnresImplBlocks [ Index ];
	
}

const OilImplementBlock * OilNamespaceDefinition :: GetUnresolvedImplementBlock ( uint32_t Index ) const
{
	
	if ( Index >= UnresImplBlocks.size () )
		return NULL;
	
	return UnresImplBlocks [ Index ];
	
}

void OilNamespaceDefinition :: RemoveUnresolvedImplementBlock ( uint32_t Index )
{
	
	if ( Index >= UnresImplBlocks.size () )
		return;
	
	UnresImplBlocks.erase ( UnresImplBlocks.begin () + Index );
	
}
