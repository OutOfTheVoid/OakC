#include <OIL/OilWhileLoop.h>

OilWhileLoop :: OilWhileLoop ( const SourceRef & Ref, OilExpression * ConditionExpression, OilStatementBody * LoopBody ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( U"" ),
	Ref ( Ref )
{
}

OilWhileLoop :: OilWhileLoop ( const SourceRef & Ref, OilExpression * ConditionExpression, OilStatementBody * LoopBody, const std :: u32string & LoopLabel ):
	ConditionExpression ( ConditionExpression ),
	LoopBody ( LoopBody ),
	LoopLabel ( LoopLabel ),
	Ref ( Ref )
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

const OilStatementBody * OilWhileLoop :: GetStatementBody () const
{
	
	return LoopBody;
	
}

OilStatementBody * OilWhileLoop :: GetStatementBody ()
{
	
	return LoopBody;
	
}

IOilStatement :: StatementType OilWhileLoop :: GetStatementType () const
{
	
	return kStatementType_WhileLoop;
	
}

const SourceRef & OilWhileLoop :: GetSourceRef () const
{
	
	return Ref;
	
}
