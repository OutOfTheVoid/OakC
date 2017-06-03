#ifndef OIL_OILUNARYOPERATOR_H
#define OIL_OILUNARYOPERATOR_H

#include <OIL/IOilOperator.h>

#include <string>

#include <Tokenization/SourceRef.h>

class OilExpression;
class IOilPrimary;
class OilFunctionCallParameterList;

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
	
	OilUnaryOperator ( const SourceRef & Ref, Operator Op, IOilOperator * Term );
	OilUnaryOperator ( const SourceRef & Ref, Operator Op, IOilPrimary * Term );
	OilUnaryOperator ( const SourceRef & Ref, IOilOperator * Term, OilFunctionCallParameterList * ParameterList );
	OilUnaryOperator ( const SourceRef & Ref, IOilPrimary * Term, OilFunctionCallParameterList * ParameterList );
	
	~OilUnaryOperator ();
	
	const IOilOperator * GetTermAsOperator () const;
	IOilOperator * GetTermAsOperator ();
	
	const IOilPrimary * GetTermAsPrimary () const;
	IOilPrimary * GetTermAsPrimary ();
	
	const OilFunctionCallParameterList * GetFunctionCallParameterList () const;
	OilFunctionCallParameterList * GetFunctionCallParameterList ();
	
	void SetTerm ( IOilOperator * Term );
	void SetTerm ( IOilPrimary * Term );
	
	Operator GetOp () const;
	
	const std :: string & GetOpName () const;
	
	bool ConstantTerms () const;
	OperatorType GetOperatorType () const;
	
	bool IsTermPrimary () const;
	
	void DisownTerm ();
	
	const SourceRef & GetSourceRef () const;
	
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
	
	OilFunctionCallParameterList * ParameterList;
	
	SourceRef Ref;
	
};

#endif
