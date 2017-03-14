#ifndef OIL_OILIMPLICITBINDINGINITIALIZATIONSTATEMENT_H
#define OIL_OILIMPLICITBINDINGINITIALIZATIONSTATEMENT_H

#include <OIL/IOilStatement.h>

#include <stdint.h>
#include <string>

class OilImplicitBindingInitializationStatement : public virtual IOilStatement
{
public:
	
	OilImplicitBindingInitializationStatement ( const std :: u32string & BindingID );
	~OilImplicitBindingInitializationStatement ();
	
	StatementType GetStatementType () const;
	
	const std :: u32string & GetBindingID () const;
	
private:
	
	const std :: u32string BindingID;
	
};

#endif
