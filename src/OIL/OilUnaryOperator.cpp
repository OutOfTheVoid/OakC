#include <OIL/OilUnaryOperator.h>
#include <OIL/IOilPrimary.h>
#include <OIL/OilExpression.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilUnaryOperator :: OilUnaryOperator ( Operator Op, OilExpression * Term ):
	Op ( Op ),
	TermIsPrimary ( false ),
	ExpressionTerm ( Term )
{
}
	
OilUnaryOperator :: OilUnaryOperator ( Operator Op, IOilPrimary * Term ):
	Op ( Op ),
	TermIsPrimary ( true ),
	PrimaryTerm ( Term )
{
}

void OilUnaryOperator :: SetTerm ( OilExpression * Term )
{
	
	if ( TermIsPrimary )
	{
		
		if ( PrimaryTerm != NULL )
			delete PrimaryTerm;
		
	}
	else
	{
		
		if ( ExpressionTerm != NULL )
			delete PrimaryTerm;
		
	}
	
	ExpressionTerm = Term;
	TermIsPrimary = false;
	
}

void OilUnaryOperator :: SetTerm ( IOilPrimary * Term )
{
	
	if ( TermIsPrimary )
	{
		
		if ( PrimaryTerm != NULL )
			delete PrimaryTerm;
		
	}
	else
	{
		
		if ( ExpressionTerm != NULL )
			delete PrimaryTerm;
		
	}
	
	PrimaryTerm = Term;
	TermIsPrimary = true;
	
}

OilUnaryOperator :: ~OilUnaryOperator ()
{
	
	if ( TermIsPrimary )
	{
		
		if ( PrimaryTerm != NULL )
			delete PrimaryTerm;
		
	}
	else
	{
		
		if ( ExpressionTerm != NULL )
			delete PrimaryTerm;
		
	}
	
}

OilExpression * OilUnaryOperator :: GetTermAsExpression () const
{
	
	return TermIsPrimary ? NULL : ExpressionTerm;
	
}


IOilPrimary * OilUnaryOperator :: GetTermAsPrimary () const
{
	
	return TermIsPrimary ? PrimaryTerm : NULL;
	
}

OilUnaryOperator :: Operator OilUnaryOperator :: GetOp () const
{
	
	return Op;
	
}

bool OilUnaryOperator :: ConstantTerms () const
{
	
	// FOR NOW
	return false;
	
}

void OilUnaryOperator :: DisownTerm ()
{
	
	if ( TermIsPrimary )
		PrimaryTerm = NULL;
	else
		ExpressionTerm = NULL;
	
}

IOilOperator :: OperatorType OilUnaryOperator :: GetOperatorType () const
{
	
	return kOperatorType_Unary;
	
}
