#include <OIL/OilDoWhileLoop.h>

OilDoWhileLoop :: OilDoWhileLoop ( OilStatementBody * LoopBody, OilExpression * ConditionExpression ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( U"" )
{
}

OilDoWhileLoop :: OilDoWhileLoop ( OilStatementBody * LoopBody, OilExpression * ConditionExpression, const std :: u32string & LoopLabel ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( LoopLabel )
{
}

bool OilDoWhileLoop :: HasLoopLabel () const
{
	
	return LoopLabel != U"";
	
}

const std :: u32string & OilDoWhileLoop :: GetLoopLabel () const
{
	
	return LoopLabel;
	
}

const OilExpression * OilDoWhileLoop :: GetConditionExpression () const
{
	
	return ConditionExpression;
	
}

OilExpression * OilDoWhileLoop :: GetConditionExpression ()
{
	
	return ConditionExpression;
	
}

const OilStatementBody * OilDoWhileLoop :: GetLoopBody () const
{
	
	return LoopBody;
	
}

OilStatementBody * OilDoWhileLoop :: GetLoopBody ()
{
	
	return LoopBody;
	
}

IOilStatement :: StatementType OilDoWhileLoop :: GetStatementType () const
{
	
	return kStatementType_DoWhileLoop;
	
}
