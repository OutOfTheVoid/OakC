#ifndef OIL_OILSTRUCTDESTRUCTURE_H
#define OIL_OILSTRUCTDESTRUCTURE_H

#include <Tokenization/SourceRef.h>

#include <vector>

class OilTypeRef;
class OilMemberDestructure;

class OilStructDestructure
{
public:
	
	OilStructDestructure ( const SourceRef & Ref );
	~OilStructDestructure ();
	
	bool IsDestructuredTypeResolved () const;
	
	void SetDestructuredType ( OilTypeRef * Ref );
	
	const OilTypeRef * GetDestructuredType () const;
	OilTypeRef * GetDestructuredType ();
	
	uint32_t GetMemberDestructureCount () const;
	
	void AddMemberDestructure ( OilMemberDestructure * Member );
	
	const OilMemberDestructure * GetMemberDestructure ( uint32_t Index ) const;
	OilMemberDestructure * GetMemberDestructure ( uint32_t Index );
	
	const SourceRef & GetSourceRef () const;

private:
	
	const SourceRef Ref;
	
	std :: vector <OilMemberDestructure *> DestructuredMembers;
	
	OilTypeRef * StructType;
	
};

#endif
