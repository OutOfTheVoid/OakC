#ifndef OIL_OILLOOP_H
#define OIL_OILLOOP_H

#include <OIL/IOilStatement.h>
#include <OIL/IOilLoop.h>

#include <string>

#include <Tokenization/SourceRef.h>

class OilStatementBody;

class OilLoop : public virtual IOilStatement, public virtual IOilLoop
{
public:
	
	OilLoop ( const SourceRef & Ref, OilStatementBody * StatementBody );
	OilLoop ( const SourceRef & Ref, OilStatementBody * StatementBody, const std :: u32string & LoopLabel );
	~OilLoop ();
	
	bool HasLoopLabel () const;
	
	const std :: u32string & GetLoopLabel () const;
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	StatementType GetStatementType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilStatementBody * StatementBody;
	
	const std :: u32string LoopLabel;
	
	SourceRef Ref;
	
};

#endif
