#ifndef OIL_OILWHILELOOP_H
#define OIL_OILWHILELOOP_H

#include <OIL/IOilStatement.h>

class OilExpression;
class OilStatementBody;

#include <string>

class OilWhileLoop : public virtual IOilStatement
{
public:
	
	OilWhileLoop ( OilExpression * ConditionExpression, OilStatementBody * LoopBody );
	OilWhileLoop ( OilExpression * ConditionExpression, OilStatementBody * LoopBody, const std :: u32string & LoopLabel );
	
	bool HasLoopLabel () const;
	
	const std :: u32string & GetLoopLabel () const;
	
	const OilExpression * GetConditionExpression () const;
	OilExpression * GetConditionExpression ();
	
	const OilStatementBody * GetLoopBody () const;
	OilStatementBody * GetLoopBody ();
	
	StatementType GetStatementType () const;
	
private:
	
	OilExpression * ConditionExpression;
	OilStatementBody * LoopBody;
	
	const std :: u32string LoopLabel;
	
};

#endif