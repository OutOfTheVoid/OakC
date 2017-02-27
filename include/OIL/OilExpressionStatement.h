#ifndef OIL_OILEXPRESSIONSTATEMENT_H
#define OIL_OILEXPRESSIONSTATEMENT_H

class OilExpression;

class OilExpressionStatement
{
public:
	
	OilExpressionStatement ( OilExpression * Expression );
	~OilExpressionStatement ();
	
	OilExpression * GetExpression ();
	const OilExpression * GetExpression () const;
	
	void DisownExpression ();
	
private:
	
	OilExpression * Expression;
	
};

#endif
