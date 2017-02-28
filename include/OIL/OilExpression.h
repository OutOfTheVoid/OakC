#ifndef OIL_OILEXPRESSION_H
#define OIL_OILEXPRESSION_H

#include <OIL/IOilPrimary.h>

class IOilOperator;

class OilExpression : public virtual IOilPrimary
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
	
	bool IsConstant ();
	
private:
	
	bool TermIsPrimary;
	
	union
	{
		
		IOilOperator * OperatorTerm;
		IOilPrimary * PrimaryTerm;
		
	};
	
};

#endif
