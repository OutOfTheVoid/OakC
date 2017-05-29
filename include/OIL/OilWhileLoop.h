#ifndef OIL_OILWHILELOOP_H
#define OIL_OILWHILELOOP_H

#include <OIL/IOilStatement.h>

class OilExpression;
class OilStatementBody;

#include <string>

#include <Tokenization/SourceRef.h>

class OilWhileLoop : public virtual IOilStatement
{
public:
	
	OilWhileLoop ( const SourceRef & Ref, OilExpression * ConditionExpression, OilStatementBody * LoopBody );
	OilWhileLoop ( const SourceRef & Ref, OilExpression * ConditionExpression, OilStatementBody * LoopBody, const std :: u32string & LoopLabel );
	
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
