#ifndef OIL_OILBREAK_H
#define OIL_OILBREAK_H

#include <OIL/IOilStatement.h>

#include <string>

class OilBreak : public virtual IOilStatement
{
public:
	
	OilBreak ();
	OilBreak ( const std :: u32string & LoopLabel );
	~OilBreak ();
	
	bool HasLoopLabel () const;
	
	const std :: u32string & GetLoopLabel () const;
	
	StatementType GetStatementType () const;
	
private:
	
	const std :: u32string LoopLabel;
	
};

#endif
