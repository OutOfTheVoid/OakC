#ifndef OIL_OILUNARYOPERATOR_H
#define OIL_OILUNARYOPERATOR_H

#include <OIL/IOilOperator.h>

#include <string>

class OilExpression;
class IOilPrimary;

class OilUnaryOperator : public virtual IOilOperator
{
public:
	
	typedef enum
	{
		
		kOperator_PostfixIncrement,
		kOperator_PostfixDecrement,
		kOperator_PrefixIncrement,
		kOperator_PrefixDecrement,
		kOperator_BitwiseNot,
		kOperator_LogicalNot,
		kOperator_UnaryNegative,
		kOperator_UnaryPositive,
		kOperator_Reference,
		kOperator_Dereference,
		kOperator_ArrayAccess,
		kOperator_FunctionCall,
		
	} Operator;
	
	OilUnaryOperator ( Operator Op, IOilOperator * Term );
	OilUnaryOperator ( Operator Op, IOilPrimary * Term );
	
	~OilUnaryOperator ();
	
	IOilOperator * GetTermAsOperator () const;
	IOilPrimary * GetTermAsPrimary () const;
	
	void SetTerm ( IOilOperator * Term );
	void SetTerm ( IOilPrimary * Term );
	
	Operator GetOp () const;
	
	const std :: string & GetOpName () const;
	
	bool ConstantTerms () const;
	OperatorType GetOperatorType () const;
	
	bool IsTermPrimary () const;
	
	void DisownTerm ();
	
private:
	
	static const std :: string OperatorStrings [];
	static const uint32_t MaxOpString;
	static const std :: string UnknownOpString;
	
	Operator Op;
	
	bool TermIsPrimary;
	
	union
	{
		
		IOilPrimary * PrimaryTerm;
		IOilOperator * OperatorTerm;
		
	};
	
};

#endif
