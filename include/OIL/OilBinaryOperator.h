#ifndef OIL_OILBINARYOPERATOR_H
#define OIL_OILBINARYOPERATOR_H

#include <OIL/IOilOperator.h>

#include <string>

#include <Tokenization/SourceRef.h>

class IOilPrimary;

class OilBinaryOperator : public virtual IOilOperator
{
public:
	
	typedef enum
	{
		
		kOperator_DirectMemberAccess = 0,
		kOperator_IndirectMemberAccess = 1,
		kOperator_Multiply = 2,
		kOperator_Divide = 3,
		kOperator_Modulus = 4,
		kOperator_Addition = 5,
		kOperator_Subtraction = 6,
		kOperator_ShiftLeft = 7,
		kOperator_LogicalShiftRight = 8,
		kOperator_ArithmeticShiftRight = 9,
		kOperator_GreaterThan = 10,
		kOperator_LessThan = 11,
		kOperator_GreaterThanOrEqual = 12,
		kOperator_LessThanOrEqual = 13,
		kOperator_NotEqual = 14,
		kOperator_Equal = 15,
		kOperator_BitwiseAnd = 16,
		kOperator_BitwiseXor = 17,
		kOperator_BitwiseOr = 18,
		kOperator_LogicalAnd = 19,
		kOperator_LogicalOr = 20,
		kOperator_Assignment = 21,
		kOperator_CompoundMultiply = 22,
		kOperator_CompoundDivide = 23,
		kOperator_CompoundModulus = 24,
		kOperator_CompoundAddition = 25,
		kOperator_CompoundSubtraction = 26,
		kOperator_CompoundShiftLeft = 27,
		kOperator_CompoundLogicalShiftRight = 28,
		kOperator_CompoundArithmeticShiftRight = 29,
		kOperator_CompoundBitwiseAnd = 30,
		kOperator_CompoundBitwiseOr = 31,
		kOperator_CompoundBitwiseXor = 32,
		kOperator_CompoundLogicalAnd = 33,
		kOperator_CompoundLogicalOr = 34,
		
	} Operator;
	
	OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilOperator * LeftTerm, IOilOperator * RightTerm );
	OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilOperator * LeftTerm, IOilPrimary * RightTerm );
	OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilPrimary * LeftTerm, IOilOperator * RightTerm );
	OilBinaryOperator ( const SourceRef & Ref, Operator Op, IOilPrimary * LeftTerm, IOilPrimary * RightTerm );
	
	~OilBinaryOperator ();
	
	IOilOperator * GetLeftTermAsOperator () const;
	IOilPrimary * GetLeftTermAsPrimary () const;
	IOilOperator * GetRightTermAsOperator () const;
	IOilPrimary * GetRightTermAsPrimary () const;
	
	bool IsLeftPrimary () const;
	bool IsRightPrimary () const;
	
	void SetLeftTerm ( IOilOperator * LeftTerm );
	void SetLeftTerm ( IOilPrimary * LeftTerm );
	void SetRightTerm ( IOilOperator * RightTerm );
	void SetRightTerm ( IOilPrimary * RightTerm );
	
	Operator GetOp () const;
	
	const std :: string & GetOpName () const;
	
	bool ConstantTerms () const;
	OperatorType GetOperatorType () const;
	
	void DisownTerms ();
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	static const std :: string OperatorStrings [];
	static const uint32_t MaxOpString;
	static const std :: string UnknownOpString;
	
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
	
	SourceRef Ref;
	
};

#endif
