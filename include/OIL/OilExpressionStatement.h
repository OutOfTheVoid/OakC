#ifndef OIL_OILEXPRESSIONSTATEMENT_H
#define OIL_OILEXPRESSIONSTATEMENT_H

#include <Tokenization/SourceRef.h>

class OilExpression;

class OilExpressionStatement
{
public:
	
	OilExpressionStatement ( const SourceRef & Ref, OilExpression * Expression );
	~OilExpressionStatement ();
	
	OilExpression * GetExpression ();
	const OilExpression * GetExpression () const;
	
	void DisownExpression ();
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilExpression * Expression;
	
	SourceRef Ref;
	
};

#endif
