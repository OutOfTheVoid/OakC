#include <OIL/OilBreak.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilBreak :: OilBreak ( const SourceRef & Ref ):
	LoopLabel ( U"" ),
	Ref ( Ref ),
	BrokenLoop ( NULL )
{
}

OilBreak :: OilBreak ( const SourceRef & Ref, const std :: u32string & LoopLabel ):
	LoopLabel ( LoopLabel ),
	Ref ( Ref ),
	BrokenLoop ( NULL )
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

void OilBreak :: SetBrokenLoop ( IOilLoop * Loop )
{
	
	BrokenLoop = Loop;
	
}

const IOilLoop * OilBreak :: GetBrokenLoop () const
{
	
	return BrokenLoop;
	
}

IOilLoop * OilBreak :: GetBrokenLoop ()
{
	
	return BrokenLoop;
	
}

bool OilBreak :: BrokenLoopResolved () const
{
	
	return BrokenLoop != NULL;
	
}
