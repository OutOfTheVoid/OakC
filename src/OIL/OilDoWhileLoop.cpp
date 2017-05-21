#include <OIL/OilDoWhileLoop.h>

OilDoWhileLoop :: OilDoWhileLoop ( const SourceRef & Ref, OilStatementBody * LoopBody, OilExpression * ConditionExpression ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( U"" ),
	Ref ( Ref )
{
}

OilDoWhileLoop :: OilDoWhileLoop ( const SourceRef & Ref, OilStatementBody * LoopBody, OilExpression * ConditionExpression, const std :: u32string & LoopLabel ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( LoopLabel ),
	Ref ( Ref )
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

const SourceRef & OilDoWhileLoop :: GetSourceRef () const
{
	
	return Ref;
	
}
