#include <OIL/OilConstStatement.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilExpression.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilConstStatement :: OilConstStatement ( const std :: u32string & Name, bool Public, OilTypeRef * Type, OilExpression * InitializerValue ):
	Name ( Name ),
	Public ( Public ),
	Type ( Type ),
	InitializerValue ( InitializerValue )
{
}

OilConstStatement :: ~OilConstStatement ()
{
	
	delete Type;
	
}

const std :: u32string & OilConstStatement :: GetName () const
{
	
	return Name;
	
}

const OilTypeRef * OilConstStatement :: GetType () const
{
	
	return Type;
	
}

OilTypeRef * OilConstStatement :: GetType ()
{
	
	return Type;
	
}

void OilConstStatement :: DropInitializer ()
{
	
	InitializerValue = NULL;
	
}

const OilExpression * OilConstStatement :: GetInitializerValue () const
{
	
	return InitializerValue;
	
}

OilExpression * OilConstStatement :: GetInitializerValue ()
{
	
	return InitializerValue;
	
}

bool OilConstStatement :: IsPublic () const
{
	
	return Public;
	
}

IOilStatement :: StatementType OilConstStatement :: GetStatementType () const
{
	
	return kStatementType_Const;
	
}
