#ifndef OIL_OILMATCHBRANCH_H
#define OIL_OILMATCHBRANCH_H

#include <Tokenization/SourceRef.h>

class OilExpression;

class OilMatchBranch
{
public:
	
	OilMatchBranch ( const SourceRef & Ref, OilExpression * MatcheeExpression );
	~OilMatchBranch ();
	
	const OilExpression * GetMatcheeExpression () const;
	OilExpression * GetMatcheeExpression ();
	
	
private:
	
	OilExpression * MatcheeExpression;
	
	const SourceRef Ref;
	
};

#endif
