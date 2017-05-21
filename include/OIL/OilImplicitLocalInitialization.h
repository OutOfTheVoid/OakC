#ifndef OIL_OILIMPLICITLOCALINITIALIZATION_H
#define OIL_OILIMPLICITLOCALINITIALIZATION_H

#include <OIL/IOilStatement.h>

#include <stdint.h>

#include <Tokenization/SourceRef.h>

class OilImplicitLocalInitialization : public virtual IOilStatement
{
public:
	
	OilImplicitLocalInitialization ( const SourceRef & Ref, uint64_t LocalIndex );
	~OilImplicitLocalInitialization ();
	
	StatementType GetStatementType () const;
	
	uint64_t GetLocalIndex () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	uint64_t LocalIndex;
	
	SourceRef Ref;
	
};

#endif
