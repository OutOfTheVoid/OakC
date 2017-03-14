#include <OIL/OilImplicitBindingInitializationStatement.h>

OilImplicitBindingInitializationStatement :: OilImplicitBindingInitializationStatement ( const std :: u32string & BindingID ):
	BindingID ( BindingID )
{
}

OilImplicitBindingInitializationStatement :: ~OilImplicitBindingInitializationStatement ()
{
}

IOilStatement :: StatementType OilImplicitBindingInitializationStatement :: GetStatementType () const
{
	
	return kStatementType_ImplicitBindingInitialization;
	
}

const std :: u32string & OilImplicitBindingInitializationStatement :: GetBindingID () const
{
	
	return BindingID;
	
}
