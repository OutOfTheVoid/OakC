#include <OIL/OilStatementBody.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilImplicitLocalInitialization.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilStatementBody :: OilStatementBody ():
	IgnoredParameters (),
	Statements (),
	Locals ()
{
}

OilStatementBody :: ~OilStatementBody ()
{
	
	for ( uint64_t I = 0; I < Statements.size (); I ++ )
	{
		
		if ( Statements [ I ] != NULL )
			delete Statements [ I ];
		
	}
	
	for ( uint64_t I = 0; I < Locals.size (); I ++ )
	{
		
		if ( Locals [ I ].Binding != NULL )
			delete Locals [ I ].Binding;
		
	}
	
}

void OilStatementBody :: AddIgnoredParameter ( const std :: u32string & ParameterName )
{
	
	IgnoredParameters.push_back ( ParameterName );
	
}

uint32_t OilStatementBody :: GetIgnoredParamCount () const
{
	
	return IgnoredParameters.size ();
	
}

const std :: u32string _OilStatementBody_NullString ( U"" );

const std :: u32string & OilStatementBody :: GetIgnoredParamName ( uint32_t Index ) const
{
	
	if ( Index >= IgnoredParameters.size () )
		return _OilStatementBody_NullString;
		
	return IgnoredParameters [ Index ];
	
}

void OilStatementBody :: TakeIgnoredParams ( OilStatementBody & SubBody )
{
	
	for ( uint64_t I = 0; I < SubBody.IgnoredParameters.size (); I ++ )
		IgnoredParameters.emplace_back ( std :: move ( SubBody.IgnoredParameters [ I ] ) );
	
	SubBody.IgnoredParameters.clear ();
	
}

void OilStatementBody :: AddStatement ( IOilStatement * Statement )
{
	
	Statements.push_back ( Statement );
	
}

const IOilStatement * OilStatementBody :: GetStatement ( uint64_t Index ) const
{
	
	if ( Index >= Statements.size () )
		return NULL;
	
	return Statements [ Index ];
	
}

IOilStatement * OilStatementBody :: GetStatement ( uint64_t Index )
{
	
	if ( Index >= Statements.size () )
		return NULL;
	
	return Statements [ Index ];
	
}

uint64_t OilStatementBody :: GetStatementCount () const
{
	
	return Statements.size ();
	
}

uint64_t OilStatementBody :: GetLocalBindingCount () const
{
	
	return Locals.size ();
	
}

void OilStatementBody :: AddLocalBinding ( OilBindingStatement * LocalBinding )
{
	
	LocalData Data;
	
	Data.Binding = LocalBinding;
	
	if ( LocalBinding -> HasInitializer () )
	{
		
		Data.InitializationStatementIndex = Statements.size ();
		Statements.push_back ( new OilImplicitLocalInitialization ( Locals.size () ) );
		
		
	}
	else
		Data.InitializationStatementIndex = 0;
	
	Locals.push_back ( Data );
	
}

const OilBindingStatement * OilStatementBody :: GetLocalBinding ( uint64_t Index ) const
{
	
	if ( Index >= Locals.size () )
		return NULL;
	
	return Locals [ Index ].Binding;
	
}

OilBindingStatement * OilStatementBody :: GetLocalBinding ( uint64_t Index )
{
	
	if ( Index >= Locals.size () )
		return NULL;
	
	return Locals [ Index ].Binding;
	
}

const OilBindingStatement * OilStatementBody :: FindLocalBinding ( const std :: u32string & ID ) const
{
	
	for ( uint64_t I = 0; I < Locals.size (); I ++ )
	{
		
		if ( Locals [ I ].Binding -> GetName () == ID )
			return Locals [ I ].Binding;
		
	}
	
	return NULL;
	
}

OilBindingStatement * OilStatementBody :: FindLocalBinding ( const std :: u32string & ID )
{
	
	for ( uint64_t I = 0; I < Locals.size (); I ++ )
	{
		
		if ( Locals [ I ].Binding -> GetName () == ID )
			return Locals [ I ].Binding;
		
	}
	
	return NULL;
	
}

uint64_t OilStatementBody :: GetLocalInitializationStatementIndex ( uint64_t Index ) const
{
	
	if ( Index >= Locals.size () )
		return 0;
	
	return Locals [ Index ].InitializationStatementIndex;
	
}

OilStatementBody :: StatementType OilStatementBody :: GetStatementType () const
{
	
	return kStatementType_Body;
	
}
