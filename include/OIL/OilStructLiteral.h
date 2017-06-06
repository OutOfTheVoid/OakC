#ifndef OIL_OILSTRUCTLITERAL_H
#define OIL_OILSTRUCTLITERAL_H

#include <string>

#include <OIL/IOilPrimary.h>

#include <Tokenization/SourceRef.h>

class OilTypeRef;
class OilStructInitializerValue;

class OilStructLiteral : public virtual IOilPrimary
{
public:
	
	OilStructLiteral ( const SourceRef & Ref, OilTypeRef * LiteralType, OilStructInitializerValue ** InitializerValues, uint32_t InitializerValueCount );
	~OilStructLiteral ();
	
	const OilTypeRef * GetLiteralType () const;
	OilTypeRef * GetLiteralType ();
	
	uint32_t GetMemberValueCount () const;
	
	const OilStructInitializerValue * GetInitializerValue ( uint32_t Index ) const;
	OilStructInitializerValue * GetInitializerValue ( uint32_t Index );
	
	bool IsConstant () const;
	
	PrimaryType GetPrimaryType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	OilTypeRef * LiteralType;
	
	uint32_t InitializerValueCount;
	OilStructInitializerValue ** InitializerValues;
	
	const SourceRef Ref;
	
};

#endif
