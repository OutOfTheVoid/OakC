#include <OIL/OilImplicitLocalInitialization.h>

OilImplicitLocalInitialization :: OilImplicitLocalInitialization ( const SourceRef & Ref, uint64_t LocalIndex ):
	LocalIndex ( LocalIndex ),
	Ref ( Ref )
{
}

OilImplicitLocalInitialization :: ~OilImplicitLocalInitialization ()
{
}

IOilStatement :: StatementType OilImplicitLocalInitialization :: GetStatementType () const
{
	
	return kStatementType_ImplicitLocalInitialization;
	
}

uint64_t OilImplicitLocalInitialization :: GetLocalIndex () const
{
	
	return LocalIndex;
	
}

const SourceRef & OilImplicitLocalInitialization :: GetSourceRef () const
{
	
	return Ref;
	
}
