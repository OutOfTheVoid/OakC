#ifndef OIL_OILMATCHBRANCH_H
#define OIL_OILMATCHBRANCH_H

#include <Tokenization/SourceRef.h>

#include <string>

class IOilPrimary;
class OilStatementBody;
class OilAllusion;
class OilStructDestructure;

class OilMatchBranch
{
public:
	
	typedef enum
	{
		
		kMatchType_Constant,
		kMatchType_Allusion,
		kMatchType_AllusionValue,
		kMatchType_Destructure,
		kMatchType_Other
		
	} MatchType;
	
	OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body );
	OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, IOilPrimary * MatchConstantPrimary );
	OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, OilAllusion * MatchAllusion );
	OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, OilAllusion * MatchAllusion, const std :: u32string & AllusionValueName );
	OilMatchBranch ( const SourceRef & Ref, OilStatementBody * Body, OilAllusion * MatchAllusion, OilStructDestructure * Destructure );
	~OilMatchBranch ();
	
	MatchType GetMatchType () const;
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	const IOilPrimary * GetConstantPrimary () const;
	IOilPrimary * GetConstantPrimary ();
	
	const OilAllusion * GetMatchAllusion () const;
	OilAllusion * GetMatchAllusion ();
	
	const OilStructDestructure * GetMatchDestructure () const;
	OilStructDestructure * GetMatchDestructure ();
	
	const std :: u32string & GetAllusionValueName () const;
	
private:
	
	MatchType Type;
	
	union
	{
		
		IOilPrimary * MatchConstantPrimary;
		OilAllusion * MatchAllusion;
		
	};
	
	const std :: u32string AllusionValueName;
	OilStructDestructure * MatchDestructure;
	
	OilStatementBody * Body;
	
	const SourceRef Ref;
	
};

#endif
