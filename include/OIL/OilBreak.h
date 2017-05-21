#ifndef OIL_OILBREAK_H
#define OIL_OILBREAK_H

#include <OIL/IOilStatement.h>

#include <string>

#include <Tokenization/SourceRef.h>

class OilBreak : public virtual IOilStatement
{
public:
	
	OilBreak ( const SourceRef & Ref );
	OilBreak ( const SourceRef & Ref, const std :: u32string & LoopLabel );
	~OilBreak ();
	
	bool HasLoopLabel () const;
	
	const std :: u32string & GetLoopLabel () const;
	
	StatementType GetStatementType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string LoopLabel;
	
	SourceRef Ref;
	
};

#endif
