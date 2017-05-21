#ifndef OIL_OILNULLPOINTERLITERAL_H
#define OIL_OILNULLPOINTERLITERAL_H

#include <OIL/IOilPrimary.h>

#include <Tokenization/SourceRef.h>

class OilNullPointerLiteral : public virtual IOilPrimary
{
public:
	
	OilNullPointerLiteral ( const SourceRef & Ref );
	~OilNullPointerLiteral ();
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	SourceRef Ref;
	
};

#endif
