#include <OIL/OilBindingStatement.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilExpression.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilBindingStatement :: OilBindingStatement ( const std :: u32string & Name, bool Public, bool Mutable, OilTypeRef * Type, OilExpression * InitializerValue ):
	Name ( Name ),
	Mutable ( Mutable ),
	Public ( Public ),
	Type ( Type ),
	InitializerValue ( InitializerValue )
{
}

OilBindingStatement :: OilBindingStatement ( const std :: u32string & Name, bool Public, bool Mutable, OilTypeRef * Type ):
	Name ( Name ),
	Mutable ( Mutable ),
	Public ( Public ),
	Type ( Type ),
	InitializerValue ( NULL )
{
}

OilBindingStatement :: ~OilBindingStatement ()
{
	
	delete Type;
	
}

const std :: u32string & OilBindingStatement :: GetName () const
{
	
	return Name;
	
}

const OilTypeRef * OilBindingStatement :: GetType () const
{
	
	return Type;
	
}

OilTypeRef * OilBindingStatement :: GetType ()
{
	
	return Type;
	
}

bool OilBindingStatement :: HasInitializer () const
{
	
	return InitializerValue != NULL;
	
}

void OilBindingStatement :: DropInitializer ()
{
	
	InitializerValue = NULL;
	
}

const OilExpression * OilBindingStatement :: GetInitializerValue () const
{
	
	return InitializerValue;
	
}

OilExpression * OilBindingStatement :: GetInitializerValue ()
{
	
	return InitializerValue;
	
}

bool OilBindingStatement :: IsMutable () const
{
	
	return Mutable;
	
}

bool OilBindingStatement :: IsPublic () const
{
	
	return Public;
	
}

IOilStatement :: StatementType OilBindingStatement :: GetStatementType () const
{
	
	return kStatementType_Binding;
	
}
