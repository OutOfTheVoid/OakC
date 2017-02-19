#include <Tokenization/Token.h>

Token :: Token ( const std :: u32string & Source, uint64_t Char, uint64_t Line, uint64_t Tag, uint64_t AuxTag, CompilationUnit * SourceUnit ):
	Source ( Source ),
	Char ( Char ),
	Line ( Line ),
	Tag ( Tag ),
	AuxTag ( AuxTag ),
	SourceUnit ( SourceUnit )
{
}

Token :: Token ( const Token & CopyFrom ):
	Source ( CopyFrom.Source ),
	Char ( CopyFrom.Char ),
	Line ( CopyFrom.Line ),
	Tag ( CopyFrom.Tag ),
	AuxTag ( CopyFrom.AuxTag ),
	SourceUnit ( SourceUnit )
{
}

Token :: ~Token ()
{
}

const std :: u32string & Token :: GetSource () const
{
	
	return Source;
	
}

uint64_t Token :: GetChar () const
{
	
	return Char;
	
}

uint64_t Token :: GetLine () const
{
	
	return Line;
	
}

uint64_t Token :: GetTag () const
{
	
	return Tag;
	
}

uint64_t Token :: GetAuxTag () const
{
	
	return AuxTag;
	
}

CompilationUnit * Token :: GetSourceUnit () const
{
	
	return SourceUnit;
	
}
