#ifndef OIL_OILARRAYLITERAL_H
#define OIL_OILARRAYLITERAL_H

#include <OIL/IOilPrimary.h>

#include <stdint.h>
#include <vector>

class OilTypeRef;

class OilArrayLiteral : public virtual IOilPrimary
{
public:
	
	OilArrayLiteral ();
	OilArrayLiteral ( IOilPrimary * CountExpression );
	OilArrayLiteral ( IOilPrimary * CountExpression, OilTypeRef * TypeSpecifier );
	OilArrayLiteral ( OilTypeRef * TypeSpecifier );
	OilArrayLiteral ( IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount );
	OilArrayLiteral ( IOilPrimary * CountExpression, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount );
	OilArrayLiteral ( IOilPrimary * CountExpression, OilTypeRef * TypeSpecifier, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount );
	OilArrayLiteral ( OilTypeRef * TypeSpecifier, IOilPrimary ** MemberInitializerExpressions, uint64_t ValueCount );
	
	~OilArrayLiteral ();
	
	bool HasSpecificCount () const;
	bool HasTypeSpecifier () const;
	bool HasMemberInitiailizers () const;
	
	const OilTypeRef * GetTypeSpecifier () const;
	OilTypeRef * GetTypeSpecifier ();
	
	const IOilPrimary * GetCountExpression () const;
	IOilPrimary * GetCountExpression ();
	
	uint64_t GetMemberInitializerCount () const;
	
	const IOilPrimary * GetMemberInitializer ( uint64_t Index ) const;
	IOilPrimary * GetMemberInitializer ( uint64_t Index );
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
private:
	
	IOilPrimary * CountExpression;
	
	OilTypeRef * TypeSpecifier;
	
	std :: vector <IOilPrimary *> MemberInitializerExpressions;
	
};

#endif
