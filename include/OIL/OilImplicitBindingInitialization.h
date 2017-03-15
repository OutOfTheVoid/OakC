#ifndef OIL_OILIMPLICITBINDINGINITIALIZATION_H
#define OIL_OILIMPLICITBINDINGINITIALIZATION_H

#include <OIL/IOilStatement.h>

#include <stdint.h>
#include <string>

class OilImplicitBindingInitialization : public virtual IOilStatement
{
public:
	
	OilImplicitBindingInitialization ( const std :: u32string & BindingID );
	~OilImplicitBindingInitialization ();
	
	StatementType GetStatementType () const;
	
	const std :: u32string & GetBindingID () const;
	
private:
	
	const std :: u32string BindingID;
	
};

#endif
