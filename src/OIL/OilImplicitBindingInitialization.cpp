#include <OIL/OilImplicitBindingInitialization.h>

OilImplicitBindingInitialization :: OilImplicitBindingInitialization ( const std :: u32string & BindingID ):
	BindingID ( BindingID )
{
}

OilImplicitBindingInitialization :: ~OilImplicitBindingInitialization ()
{
}

IOilStatement :: StatementType OilImplicitBindingInitialization :: GetStatementType () const
{
	
	return kStatementType_ImplicitBindingInitialization;
	
}

const std :: u32string & OilImplicitBindingInitialization :: GetBindingID () const
{
	
	return BindingID;
	
}
