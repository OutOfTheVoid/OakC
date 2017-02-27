#include <OIL/OilStatementBody.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilStatementBody :: OilStatementBody ():
	IgnoredParameters (),
	Statements ()
{
	
	for ( uint64_t I = 0; I < Statements.size (); I ++ )
	{
		
		if ( Statements [ I ] != NULL )
			delete Statements [ I ];
		
	}
	
}

OilStatementBody :: ~OilStatementBody ()
{
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

OilStatementBody :: StatementType OilStatementBody :: GetStatementType () const
{
	
	return kStatementType_Body;
	
}
