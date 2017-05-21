#ifndef TOKENIZATION_TOKEN_H
#define TOKENIZATION_TOKEN_H

#include <string>
#include <stdint.h>

#include <Tokenization/SourceRef.h>

class CompilationUnit;

class Token
{
public:
	
	/// Token constructor. Sets associated fields.
	Token ( const std :: u32string & Source, uint64_t Tag, uint64_t AuxTag, const SourceRef & Ref );
	/// Copy constructor.
	Token ( const Token & CopyFrom );
	/// Destructor.
	~Token ();
	
	/// Gets the source segment that the token represents.
	const std :: u32string & GetSource () const;
	
	/// Gets the optional tag set to aid the lexer.
	uint64_t GetTag () const;
	/// Gets the optional tag-specific auxiliary tag.
	uint64_t GetAuxTag () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string Source;
	
	uint64_t Tag;
	uint64_t AuxTag;
	
	SourceRef Ref;
	
};

#endif
