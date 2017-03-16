#include <OIL/OilWhileLoop.h>

OilWhileLoop :: OilWhileLoop ( OilExpression * ConditionExpression, OilStatementBody * LoopBody ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( U"" )
{
}

OilWhileLoop :: OilWhileLoop ( OilExpression * ConditionExpression, OilStatementBody * LoopBody, const std :: u32string & LoopLabel ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( LoopLabel )
{
}

bool OilWhileLoop :: HasLoopLabel () const
{
	
	return LoopLabel != U"";
	
}

const std :: u32string & OilWhileLoop :: GetLoopLabel () const
{
	
	return LoopLabel;
	
}

const OilExpression * OilWhileLoop :: GetConditionExpression () const
{
	
	return ConditionExpression;
	
}

OilExpression * OilWhileLoop :: GetConditionExpression ()
{
	
	return ConditionExpression;
	
}

const OilStatementBody * OilWhileLoop :: GetLoopBody () const
{
	
	return LoopBody;
	
}

OilStatementBody * OilWhileLoop :: GetLoopBody ()
{
	
	return LoopBody;
	
}

IOilStatement :: StatementType OilWhileLoop :: GetStatementType () const
{
	
	return kStatementType_WhileLoop;
	
}
