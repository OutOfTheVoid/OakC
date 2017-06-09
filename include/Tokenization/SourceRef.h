#ifndef TOKENIZATION_SOURCEREF_H
#define TOKENIZATION_SOURCEREF_H

#include <stdint.h>

#ifndef NULL
	#define NULL nullptr
#endif

class CompilationUnit;

class SourceRef
{
public:
	
	inline SourceRef ():
		Char ( 0 ),
		Line ( 0 ),
		SourceUnit ( NULL )
	{
	}
	
	inline SourceRef ( uint64_t Char, uint64_t Line, CompilationUnit * SourceUnit ):
		Char ( Char ),
		Line ( Line ),
		SourceUnit ( SourceUnit )
	{
	}
	
	inline SourceRef ( const SourceRef & CopyFrom ):
		Char ( CopyFrom.Char ),
		Line ( CopyFrom.Line ),
		SourceUnit ( CopyFrom.SourceUnit )
	{
	}
	
	inline ~SourceRef () {};
	
	inline uint64_t GetChar () const
	{
		
		return Char;
		
	}
	
	inline uint64_t GetLine () const
	{
		
		return Line;
		
	}
	
	inline const CompilationUnit * GetUnit () const
	{
		
		return SourceUnit;
		
	}
	
	inline CompilationUnit * GetUnit ()
	{
		
		return SourceUnit;
		
	}
	
private:
	
	uint64_t Char;
	uint64_t Line;
	
	CompilationUnit * SourceUnit;
	
};

#endif
