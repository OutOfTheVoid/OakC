#include <Tokenization/Token.h>

Token :: Token ( const std :: u32string & Source, uint64_t Tag, uint64_t AuxTag, const SourceRef & Ref ):
	Source ( Source ),
	Tag ( Tag ),
	AuxTag ( AuxTag ),
	Ref ( Ref )
{
}

Token :: Token ( const Token & CopyFrom ):
	Source ( CopyFrom.Source ),
	Tag ( CopyFrom.Tag ),
	AuxTag ( CopyFrom.AuxTag ),
	Ref ( CopyFrom.Ref )
{
}

Token :: ~Token ()
{
}

const std :: u32string & Token :: GetSource () const
{
	
	return Source;
	
}

uint64_t Token :: GetTag () const
{
	
	return Tag;
	
}

uint64_t Token :: GetAuxTag () const
{
	
	return AuxTag;
	
}

const SourceRef & Token :: GetSourceRef () const
{
	
	return Ref;
	
}
