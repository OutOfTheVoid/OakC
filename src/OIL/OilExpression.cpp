#include <OIL/OilExpression.h>
#include <OIL/IOilPrimary.h>
#include <OIL/IOilOperator.h>

#ifndef NULL
	#define NULL nullptr
#endif

OilExpression :: OilExpression ( const SourceRef & Ref, IOilPrimary * Primary ):
	TermIsPrimary ( true ),
	PrimaryTerm ( Primary ),
	Ref ( Ref )
{
}

OilExpression :: OilExpression ( const SourceRef & Ref, IOilOperator * Operator ):
	TermIsPrimary ( false ),
	OperatorTerm ( Operator ),
	Ref ( Ref )
{
}

OilExpression :: ~OilExpression ()
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
	
}

bool OilExpression :: IsPrimary () const
{
	
	return TermIsPrimary;
	
}

IOilOperator * OilExpression :: GetTermAsOperator () const
{
	
	return TermIsPrimary ? NULL : OperatorTerm;
	
}

IOilPrimary * OilExpression :: GetTermAsPrimary () const
{
	
	return TermIsPrimary ? PrimaryTerm : NULL;
	
}

void OilExpression :: SetTerm ( IOilOperator * Operator )
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
	
	TermIsPrimary = false;
	OperatorTerm = Operator;
	
}

void OilExpression :: SetTerm ( IOilPrimary * Primary )
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
	
	TermIsPrimary = true;
	PrimaryTerm = Primary;
	
}

void OilExpression :: DisownTerm ()
{
	
	if ( TermIsPrimary )
		PrimaryTerm = NULL;
	else
		OperatorTerm = NULL;
	
}

bool OilExpression :: IsConstant () const
{
	
	if ( TermIsPrimary )
		return PrimaryTerm -> IsConstant ();
	
	return OperatorTerm -> ConstantTerms ();
	
}

IOilStatement :: StatementType OilExpression :: GetStatementType () const
{
	
	return kStatementType_Expression;
	
}

IOilPrimary :: PrimaryType OilExpression :: GetPrimaryType () const
{
	
	return kPrimaryType_Expression;
	
}

const SourceRef & OilExpression :: GetSourceRef () const
{
	
	return Ref;
	
}
