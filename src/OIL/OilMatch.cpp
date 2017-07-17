#include <OIL/OilMatch.h>
#include <OIL/OilExpression.h>

OilMatch :: OilMatch ( const SourceRef & Ref, OilExpression * MatcheeExpression ):
	MatcheeExpression ( MatcheeExpression ),
	Branches (),
	Ref ( Ref )
{	
}

OilMatch :: ~OilMatch ()
{
	
	delete MatcheeExpression;
	
}

IOilStatement :: StatementType OilMatch :: GetStatementType () const
{
	
	return IOilStatement :: kStatementType_Match;
	
}
	
void OilMatch :: AddBranch ( OilMatchBranch * Branch )
{
	
	Branches.push_back ( Branch );
	
}

uint32_t OilMatch :: GetBranchCount () const
{
	
	return Branches.size ();
	
}

const OilMatchBranch * OilMatch :: GetBranch ( uint32_t Index ) const
{
	
	if ( Index >= Branches.size () )
		return NULL;
	
	return Branches [ Index ];
	
}

OilMatchBranch * OilMatch :: GetBranch ( uint32_t Index )
{
	
	if ( Index >= Branches.size () )
		return NULL;
	
	return Branches [ Index ];
	
}

const OilExpression * OilMatch :: GetMatcheeExpression () const
{
	
	return MatcheeExpression;
	
}

OilExpression * OilMatch :: GetMatcheeExpression ()
{
	
	return MatcheeExpression;
	
}

const SourceRef & OilMatch :: GetSourceRef () const
{
	
	return Ref;
	
}
