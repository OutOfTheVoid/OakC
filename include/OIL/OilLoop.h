#ifndef OIL_OILLOOP_H
#define OIL_OILLOOP_H

#include <OIL/IOilStatement.h>

#include <string>

class OilStatementBody;

class OilLoop : public virtual IOilStatement
{
public:
	
	OilLoop ( OilStatementBody * StatementBody );
	OilLoop ( OilStatementBody * StatementBody, const std :: u32string & LoopLabel );
	~OilLoop ();
	
	bool HasLoopLabel () const;
	
	const std :: u32string & GetLoopLabel () const;
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	StatementType GetStatementType () const;
	
private:
	
	OilStatementBody * StatementBody;
	
	const std :: u32string LoopLabel;
	
};

#endif
