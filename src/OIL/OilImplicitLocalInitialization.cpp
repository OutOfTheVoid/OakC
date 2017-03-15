#include <OIL/OilImplicitLocalInitialization.h>

OilImplicitLocalInitialization :: OilImplicitLocalInitialization ( uint64_t LocalIndex ):
	LocalIndex ( LocalIndex )
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
