#ifndef OIL_OILDOWHILELOOP_H
#define OIL_OILDOWHILELOOP_H

#include <OIL/IOilStatement.h>

class OilExpression;
class OilStatementBody;

#include <string>

class OilDoWhileLoop : public virtual IOilStatement
{
public:
	
	OilDoWhileLoop ( OilStatementBody * LoopBody, OilExpression * ConditionExpression );
	OilDoWhileLoop ( OilStatementBody * LoopBody, OilExpression * ConditionExpression, const std :: u32string & LoopLabel );
	
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
