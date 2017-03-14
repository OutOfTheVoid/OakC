#ifndef OIL_OILBINDINGSTATEMENT_H
#define OIL_OILBINDINGSTATEMENT_H

#include <OIL/IOilStatement.h>

#include <string>

class OilTypeRef;
class OilExpression;

class OilBindingStatement : public virtual IOilStatement
{
public:
	
	OilBindingStatement ( const std :: u32string & Name, bool Public, bool Mutable, OilTypeRef * Type );
	OilBindingStatement ( const std :: u32string & Name, bool Public, bool Mutable, OilTypeRef * Type, OilExpression * InitializerValue );
	~OilBindingStatement ();
	
	const std :: u32string & GetName () const;
	
	const OilTypeRef * GetType () const;
	OilTypeRef * GetType ();
	
	const OilExpression * GetInitializerValue () const;
	OilExpression * GetInitializerValue ();
	
	bool HasInitializer () const;
	
	void DropInitializer ();
	
	bool IsMutable () const;
	bool IsPublic () const;
	
	StatementType GetStatementType () const;
	
private:
	
	const std :: u32string Name;
	
	bool Mutable;
	bool Public;
	
	OilTypeRef * Type;
	OilExpression * InitializerValue;
	
};

#endif
