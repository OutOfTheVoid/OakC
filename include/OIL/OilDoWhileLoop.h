#ifndef OIL_OILDOWHILELOOP_H
#define OIL_OILDOWHILELOOP_H

#include <OIL/IOilStatement.h>
#include <OIL/IOilLoop.h>

class OilExpression;
class OilStatementBody;

#include <string>

#include <Tokenization/SourceRef.h>

class OilDoWhileLoop : public virtual IOilStatement, public virtual IOilLoop
{
public:
	
	OilDoWhileLoop ( const SourceRef & Ref, OilStatementBody * LoopBody, OilExpression * ConditionExpression );
	OilDoWhileLoop ( const SourceRef & Ref, OilStatementBody * LoopBody, OilExpression * ConditionExpression, const std :: u32string & LoopLabel );
	
	bool HasLoopLabel () const;
	
	const std :: u32string & GetLoopLabel () const;
	
	const OilExpression * GetConditionExpression () const;
	OilExpression * GetConditionExpression ();
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	StatementType GetStatementType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilExpression * ConditionExpression;
	OilStatementBody * LoopBody;
	
	const std :: u32string LoopLabel;
	
	SourceRef Ref;
	
};


#endif
