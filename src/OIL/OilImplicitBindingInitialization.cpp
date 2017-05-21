#include <OIL/OilImplicitBindingInitialization.h>

OilImplicitBindingInitialization :: OilImplicitBindingInitialization ( const SourceRef & Ref, const std :: u32string & BindingID ):
	BindingID ( BindingID ),
	Ref ( Ref )
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

const SourceRef & OilImplicitBindingInitialization :: GetSourceRef () const
{
	
	return Ref;
	
}
