#ifndef OIL_OILUNARYOPERATOR_H
#define OIL_OILUNARYOPERATOR_H

#include <OIL/IOilOperator.h>

class OilExpression;
class IOilPrimary;

class OilUnaryOperator : public virtual IOilOperator
{
public:
	
	typedef enum
	{
		
		kOperator_RangeConstruction,
		kOperator_PostfixIncrement,
		kOperator_PostfixDecrement,
		kOperator_PrefixIncrement,
		kOperator_PrefixDecrement,
		kOperator_BitwiseNot,
		kOperator_LogicalNot,
		kOperator_UnaryNegative,
		kOperator_UnaryPositive,
		kOperator_AddressOfRef,
		kOperator_Dereference,
		kOperator_ArrayAccess,
		kOperator_FunctionCall,
		
	} Operator;
	
	OilUnaryOperator ( Operator Op, OilExpression * Term );
	OilUnaryOperator ( Operator Op, IOilPrimary * Term );
	
	~OilUnaryOperator ();
	
	OilExpression * GetTermAsExpression () const;
	IOilPrimary * GetTermAsPrimary () const;
	
	void SetTerm ( OilExpression * Term );
	void SetTerm ( IOilPrimary * Term );
	
	Operator GetOp () const;
	
	bool ConstantTerms () const;
	OperatorType GetOperatorType () const;
	
	void DisownTerm ();
	
private:
	
	Operator Op;
	
	bool TermIsPrimary;
	
	union
	{
		
		IOilPrimary * PrimaryTerm;
		OilExpression * ExpressionTerm;
		
	};
	
};

#endif
