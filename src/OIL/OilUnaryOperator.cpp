#include <OIL/OilUnaryOperator.h>
#include <OIL/IOilPrimary.h>
#include <OIL/OilExpression.h>

#ifndef NULL
	#define NULL nullptr
#endif

const std :: string OilUnaryOperator :: OperatorStrings [] =
{
	
	"increment_postfix",
	"decrement_postfix",
	"increment_prefix",
	"decrement_prefix",
	"bitwise_not",
	"logical_not",
	"unary_negative",
	"unary_positive",
	"address_of_or_reference",
	"dereference",
	"array_access",
	"function_call",
	
};

const uint32_t OilUnaryOperator :: MaxOpString = 11;

const std :: string OilUnaryOperator :: UnknownOpString = "UNKOWN_OP";

OilUnaryOperator :: OilUnaryOperator ( const SourceRef & Ref, Operator Op, IOilOperator * Term ):
	Op ( Op ),
	TermIsPrimary ( false ),
	OperatorTerm ( Term ),
	ParameterList ( NULL ),
	Ref ( Ref )
{
}
	
OilUnaryOperator :: OilUnaryOperator ( const SourceRef & Ref, Operator Op, IOilPrimary * Term ):
	Op ( Op ),
	TermIsPrimary ( true ),
	PrimaryTerm ( Term ),
	ParameterList ( NULL ),
	Ref ( Ref )
{
}

OilUnaryOperator :: OilUnaryOperator ( const SourceRef & Ref, IOilOperator * Term, OilFunctionCallParameterList * ParameterList ):
	Op ( kOperator_FunctionCall ),
	TermIsPrimary ( false ),
	OperatorTerm ( Term ),
	ParameterList ( ParameterList ),
	Ref ( Ref )
{
}

OilUnaryOperator :: OilUnaryOperator ( const SourceRef & Ref, IOilPrimary * Term, OilFunctionCallParameterList * ParameterList ):
	Op ( kOperator_FunctionCall ),
	TermIsPrimary ( true ),
	PrimaryTerm ( Term ),
	ParameterList ( ParameterList ),
	Ref ( Ref )
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

const IOilOperator * OilUnaryOperator :: GetTermAsOperator () const
{
	
	return TermIsPrimary ? NULL : OperatorTerm;
	
}


const IOilPrimary * OilUnaryOperator :: GetTermAsPrimary () const
{
	
	return TermIsPrimary ? PrimaryTerm : NULL;
	
}

IOilOperator * OilUnaryOperator :: GetTermAsOperator ()
{
	
	return TermIsPrimary ? NULL : OperatorTerm;
	
}


IOilPrimary * OilUnaryOperator :: GetTermAsPrimary ()
{
	
	return TermIsPrimary ? PrimaryTerm : NULL;
	
}

const OilFunctionCallParameterList * OilUnaryOperator :: GetFunctionCallParameterList () const
{
	
	return ParameterList;
	
}

OilFunctionCallParameterList * OilUnaryOperator :: GetFunctionCallParameterList ()
{
	
	return ParameterList;
	
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

const std :: string & OilUnaryOperator :: GetOpName () const
{
	
	if ( Op > MaxOpString )
		return UnknownOpString;
	
	return OperatorStrings [ Op ];
	
}

const SourceRef & OilUnaryOperator :: GetSourceRef () const
{
	
	return Ref;
	
}
