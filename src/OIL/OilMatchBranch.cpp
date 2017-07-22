#include <OIL/OilMatchBranch.h>
#include <OIL/IOilPrimary.h>
#include <OIL/OilStatementBody.h>
#include <OIL/OilAllusion.h>
#include <OIL/OilStructDestructure.h>

#ifndef NULL
	#define NULL nullptr;
#endif

OilMatchBranch :: OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body ):
	Type ( kMatchType_Other ),
	AllusionValueName ( U"" ),
	MatchDestructure ( NULL ),
	Body ( Body ),
	Ref ( Ref )
{
}

OilMatchBranch :: OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, IOilPrimary * MatchConstantPrimary ):
	Type ( kMatchType_Constant ),
	MatchConstantPrimary ( MatchConstantPrimary ),
	AllusionValueName ( U"" ),
	MatchDestructure ( NULL ),
	Body ( Body ),
	Ref ( Ref )
{
}

OilMatchBranch :: OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, OilAllusion * MatchAllusion ):
	Type ( kMatchType_Allusion ),
	MatchAllusion ( MatchAllusion ),
	AllusionValueName ( U"" ),
	MatchDestructure ( NULL ),
	Body ( Body ),
	Ref ( Ref )
{
}

OilMatchBranch :: OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, OilAllusion * MatchAllusion, const std :: u32string & AllusionValueName ):
	Type ( kMatchType_AllusionValue ),
	MatchAllusion ( MatchAllusion ),
	AllusionValueName ( AllusionValueName ),
	MatchDestructure ( NULL ),
	Body ( Body ),
	Ref ( Ref )
{
}


OilMatchBranch :: OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, OilAllusion * MatchAllusion, OilStructDestructure * Destructure ):
	Type ( kMatchType_Destructure ),
	MatchAllusion ( MatchAllusion ),
	AllusionValueName ( U"" ),
	MatchDestructure ( Destructure ),
	Body ( Body ),
	Ref ( Ref )
{
}

OilMatchBranch :: ~OilMatchBranch ()
{
	
	delete Body;
	
	switch ( Type )
	{
		
		case kMatchType_Constant:
			delete MatchConstantPrimary;
			break;
			
		case kMatchType_AllusionValue:
		case kMatchType_Allusion:
		case kMatchType_Destructure:
			delete MatchAllusion;
			break;
			
		default: 
			break;
		
	}
	
	if ( Type == kMatchType_Destructure )
		delete MatchDestructure;
	
}

OilMatchBranch :: MatchType OilMatchBranch :: GetMatchType () const
{
	
	return Type;
	
}

const OilStatementBody * OilMatchBranch :: GetStatementBody () const
{
	
	return Body;
	
}

OilStatementBody * OilMatchBranch :: GetStatementBody ()
{
	
	return Body;
	
}

const IOilPrimary * OilMatchBranch :: GetConstantPrimary () const
{
	
	return ( Type == kMatchType_Constant ) ? MatchConstantPrimary : NULL;
	
}

IOilPrimary * OilMatchBranch :: GetConstantPrimary ()
{
	
	return ( Type == kMatchType_Constant ) ? MatchConstantPrimary : NULL;
	
}

const OilAllusion * OilMatchBranch :: GetMatchAllusion () const
{
	
	return ( ( Type == kMatchType_Allusion ) || ( Type == kMatchType_Destructure ) || ( Type == kMatchType_AllusionValue ) ) ? MatchAllusion : NULL;
	
}

OilAllusion * OilMatchBranch :: GetMatchAllusion ()
{
	
	return ( ( Type == kMatchType_Allusion ) || ( Type == kMatchType_Destructure ) || ( Type == kMatchType_AllusionValue ) ) ? MatchAllusion : NULL;
	
}

const OilStructDestructure * OilMatchBranch :: GetMatchDestructure () const
{
	
	return ( Type == kMatchType_Destructure ) ? MatchDestructure : NULL;
	
}

OilStructDestructure * OilMatchBranch :: GetMatchDestructure ()
{
	
	return ( Type == kMatchType_Destructure ) ? MatchDestructure : NULL;
	
}

const std :: u32string & OilMatchBranch :: GetAllusionValueName () const
{
	
	return AllusionValueName;
	
}
