#ifndef OIL_OILBINDINGSTATEMENT_H
#define OIL_OILBINDINGSTATEMENT_H

#include <OIL/IOilStatement.h>

#include <string>

#include <Tokenization/SourceRef.h>

class OilTypeRef;
class OilExpression;

class OilBindingStatement : public virtual IOilStatement
{
public:
	
	OilBindingStatement ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Mutable, OilTypeRef * Type );
	OilBindingStatement ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Mutable, OilTypeRef * Type, OilExpression * InitializerValue );
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
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string Name;
	
	bool Mutable;
	bool Public;
	
	OilTypeRef * Type;
	OilExpression * InitializerValue;
	
	SourceRef Ref;
	
};

#endif
