#ifndef OIL_OILEXPRESSION_H
#define OIL_OILEXPRESSION_H

class IOilOperator;
class IOilPrimary;

class OilExpression
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
	
private:
	
	bool TermIsPrimary;
	
	union
	{
		
		IOilOperator * OperatorTerm;
		IOilPrimary * PrimaryTerm;
		
	};
	
};

#endif
