#include <OIL/OilEnum.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateDefinition.h>

const std :: u32string OilEnum :: NullStringRef;
const SourceRef OilEnum :: NullSourceRef;

OilEnum :: OilEnum ( const SourceRef & Ref, const std :: u32string & Name ):
	Name ( Name ),
	Template ( NULL ),
	Branches (),
	Ref ( Ref ),
	ParentNamespace ( NULL )
{
}

OilEnum :: OilEnum ( const SourceRef & Ref, const std :: u32string & Name, OilTemplateDefinition * Template ):
	Name ( Name ),
	Template ( Template ),
	Branches (),
	Ref ( Ref ),
	ParentNamespace ( NULL )
{
}

OilEnum :: ~OilEnum ()
{
	
	if ( Template != NULL )
		delete Template;
	
	std :: map <std :: u32string, BranchData> :: iterator BranchIter = Branches.begin ();
	
	while ( BranchIter != Branches.end () )
	{
		
		if ( BranchIter -> second.DataType != NULL )
			delete BranchIter -> second.DataType;
		
		BranchIter ++;
		
	}
	
}

const std :: u32string & OilEnum :: GetName () const
{
	
	return Name;
	
}

bool OilEnum :: IsTemplated () const
{
	
	return Template != NULL;
	
}

OilTemplateDefinition * OilEnum :: GetTemplateDefinition ()
{
	
	return Template;
	
}

const OilTemplateDefinition * OilEnum :: GetTemplateDefinition () const
{
	
	return Template;
	
}

uint32_t OilEnum :: GetBranchCount () const
{
	
	return Branches.size ();
	
}

void OilEnum :: AddBranch ( const SourceRef & Ref, const std :: u32string & BranchName )
{
	
	Branches [ BranchName ] = { NULL, Ref };
	
}

void OilEnum :: AddDataBranch ( const SourceRef & Ref, const std :: u32string & BranchName, OilTypeRef * DataType )
{
	
	Branches [ BranchName ] = { DataType, Ref };
	
}

const std :: u32string & OilEnum :: GetBranchName ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, BranchData> :: const_iterator BranchIter = Branches.begin ();
	
	std :: advance ( BranchIter, Index );
	
	if ( BranchIter == Branches.end () )
		return NullStringRef;
	
	return BranchIter -> first;
	
}

const SourceRef & OilEnum :: GetBranchSourceRef ( const std :: u32string & Branch ) const
{
	
	std :: map <std :: u32string, BranchData> :: const_iterator BranchIter = Branches.find ( Branch );
	
	if ( BranchIter == Branches.end () )
		return NullSourceRef;
	
	return BranchIter -> second.Ref;
	
}

const SourceRef & OilEnum :: GetBranchSourceRef ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, BranchData> :: const_iterator BranchIter = Branches.begin ();
	
	std :: advance ( BranchIter, Index );
	
	if ( BranchIter == Branches.end () )
		return NullSourceRef;
	
	return BranchIter -> second.Ref;
	
}

bool OilEnum :: HasBranch ( const std :: u32string & Name ) const
{
	
	return Branches.find ( Name ) != Branches.end ();
	
}

bool OilEnum :: HasBranch ( uint32_t Index ) const
{
	
	return Branches.size () > Index;
	
}

bool OilEnum :: BranchHasData ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, BranchData> :: const_iterator BranchIter = Branches.begin ();
	
	std :: advance ( BranchIter, Index );
	
	if ( BranchIter == Branches.end () )
		return false;
	
	return BranchIter -> second.DataType != NULL;
	
}

const OilTypeRef * OilEnum :: GetBranchDataType ( uint32_t Index ) const
{
	
	std :: map <std :: u32string, BranchData> :: const_iterator BranchIter = Branches.begin ();
	
	std :: advance ( BranchIter, Index );
	
	if ( BranchIter == Branches.end () )
		return NULL;
	
	return BranchIter -> second.DataType;
	
}

OilTypeRef * OilEnum :: GetBranchDataType ( uint32_t Index )
{
	
	std :: map <std :: u32string, BranchData> :: iterator BranchIter = Branches.begin ();
	
	std :: advance ( BranchIter, Index );
	
	if ( BranchIter == Branches.end () )
		return NULL;
	
	return BranchIter -> second.DataType;
	
}

const OilTypeRef * OilEnum :: GetBranchDataType ( const std :: u32string & Branch ) const
{
	
	std :: map <std :: u32string, BranchData> :: const_iterator BranchIter = Branches.find ( Branch );
	
	if ( BranchIter == Branches.end () )
		return NULL;
	
	return BranchIter -> second.DataType;
	
}

OilTypeRef * OilEnum :: GetBranchDataType ( const std :: u32string & Branch )
{
	
	std :: map <std :: u32string, BranchData> :: iterator BranchIter = Branches.find ( Branch );
	
	if ( BranchIter == Branches.end () )
		return NULL;
	
	return BranchIter -> second.DataType;
	
}

const SourceRef & OilEnum :: GetSourceRef () const
{
	
	return Ref;
	
}

const OilNamespaceDefinition * OilEnum :: GetParentNamespace () const
{
	
	return ParentNamespace;
	
}

OilNamespaceDefinition * OilEnum :: GetParentNamespace ()
{
	
	return ParentNamespace;
	
}
