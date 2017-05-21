#ifndef OIL_OILIMPLICITBINDINGINITIALIZATION_H
#define OIL_OILIMPLICITBINDINGINITIALIZATION_H

#include <OIL/IOilStatement.h>

#include <stdint.h>
#include <string>

#include <Tokenization/SourceRef.h>

class OilImplicitBindingInitialization : public virtual IOilStatement
{
public:
	
	OilImplicitBindingInitialization ( const SourceRef & Ref, const std :: u32string & BindingID );
	~OilImplicitBindingInitialization ();
	
	StatementType GetStatementType () const;
	
	const std :: u32string & GetBindingID () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string BindingID;
	
	SourceRef Ref;
	
};

#endif
