#ifndef OIL_OILBINARYOPERATOR_H
#define OIL_OILBINARYOPERATOR_H

#include <OIL/IOilOperator.h>

class IOilPrimary;

class OilBinaryOperator : public virtual IOilOperator
{
public:
	
	typedef enum
	{
		
		kOperator_DirectMemberAccess,
		kOperator_IndirectMemberAccess,
		kOperator_Multiply,
		kOperator_Divide,
		kOperator_Modulus,
		kOperator_Addition,
		kOperator_Subtraction,
		kOperator_ShiftLeft,
		kOperator_LogicalShiftRight,
		kOperator_ArithmeticShiftRight,
		kOperator_GreaterThan,
		kOperator_LessThan,
		kOperator_GreaterThanOrEqual,
		kOperator_LessThanOrEqual,
		kOperator_NotEqual,
		kOperator_Equal,
		kOperator_BitwiseAnd,
		kOperator_BitwiseXor,
		kOperator_BitwiseOr,
		kOperator_LogicalAnd,
		kOperator_LogicalOr,
		kOperator_Assignment,
		kOperator_CompoundMultiply,
		kOperator_CompoundDivide,
		kOperator_CompoundModulus,
		kOperator_CompoundAddition,
		kOperator_CompoundSubtraction,
		kOperator_CompoundShiftLeft,
		kOperator_CompoundLogicalShiftRight,
		kOperator_CompoundArithmeticShiftRight,
		kOperator_CompoundBitwiseAnd,
		kOperator_CompoundBitwiseOr,
		kOperator_CompoundBitwiseXor,
		
	} Operator;
	
	OilBinaryOperator ( Operator Op, IOilOperator * LeftTerm, IOilOperator * RightTerm );
	OilBinaryOperator ( Operator Op, IOilOperator * LeftTerm, IOilPrimary * RightTerm );
	OilBinaryOperator ( Operator Op, IOilPrimary * LeftTerm, IOilOperator * RightTerm );
	OilBinaryOperator ( Operator Op, IOilPrimary * LeftTerm, IOilPrimary * RightTerm );
	
	~OilBinaryOperator ();
	
	IOilOperator * GetLeftTermAsExpression () const;
	IOilPrimary * GetLeftTermAsPrimary () const;
	IOilOperator * GetRightTermAsExpression () const;
	IOilPrimary * GetRightTermAsPrimary () const;
	
	bool IsLeftPrimary () const;
	bool IsRightPrimary () const;
	
	void SetLeftTerm ( IOilOperator * LeftTerm );
	void SetLeftTerm ( IOilPrimary * LeftTerm );
	void SetRightTerm ( IOilOperator * RightTerm );
	void SetRightTerm ( IOilPrimary * RightTerm );
	
	Operator GetOp () const;
	
	bool ConstantTerms () const;
	OperatorType GetOperatorType () const;
	
	void DisownTerms ();
	
private:
	
	Operator Op;
	
	bool LeftIsPrimary;
	bool RightIsPrimary;
	
	union
	{
		
		IOilOperator * LeftOperatorTerm;
		IOilPrimary * LeftPrimaryTerm;
		
	};
	
	union
	{
		
		IOilOperator * RightOperatorTerm;
		IOilPrimary * RightPrimaryTerm;
		
	};
	
};

#endif
