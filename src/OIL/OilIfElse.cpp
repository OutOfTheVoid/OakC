#include <OIL/OilIfElse.h>
#include <OIL/OilExpression.h>
#include <OIL/OilStatementBody.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilIfElse :: OilIfElse ( OilExpression * IfConditionExpression, OilStatementBody * IfStatementBody ):
	IfConditionExpression ( IfConditionExpression ),
	IfStatementBody ( IfStatementBody ),
	ElseStatementBody ( NULL ),
	ElseIfClauses ()
{
}
	
OilIfElse :: OilIfElse ( OilExpression * IfConditionExpression, OilStatementBody * IfStatementBody, OilStatementBody * ElseStatementBody ):
	IfConditionExpression ( IfConditionExpression ),
	IfStatementBody ( IfStatementBody ),
	ElseStatementBody ( ElseStatementBody ),
	ElseIfClauses ()
{
}

OilIfElse :: OilIfElse ( OilExpression * IfConditionExpression, OilStatementBody * IfStatementBody, OilExpression ** ElseIfConditionExpressions, OilStatementBody ** ElseIfStatementBodies, uint32_t ElseIfCount, OilStatementBody * ElseStatementBody ):
	IfConditionExpression ( IfConditionExpression ),
	IfStatementBody ( IfStatementBody ),
	ElseStatementBody ( ElseStatementBody ),
	ElseIfClauses ()
{
	
	for ( uint32_t I = 0; I < ElseIfCount; I ++ )
	{
		
		ElseIfClause Clause;
		
		Clause.ConditionExpression = ElseIfConditionExpressions [ I ];
		Clause.StatementBody = ElseIfStatementBodies [ I ];
		
		ElseIfClauses.push_back ( Clause );
		
	}
	
}

OilIfElse :: ~OilIfElse ()
{
	
	delete IfConditionExpression;
	delete IfStatementBody;
	
	for ( uint32_t I = 0; I < ElseIfClauses.size (); I ++ )
	{
		
		delete ElseIfClauses [ I ].ConditionExpression;
		delete ElseIfClauses [ I ].StatementBody;
		
	}
	
	if ( ElseStatementBody != NULL )
		delete ElseStatementBody;
	
}

const OilExpression * OilIfElse :: GetIfClauseConditionExpression () const
{
	
	return IfConditionExpression;
	
}

OilExpression * OilIfElse :: GetIfClauseConditionExpression ()
{
	
	return IfConditionExpression;
	
}

const OilStatementBody * OilIfElse :: GetIfClauseStatementBody () const
{
	
	return IfStatementBody;
	
}

OilStatementBody * OilIfElse :: GetIfClauseStatementBody ()
{
	
	return IfStatementBody;
	
}

bool OilIfElse :: HasElseClause () const
{
	
	return ElseStatementBody != NULL;
	
}

const OilStatementBody * OilIfElse :: GetElseClauseStatementBody () const
{
	
	return ElseStatementBody;
	
}

OilStatementBody * OilIfElse :: GetElseClauseStatementBody ()
{
	
	return ElseStatementBody;
	
}

bool OilIfElse :: HasElseIfClauses () const
{
	
	return ElseIfClauses.size () != 0;
	
}

uint32_t OilIfElse :: GetElseIfClauseCount () const
{
	
	return ElseIfClauses.size ();
	
}

const OilExpression * OilIfElse :: GetElseIfClauseConditionExpression ( uint32_t Index ) const
{
	
	if ( Index >= ElseIfClauses.size () )
		return NULL;
	
	return ElseIfClauses [ Index ].ConditionExpression;
	
}

OilExpression * OilIfElse :: GetElseIfClauseConditionExpression ( uint32_t Index )
{
	
	if ( Index >= ElseIfClauses.size () )
		return NULL;
	
	return ElseIfClauses [ Index ].ConditionExpression;
	
}

const OilStatementBody * OilIfElse :: GetElseIfClauseStatementBody ( uint32_t Index ) const
{
	
	if ( Index >= ElseIfClauses.size () )
		return NULL;
	
	return ElseIfClauses [ Index ].StatementBody;
	
}

OilStatementBody * OilIfElse :: GetElseIfClauseStatementBody ( uint32_t Index )
{
	
	if ( Index >= ElseIfClauses.size () )
		return NULL;
	
	return ElseIfClauses [ Index ].StatementBody;
	
}

IOilStatement :: StatementType OilIfElse :: GetStatementType () const
{
	
	return kStatementType_IfElse;
	
}
