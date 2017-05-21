#include <OIL/OilExpressionStatement.h>
#include <OIL/OilExpression.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilExpressionStatement :: OilExpressionStatement ( const SourceRef & Ref, OilExpression * Expression ):
	Expression ( Expression ),
	Ref ( Ref )
{
}

OilExpressionStatement :: ~OilExpressionStatement ()
{
	
	if ( Expression == NULL )
		delete Expression;
	
}

OilExpression * OilExpressionStatement :: GetExpression ()
{
	
	return Expression;
	
}

const OilExpression * OilExpressionStatement :: GetExpression () const
{
	
	return Expression;
	
}

void OilExpressionStatement :: DisownExpression ()
{
	
	Expression = NULL;
	
}

const SourceRef & OilExpressionStatement :: GetSourceRef () const
{
	
	return Ref;
	
}
