#include <OIL/OilReturn.h>
#include <OIL/OilExpression.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilReturn :: OilReturn ( const SourceRef & Ref, OilExpression * ReturnedExpression ):
	ReturnedExpression ( ReturnedExpression ),
	Ref ( Ref )
{
}

OilReturn :: OilReturn ( const SourceRef & Ref ):
	ReturnedExpression ( NULL ),
	Ref ( Ref )
{
}

OilReturn :: ~OilReturn ()
{
	
	if ( ReturnedExpression != NULL )
		delete ReturnedExpression;
	
}

const OilExpression * OilReturn :: GetReturnedExpression () const
{
	
	return ReturnedExpression;
	
}

OilExpression * OilReturn :: GetReturnedExpression ()
{
	
	return ReturnedExpression;
	
}

bool OilReturn :: HasExpression () const
{
	
	return ReturnedExpression != NULL;
	
}

IOilStatement :: StatementType OilReturn :: GetStatementType () const
{
	
	return kStatementType_Return;
	
}

const SourceRef & OilReturn :: GetSourceRef () const
{
	
	return Ref;
	
}
