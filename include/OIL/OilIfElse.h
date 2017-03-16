#ifndef OIL_OILIFELSE_H
#define OIL_OILIFELSE_H

#include <OIL/IOilStatement.h>

#include <stdint.h>
#include <vector>

class OilExpression;
class OilStatementBody;

class OilIfElse : public virtual IOilStatement
{
public:
		
	OilIfElse ( OilExpression * IfConditionExpression, OilStatementBody * IfStatementBody );
	OilIfElse ( OilExpression * IfConditionExpression, OilStatementBody * IfStatementBody, OilStatementBody * ElseStatementBody );
	OilIfElse ( OilExpression * IfConditionExpression, OilStatementBody * IfStatementBody, OilExpression ** ElseIfConditionExpressions, OilStatementBody ** ElseIfStatementBodies, uint32_t ElseIfCount, OilStatementBody * ElseStatementBody );
	
	~OilIfElse ();
	
	const OilExpression * GetIfClauseConditionExpression () const;
	OilExpression * GetIfClauseConditionExpression ();
	
	const OilStatementBody * GetIfClauseStatementBody () const;
	OilStatementBody * GetIfClauseStatementBody ();
	
	bool HasElseClause () const;
	
	const OilStatementBody * GetElseClauseStatementBody () const;
	OilStatementBody * GetElseClauseStatementBody ();
	
	bool HasElseIfClauses () const;
	
	uint32_t GetElseIfClauseCount () const;
	
	const OilExpression * GetElseIfClauseConditionExpression ( uint32_t Index ) const;
	OilExpression * GetElseIfClauseConditionExpression ( uint32_t Index );
	
	const OilStatementBody * GetElseIfClauseStatementBody ( uint32_t Index ) const;
	OilStatementBody * GetElseIfClauseStatementBody ( uint32_t Index );
	
	StatementType GetStatementType () const;
	
private:
	
	OilExpression * IfConditionExpression;
	OilStatementBody * IfStatementBody;
	
	OilStatementBody * ElseStatementBody;
	
	typedef struct
	{
		
		OilExpression * ConditionExpression;
		OilStatementBody * StatementBody;
		
	} ElseIfClause;
	
	std :: vector <ElseIfClause> ElseIfClauses;
	
};

#endif
