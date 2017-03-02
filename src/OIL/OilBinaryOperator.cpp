#include <OIL/OilBinaryOperator.h>
#include <OIL/OilExpression.h>
#include <OIL/IOilPrimary.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilBinaryOperator :: OilBinaryOperator ( Operator Op, OilExpression * LeftTerm, OilExpression * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( false ),
	RightIsPrimary ( false ),
	LeftExpressionTerm ( LeftTerm ),
	RightExpressionTerm ( RightTerm )
{
}

OilBinaryOperator :: OilBinaryOperator ( Operator Op, OilExpression * LeftTerm, IOilPrimary * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( false ),
	RightIsPrimary ( true ),
	LeftExpressionTerm ( LeftTerm ),
	RightPrimaryTerm ( RightTerm )
{
}

OilBinaryOperator :: OilBinaryOperator ( Operator Op, IOilPrimary * LeftTerm, OilExpression * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( false ),
	RightIsPrimary ( true ),
	LeftPrimaryTerm ( LeftTerm ),
	RightExpressionTerm ( RightTerm )
{
}

OilBinaryOperator :: OilBinaryOperator ( Operator Op, IOilPrimary * LeftTerm, IOilPrimary * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( false ),
	RightIsPrimary ( true ),
	LeftPrimaryTerm ( LeftTerm ),
	RightPrimaryTerm ( RightTerm )
{
}

OilBinaryOperator :: ~OilBinaryOperator ()
{
	
	if ( LeftIsPrimary )
	{
		
		if ( LeftPrimaryTerm != NULL )
			delete LeftPrimaryTerm;
		
	}
	else
	{
		
		if ( LeftExpressionTerm != NULL )
			delete LeftExpressionTerm;
		
	}
	
	if ( RightIsPrimary )
	{
		
		if ( RightPrimaryTerm != NULL )
			delete RightPrimaryTerm;
		
	}
	else
	{
		
		if ( RightExpressionTerm != NULL )
			delete RightExpressionTerm;
		
	}
	
}

void OilBinaryOperator :: SetLeftTerm ( OilExpression * LeftTerm )
{
	
	if ( LeftIsPrimary )
	{
		
		if ( LeftPrimaryTerm != NULL )
			delete LeftPrimaryTerm;
		
	}
	else
	{
		
		if ( LeftExpressionTerm != NULL )
			delete LeftExpressionTerm;
		
	}
	
	LeftExpressionTerm = LeftTerm;
	LeftIsPrimary = false;
	
}

void OilBinaryOperator :: SetLeftTerm ( IOilPrimary * LeftTerm )
{
	
	if ( LeftIsPrimary )
	{
		
		if ( LeftPrimaryTerm != NULL )
			delete LeftPrimaryTerm;
		
	}
	else
	{
		
		if ( LeftExpressionTerm != NULL )
			delete LeftExpressionTerm;
		
	}
	
	LeftPrimaryTerm = LeftTerm;
	LeftIsPrimary = true;
	
}

void OilBinaryOperator :: SetRightTerm ( OilExpression * RightTerm )
{
	
	if ( RightIsPrimary )
	{
		
		if ( RightPrimaryTerm != NULL )
			delete RightPrimaryTerm;
		
	}
	else
	{
		
		if ( RightExpressionTerm != NULL )
			delete RightExpressionTerm;
		
	}
	
	RightExpressionTerm = RightTerm;
	RightIsPrimary = false;
	
}

void OilBinaryOperator :: SetRightTerm ( IOilPrimary * RightTerm )
{
	
	if ( RightIsPrimary )
	{
		
		if ( RightPrimaryTerm != NULL )
			delete RightPrimaryTerm;
		
	}
	else
	{
		
		if ( RightExpressionTerm != NULL )
			delete RightExpressionTerm;
		
	}
	
	RightPrimaryTerm = RightTerm;
	RightIsPrimary = true;
	
}

OilExpression * OilBinaryOperator :: GetLeftTermAsExpression () const
{
	
	return LeftIsPrimary ? NULL : LeftExpressionTerm;
	
}

IOilPrimary * OilBinaryOperator :: GetLeftTermAsPrimary () const
{
	
	return LeftIsPrimary ? LeftPrimaryTerm : NULL;
	
}

OilExpression * OilBinaryOperator :: GetRightTermAsExpression () const
{
	
	return RightIsPrimary ? NULL : RightExpressionTerm;
	
}

IOilPrimary * OilBinaryOperator :: GetRightTermAsPrimary () const
{
	
	return RightIsPrimary ? RightPrimaryTerm : NULL;
	
}

OilBinaryOperator :: Operator OilBinaryOperator :: GetOp () const
{
	
	return Op;
	
}

bool OilBinaryOperator :: ConstantTerms () const
{
	
	// FOR NOW
	return false;
	
}

void OilBinaryOperator :: DisownTerms ()
{
	
	if ( LeftIsPrimary )
		LeftPrimaryTerm = NULL;
	else
		LeftExpressionTerm = NULL;
	
	if ( RightIsPrimary )
		RightPrimaryTerm = NULL;
	else
		RightExpressionTerm = NULL;
	
}

IOilOperator :: OperatorType OilBinaryOperator :: GetOperatorType () const
{
	
	return kOperatorType_Binary;
	
}
