#include <OIL/OilImplicitLocalInitializationStatement.h>

OilImplicitLocalInitializationStatement :: OilImplicitLocalInitializationStatement ( uint64_t LocalIndex ):
	LocalIndex ( LocalIndex )
{
}

OilImplicitLocalInitializationStatement :: ~OilImplicitLocalInitializationStatement ()
{
}

IOilStatement :: StatementType OilImplicitLocalInitializationStatement :: GetStatementType () const
{
	
	return kStatementType_ImplicitLocalInitialization;
	
}

uint64_t OilImplicitLocalInitializationStatement :: GetLocalIndex () const
{
	
	return LocalIndex;
	
}
