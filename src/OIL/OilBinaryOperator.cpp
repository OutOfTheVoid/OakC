#include <OIL/OilBinaryOperator.h>
#include <OIL/IOilOperator.h>
#include <OIL/IOilPrimary.h>

#ifndef NULL
	#define NULL nullptr
#endif

const std :: string OilBinaryOperator :: OperatorStrings [] =
{
	
	"RESERVED_0",
	"RESERVED_1",
	"multiply",
	"divide",
	"modulo",
	"add",
	"subtract",
	"left_shift",
	"right_shift_arithmetic",
	"right_shift_logical",
	"greater_than",
	"less_than",
	"greater_than_or_equal",
	"less_than_or_equal",
	"not_equal",
	"equal",
	"bitwise_and",
	"bitwise_xor",
	"bitwise_or",
	"logical_and",
	"logical_or",
	"assign",
	"compound_multiply",
	"compound_divide",
	"compound_modulo",
	"compound_add",
	"compound_subtract",
	"compound_left_shift",
	"compound_right_shift_arithmetic",
	"compound_right_shift_logical",
	"compound_bitwise_and",
	"compound_bitwise_or",
	"compound_bitwise_xor",
	"compound_logical_and",
	"compound_logical_or",
	
};

const uint32_t OilBinaryOperator :: MaxOpString = 34;

const std :: string OilBinaryOperator :: UnknownOpString = "UNKOWN_OP";

OilBinaryOperator :: OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilOperator * LeftTerm, IOilOperator * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( false ),
	RightIsPrimary ( false ),
	LeftOperatorTerm ( LeftTerm ),
	RightOperatorTerm ( RightTerm ),
	Ref ( Ref )
{
}

OilBinaryOperator :: OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilOperator * LeftTerm, IOilPrimary * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( false ),
	RightIsPrimary ( true ),
	LeftOperatorTerm ( LeftTerm ),
	RightPrimaryTerm ( RightTerm ),
	Ref ( Ref )
{
}

OilBinaryOperator :: OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilPrimary * LeftTerm, IOilOperator * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( true ),
	RightIsPrimary ( false ),
	LeftPrimaryTerm ( LeftTerm ),
	RightOperatorTerm ( RightTerm ),
	Ref ( Ref )
{
}

OilBinaryOperator :: OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilPrimary * LeftTerm, IOilPrimary * RightTerm ):
	Op ( Op ),
	LeftIsPrimary ( true ),
	RightIsPrimary ( true ),
	LeftPrimaryTerm ( LeftTerm ),
	RightPrimaryTerm ( RightTerm ),
	Ref ( Ref )
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
		
		if ( LeftOperatorTerm != NULL )
			delete LeftOperatorTerm;
		
	}
	
	if ( RightIsPrimary )
	{
		
		if ( RightPrimaryTerm != NULL )
			delete RightPrimaryTerm;
		
	}
	else
	{
		
		if ( RightOperatorTerm != NULL )
			delete RightOperatorTerm;
		
	}
	
}

void OilBinaryOperator :: SetLeftTerm ( IOilOperator * LeftTerm )
{
	
	if ( LeftIsPrimary )
	{
		
		if ( LeftPrimaryTerm != NULL )
			delete LeftPrimaryTerm;
		
	}
	else
	{
		
		if ( LeftOperatorTerm != NULL )
			delete LeftOperatorTerm;
		
	}
	
	LeftOperatorTerm = LeftTerm;
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
		
		if ( LeftOperatorTerm != NULL )
			delete LeftOperatorTerm;
		
	}
	
	LeftPrimaryTerm = LeftTerm;
	LeftIsPrimary = true;
	
}

void OilBinaryOperator :: SetRightTerm ( IOilOperator * RightTerm )
{
	
	if ( RightIsPrimary )
	{
		
		if ( RightPrimaryTerm != NULL )
			delete RightPrimaryTerm;
		
	}
	else
	{
		
		if ( RightOperatorTerm != NULL )
			delete RightOperatorTerm;
		
	}
	
	RightOperatorTerm = RightTerm;
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
		
		if ( RightOperatorTerm != NULL )
			delete RightOperatorTerm;
		
	}
	
	RightPrimaryTerm = RightTerm;
	RightIsPrimary = true;
	
}

IOilOperator * OilBinaryOperator :: GetLeftTermAsOperator () const
{
	
	return LeftIsPrimary ? NULL : LeftOperatorTerm;
	
}

IOilPrimary * OilBinaryOperator :: GetLeftTermAsPrimary () const
{
	
	return LeftIsPrimary ? LeftPrimaryTerm : NULL;
	
}

IOilOperator * OilBinaryOperator :: GetRightTermAsOperator () const
{
	
	return RightIsPrimary ? NULL : RightOperatorTerm;
	
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
		LeftOperatorTerm = NULL;
	
	if ( RightIsPrimary )
		RightPrimaryTerm = NULL;
	else
		RightOperatorTerm = NULL;
	
}

IOilOperator :: OperatorType OilBinaryOperator :: GetOperatorType () const
{
	
	return kOperatorType_Binary;
	
}

bool OilBinaryOperator :: IsLeftPrimary () const
{
	
	return LeftIsPrimary;
	
}

bool OilBinaryOperator :: IsRightPrimary () const
{
	
	return RightIsPrimary;
	
}

const std :: string & OilBinaryOperator :: GetOpName () const
{
	
	if ( Op > MaxOpString )
		return UnknownOpString;
	
	return OperatorStrings [ Op ];
	
}

const SourceRef & OilBinaryOperator :: GetSourceRef () const
{
	
	return Ref;
	
}
