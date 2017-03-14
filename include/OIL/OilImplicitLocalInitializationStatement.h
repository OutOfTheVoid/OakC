#ifndef OIL_OILIMPLICITLOCALINITIALIZATIONSTATEMENT_H
#define OIL_OILIMPLICITLOCALINITIALIZATIONSTATEMENT_H

#include <OIL/IOilStatement.h>

#include <stdint.h>

class OilImplicitLocalInitializationStatement : public virtual IOilStatement
{
public:
	
	OilImplicitLocalInitializationStatement ( uint64_t LocalIndex );
	~OilImplicitLocalInitializationStatement ();
	
	StatementType GetStatementType () const;
	
	uint64_t GetLocalIndex () const;
	
private:
	
	uint64_t LocalIndex;
	
};

#endif
