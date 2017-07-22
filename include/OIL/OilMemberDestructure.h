#ifndef OIL_OILMEMBERDESTRUCTURE_H
#define OIL_OILMEMBERDESTRUCTURE_H

#include <Tokenization/SourceRef.h>

#include <string>

class OilStructDestructure;
class OilTypeRef;

class OilMemberDestructure
{
public:
	
	OilMemberDestructure ( const SourceRef & Ref, const std :: u32string & MemberName );// Ignored member
	OilMemberDestructure ( const SourceRef & Ref, const std :: u32string & MemberName, const std :: u32string ValueName );
	OilMemberDestructure ( const SourceRef & Ref, const std :: u32string & MemberName, OilStructDestructure * SubDestructure );
	
	~OilMemberDestructure ();
	
	const std :: u32string & GetMemberName () const;
	
	bool IsIgnored () const;
	bool IsSubDestructure () const;
	
	const std :: u32string & GetValueName () const;
	
	const OilStructDestructure * GetSubDestructure () const;
	OilStructDestructure * GetSubDestructure ();
	
	bool IsDestructuredTypeResolved () const;
	
	void SetDestructuredType ( OilTypeRef * Ref );
	
	const OilTypeRef * GetDestructuredType () const;
	OilTypeRef * GetDestructuredType ();
	
	const SourceRef & GetSourceRef () const;

private:
	
	const SourceRef Ref;
	
	bool Ignored;
	
	const std :: u32string MemberName;
	const std :: u32string ValueName;
	
	OilStructDestructure * SubDestructure;
	
	OilTypeRef * DestructureType;
	
};

#endif
