#ifndef OIL_OILIMPLICITLOCALINITIALIZATION_H
#define OIL_OILIMPLICITLOCALINITIALIZATION_H

#include <OIL/IOilStatement.h>

#include <stdint.h>

class OilImplicitLocalInitialization : public virtual IOilStatement
{
public:
	
	OilImplicitLocalInitialization ( uint64_t LocalIndex );
	~OilImplicitLocalInitialization ();
	
	StatementType GetStatementType () const;
	
	uint64_t GetLocalIndex () const;
	
private:
	
	uint64_t LocalIndex;
	
};

#endif
