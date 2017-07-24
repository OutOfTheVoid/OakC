#ifndef OIL_OILUNARYOPERATOR_H
#define OIL_OILUNARYOPERATOR_H

#include <OIL/IOilOperator.h>

#include <string>

#include <Tokenization/SourceRef.h>

class OilExpression;
class IOilPrimary;
class OilFunctionCallParameterList;
class OilTemplateSpecification;
class OilTypeRef;

class OilUnaryOperator : public virtual IOilOperator
{
public:
	
	typedef enum
	{
		
		kOperator_PostfixIncrement = 0,
		kOperator_PostfixDecrement = 1,
		kOperator_PrefixIncrement = 2,
		kOperator_PrefixDecrement = 3,
		kOperator_BitwiseNot = 4,
		kOperator_LogicalNot = 5,
		kOperator_UnaryNegative = 6,
		kOperator_UnaryPositive = 7,
		kOperator_Reference = 8,
		kOperator_Dereference = 9,
		kOperator_ArrayAccess = 10,
		kOperator_FunctionCall = 11,
		kOperator_MemberAccess = 12,
		kOperator_TraitCast = 13,
		
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
	
	// TODO: Add data slot for typeref for trait cast
	
	OilUnaryOperator ( const SourceRef & Ref, IOilOperator * Term, OilTypeRef * CastTrait );
	OilUnaryOperator ( const SourceRef & Ref, IOilPrimary * Term, OilTypeRef * CastTrait );
	
	~OilUnaryOperator ();
	
	const IOilOperator * GetTermAsOperator () const;
	IOilOperator * GetTermAsOperator ();
	
	const IOilPrimary * GetTermAsPrimary () const;
	IOilPrimary * GetTermAsPrimary ();
	
	const OilFunctionCallParameterList * GetFunctionCallParameterList () const;
	OilFunctionCallParameterList * GetFunctionCallParameterList ();
	
	const OilTypeRef * GetCastTraitRef () const;
	OilTypeRef * GetCastTraitRef ();
	
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
		OilTypeRef * CastTrait;
		
	};
	
	const std :: u32string MemberAccessName;
	
	SourceRef Ref;
	
};

#endif
