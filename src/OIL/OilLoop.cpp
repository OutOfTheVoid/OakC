#include <OIL/OilLoop.h>
#include <OIL/OilStatementBody.h>

OilLoop :: OilLoop ( OilStatementBody * StatementBody ):
	StatementBody ( StatementBody ),
	LoopLabel ( U"" )
{
}

OilLoop :: OilLoop ( OilStatementBody * StatementBody, const std :: u32string & LoopLabel ):
	StatementBody ( StatementBody ),
	LoopLabel ( LoopLabel )
{	
}

OilLoop :: ~OilLoop ()
{
	
	delete StatementBody;
	
}

bool OilLoop :: HasLoopLabel () const
{
	
	return LoopLabel != U"";
	
}

const std :: u32string & OilLoop :: GetLoopLabel () const
{
	
	return LoopLabel;
	
}

const OilStatementBody * OilLoop :: GetStatementBody () const
{
	
	return StatementBody;
	
}

OilStatementBody * OilLoop :: GetStatementBody ()
{
	
	return StatementBody;
	
}

IOilStatement :: StatementType OilLoop :: GetStatementType () const
{
	
	return kStatementType_Loop;
	
}
