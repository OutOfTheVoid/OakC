#ifndef OIL_OILMATCH_H
#define OIL_OILMATCH_H

#include <OIL/IOilStatement.h>

#include <Tokenization/SourceRef.h>

#include <vector>

class OilExpression;

class OilMatchBranch;

class OilMatch : public virtual IOilStatement
{
public:
	
	OilMatch ( const SourceRef & Ref, OilExpression * MatcheeExpression );
	~OilMatch ();
	
	StatementType GetStatementType () const;
	
	const OilExpression * GetMatcheeExpression () const;
	OilExpression * GetMatcheeExpression ();
	
	uint32_t GetBranchCount () const;
	
	void AddBranch ( OilMatchBranch * Branch );
	
	const OilMatchBranch * GetBranch ( uint32_t Index ) const;
	OilMatchBranch * GetBranch ( uint32_t Index );
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilExpression * MatcheeExpression;
	
	std :: vector <OilMatchBranch *> Branches;
	
	const SourceRef & Ref;
	
};

#endif
