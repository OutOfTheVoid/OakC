#ifndef OIL_OILRETURN_H
#define OIL_OILRETURN_H

#include <OIL/IOilStatement.h>

class OilExpression;

class OilReturn : public virtual IOilStatement
{
public:
	
	OilReturn ( OilExpression * ReturnedExpression );
	OilReturn ();
	~OilReturn ();
	
	const OilExpression * GetReturnedExpression () const;
	OilExpression * GetReturnedExpression ();
	
	bool HasExpression () const;
	
	StatementType GetStatementType () const;
	
private:
	
	OilExpression * ReturnedExpression;
	
};

#endif
