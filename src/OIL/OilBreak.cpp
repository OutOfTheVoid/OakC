#include <OIL/OilBreak.h>

OilBreak :: OilBreak ():
	LoopLabel ( U"" )
{
}

OilBreak :: OilBreak ( const std :: u32string & LoopLabel ):
	LoopLabel ( LoopLabel )
{
}

OilBreak :: ~OilBreak ()
{
}

bool OilBreak :: HasLoopLabel () const
{
	
	return LoopLabel != U"";
	
}

const std :: u32string & OilBreak :: GetLoopLabel () const
{
	
	return LoopLabel;
	
}

IOilStatement :: StatementType OilBreak :: GetStatementType () const
{
	
	return kStatementType_Break;
	
}
