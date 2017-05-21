#include <OIL/OilBreak.h>

OilBreak :: OilBreak ( const SourceRef & Ref ):
	LoopLabel ( U"" ),
	Ref ( Ref )
{
}

OilBreak :: OilBreak ( const SourceRef & Ref, const std :: u32string & LoopLabel ):
	LoopLabel ( LoopLabel ),
	Ref ( Ref )
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

const SourceRef & OilBreak :: GetSourceRef () const
{
	
	return Ref;
	
}
