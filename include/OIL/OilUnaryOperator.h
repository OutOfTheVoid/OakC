#ifndef OIL_OILUNARYOPERATOR_H
#define OIL_OILUNARYOPERATOR_H

#include <OIL/IOilOperator.h>

#include <string>

#include <Tokenization/SourceRef.h>

class OilExpression;
class IOilPrimary;
class OilFunctionCallParameterList;
class OilTemplateSpecification;

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
		kOperator_MemberAccess,
		
	} Operator;
	
	OilUnaryOperator ( const SourceRef & Ref, Operator Op, IOilOperator * Term );
	OilUnaryOperator ( const SourceRef & Ref, Operator Op, IOilPrimary * Term );
	OilUnaryOperator ( const SourceRef & Ref, IOilOperator * Term, OilFunctionCallParameterList * ParameterList );
	OilUnaryOperator ( const SourceRef & Ref, IOilPrimary * Term, OilFunctionCallParameterList * ParameterList );
	
	// Member access
	OilUnaryOperator ( const SourceRef & Ref, IOilOperator * Term, const std :: u32string & MemberName );
	OilUnaryOperator ( const SourceRef & Ref, IOilPrimary * Term, const std :: u32string & MemberName );
	OilUnaryOperator ( const SourceRef & Ref, IOilOperator * Term, const std :: u32string & MemberName, OilTemplateSpecification * MemberTemplateSpec );
	OilUnaryOperator ( const SourceRef & Ref, IOilPrimary * Term, const std :: u32string & MemberName, OilTemplateSpecification * MemberTemplateSpec );
	
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
	
	const std :: u32string & GetNameForMemberAccess () const;
	
	const OilTemplateSpecification * GetTemplateSpecificationForMemberAccess () const;
	OilTemplateSpecification * GetTemplateSpecificationForMemberAccess ();
	
	bool IsMemberAccessTempalted () const;
	
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
	
	union
	{
		
		OilFunctionCallParameterList * ParameterList;
		OilTemplateSpecification * MemberTemplateSpec;
		
	};
	
	const std :: u32string MemberAccessName;
	
	SourceRef Ref;
	
};

#endif
