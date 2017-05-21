#ifndef OIL_OILRETURN_H
#define OIL_OILRETURN_H

#include <OIL/IOilStatement.h>

#include <Tokenization/SourceRef.h>

class OilExpression;

class OilReturn : public virtual IOilStatement
{
public:
	
	OilReturn ( const SourceRef & Ref, OilExpression * ReturnedExpression );
	OilReturn ( const SourceRef & Ref );
	~OilReturn ();
	
	const OilExpression * GetReturnedExpression () const;
	OilExpression * GetReturnedExpression ();
	
	bool HasExpression () const;
	
	StatementType GetStatementType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilExpression * ReturnedExpression;
	
	SourceRef Ref;
	
};

#endif
