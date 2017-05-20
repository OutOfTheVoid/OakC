#ifndef OIL_OILCONSTSTATEMENT_H
#define OIL_OILCONSTSTATEMENT_H

#include <OIL/IOilStatement.h>

#include <string>

class OilTypeRef;
class OilExpression;

class OilConstStatement : public virtual IOilStatement
{
public:
	
	OilConstStatement ( const std :: u32string & Name, bool Public, OilTypeRef * Type, OilExpression * InitializerValue );
	~OilConstStatement ();
	
	const std :: u32string & GetName () const;
	
	const OilTypeRef * GetType () const;
	OilTypeRef * GetType ();
	
	const OilExpression * GetInitializerValue () const;
	OilExpression * GetInitializerValue ();
	
	void DropInitializer ();
	
	bool IsPublic () const;
	
	StatementType GetStatementType () const;
	
private:
	
	const std :: u32string Name;
	
	bool Public;
	
	OilTypeRef * Type;
	OilExpression * InitializerValue;
	
};

#endif
