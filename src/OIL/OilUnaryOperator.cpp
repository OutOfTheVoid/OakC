#include <OIL/OilUnaryOperator.h>
#include <OIL/IOilPrimary.h>
#include <OIL/OilExpression.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilUnaryOperator :: OilUnaryOperator ( Operator Op, IOilOperator * Term ):
	Op ( Op ),
	TermIsPrimary ( false ),
	OperatorTerm ( Term )
{
}
	
OilUnaryOperator :: OilUnaryOperator ( Operator Op, IOilPrimary * Term ):
	Op ( Op ),
	TermIsPrimary ( true ),
	PrimaryTerm ( Term )
{
}

void OilUnaryOperator :: SetTerm ( IOilOperator * Term )
{
	
	if ( TermIsPrimary )
	{
		
		if ( PrimaryTerm != NULL )
			delete PrimaryTerm;
		
	}
	else
	{
		
		if ( OperatorTerm != NULL )
			delete OperatorTerm;
		
	}
	
	OperatorTerm = Term;
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
		
		if ( OperatorTerm != NULL )
			delete OperatorTerm;
		
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
		
		if ( OperatorTerm != NULL )
			delete PrimaryTerm;
		
	}
	
}

IOilOperator * OilUnaryOperator :: GetTermAsOperator () const
{
	
	return TermIsPrimary ? NULL : OperatorTerm;
	
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
		OperatorTerm = NULL;
	
}

IOilOperator :: OperatorType OilUnaryOperator :: GetOperatorType () const
{
	
	return kOperatorType_Unary;
	
}

bool OilUnaryOperator :: IsTermPrimary () const
{
	
	return TermIsPrimary;
	
}
