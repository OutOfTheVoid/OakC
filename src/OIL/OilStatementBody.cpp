#include <OIL/OilStatementBody.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilConstStatement.h>
#include <OIL/OilImplicitLocalInitialization.h>
#include <OIL/OilLoop.h>
#include <OIL/OilIfElse.h>
#include <OIL/OilDoWhileLoop.h>
#include <OIL/OilWhileLoop.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilStatementBody :: OilStatementBody ( const SourceRef & Ref ):
	IgnoredParameters (),
	Statements (),
	Locals (),
	Constants (),
	ParentBody ( NULL ),
	ParentSelfIndex ( 0 ),
	Ref ( Ref )
{
}

OilStatementBody :: ~OilStatementBody ()
{
	
	for ( uint64_t I = 0; I < Statements.size (); I ++ )
	{
		
		if ( Statements [ I ] != NULL )
			delete Statements [ I ];
		
	}
	
}

bool OilStatementBody :: IsRootBody () const
{
	
	return ParentBody != NULL;
	
}

OilStatementBody * OilStatementBody :: GetParentBody () const
{
	
	return ParentBody;
	
}

uint64_t OilStatementBody :: GetParentBodySelfIndex () const
{
	
	return ParentSelfIndex;
	
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
	
	switch ( Statement -> GetStatementType () )
	{
		
		case kStatementType_Body:
		{
			
			OilStatementBody * BodyStatement = dynamic_cast <OilStatementBody *> ( Statement );
			
			BodyStatement -> ParentBody = this;
			BodyStatement -> ParentSelfIndex = Statements.size ();
				
		}
		break;
		
		case kStatementType_IfElse:
		{
			
			OilIfElse * IfElse = dynamic_cast <OilIfElse *> ( Statement );
			
			IfElse -> GetIfClauseStatementBody () -> ParentBody = this;
			IfElse -> GetIfClauseStatementBody () -> ParentSelfIndex = Statements.size ();
			
			uint32_t ElseIfCount = IfElse -> HasElseIfClauses () ? IfElse -> GetElseIfClauseCount () : 0;
			
			for ( uint32_t I = 0; I < ElseIfCount; I ++ )
			{
				
				IfElse -> GetElseIfClauseStatementBody ( I ) -> ParentBody = this;
				IfElse -> GetElseIfClauseStatementBody ( I ) -> ParentSelfIndex = Statements.size ();
				
			}
			
			if ( IfElse -> HasElseClause () )
			{
				
				IfElse -> GetElseClauseStatementBody () -> ParentBody = this;
				IfElse -> GetElseClauseStatementBody () -> ParentSelfIndex = Statements.size ();
				
			}
			
		}
		break;
		
		case kStatementType_WhileLoop:
		{
			
			OilWhileLoop * WhileLoop = dynamic_cast <OilWhileLoop *> ( Statement );
			
			WhileLoop -> GetStatementBody () -> ParentBody = this;
			WhileLoop -> GetStatementBody () -> ParentSelfIndex = Statements.size ();
			
		}
		break;
		
		case kStatementType_DoWhileLoop:
		{
			
			OilDoWhileLoop * DoWhileLoop = dynamic_cast <OilDoWhileLoop *> ( Statement );
			
			DoWhileLoop -> GetStatementBody () -> ParentBody = this;
			DoWhileLoop -> GetStatementBody () -> ParentSelfIndex = Statements.size ();
			
		}
		break;
		
		case kStatementType_Loop:
		{
			
			OilLoop * Loop = dynamic_cast <OilLoop *> ( Statement );
			
			Loop -> GetStatementBody () -> ParentBody = this;
			Loop -> GetStatementBody () -> ParentSelfIndex = Statements.size ();
			
		}
		break;
		
		default:
		break;
		
	}
	
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
	
	Statements.push_back ( LocalBinding );
	
	if ( LocalBinding -> HasInitializer () )
	{
		
		Data.InitializationStatementIndex = Statements.size ();
		Statements.push_back ( new OilImplicitLocalInitialization ( LocalBinding -> GetSourceRef (), Locals.size () ) );
		
	}
	else
		Data.InitializationStatementIndex = 0xFFFFFFFFFFFFFFFF;
	
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

void OilStatementBody :: AddLocalConst ( OilConstStatement * Const )
{
	
	Constants.push_back ( Const );
	Statements.push_back ( Const );
	
}

uint64_t OilStatementBody :: GetLocalConstCount () const
{
	
	return Constants.size ();
	
}

const OilConstStatement * OilStatementBody :: GetLocalConst ( uint64_t Index ) const
{
	
	if ( Index >= Constants.size () )
		return NULL;
	
	return Constants [ Index ];
	
}

OilConstStatement * OilStatementBody :: GetLocalConst ( uint64_t Index )
{
	
	if ( Index >= Constants.size () )
		return NULL;
	
	return Constants [ Index ];
	
}

const OilConstStatement * OilStatementBody :: FindLocalConst ( const std :: u32string & ID ) const
{
	
	for ( uint64_t I = 0; I < Constants.size (); I ++ )
	{
		
		if ( Constants [ I ] -> GetName () == ID )
			return Constants [ I ];
		
	}
	
	return NULL;
	
}

OilConstStatement * OilStatementBody :: FindLocalConst ( const std :: u32string & ID )
{
	
	for ( uint64_t I = 0; I < Constants.size (); I ++ )
	{
		
		if ( Constants [ I ] -> GetName () == ID )
			return Constants [ I ];
		
	}
	
	return NULL;
	
}

OilStatementBody :: StatementType OilStatementBody :: GetStatementType () const
{
	
	return kStatementType_Body;
	
}

const SourceRef & OilStatementBody :: GetSourceRef () const
{
	
	return Ref;
	
}
