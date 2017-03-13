#ifndef OIL_OILEXPRESSION_H
#define OIL_OILEXPRESSION_H

#include <OIL/IOilPrimary.h>
#include <OIL/IOilStatement.h>

class IOilOperator;

class OilExpression : public virtual IOilPrimary, public virtual IOilStatement
{
public:
	
	OilExpression ( IOilPrimary * Primary );
	OilExpression ( IOilOperator * Operator );
	~OilExpression ();
	
	bool IsPrimary () const;
	
	IOilOperator * GetTermAsOperator () const;
	IOilPrimary * GetTermAsPrimary () const;
	
	void SetTerm ( IOilOperator * Operator );
	void SetTerm ( IOilPrimary * Primary );
	
	void DisownTerm ();
	
	bool IsConstant () const;
	
	StatementType GetStatementType () const;
	PrimaryType GetPrimaryType () const;
	
private:
	
	bool TermIsPrimary;
	
	union
	{
		
		IOilOperator * OperatorTerm;
		IOilPrimary * PrimaryTerm;
		
	};
	
};

#endif
