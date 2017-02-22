#ifndef OIL_OILBINARYOPERATOR_H
#define OIL_OILBINARYOPERATOR_H

#include <OIL/IOilOperator.h>

class OilExpression;
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
	
	OilBinaryOperator ( Operator Op, OilExpression * LeftTerm, OilExpression * RightTerm );
	OilBinaryOperator ( Operator Op, OilExpression * LeftTerm, IOilPrimary * RightTerm );
	OilBinaryOperator ( Operator Op, IOilPrimary * LeftTerm, OilExpression * RightTerm );
	OilBinaryOperator ( Operator Op, IOilPrimary * LeftTerm, IOilPrimary * RightTerm );
	
	~OilBinaryOperator ();
	
	OilExpression * GetLeftTermAsExpression () const;
	IOilPrimary * GetLeftTermAsPrimary () const;
	OilExpression * GetRightTermAsExpression () const;
	IOilPrimary * GetRightTermAsPrimary () const;
	
	void SetLeftTerm ( OilExpression * LeftTerm );
	void SetLeftTerm ( IOilPrimary * LeftTerm );
	void SetRightTerm ( OilExpression * RightTerm );
	void SetRightTerm ( IOilPrimary * RightTerm );
	
	Operator GetOp () const;
	
	bool ConstantTerms () const;
	OperatorType GetOperatorType () const;
	
	void DisownTerms ();
	
private:
	
	bool LeftIsPrimary;
	bool RightIsPrimary;
	
	union
	{
		
		OilExpression * LeftExpressionTerm;
		IOilPrimary * LeftPrimaryTerm;
		
	};
	
	union
	{
		
		OilExpression * RightExpressionTerm;
		IOilPrimary * RightPrimaryTerm;
		
	};
	
	Operator Op;
	
};

#endif
