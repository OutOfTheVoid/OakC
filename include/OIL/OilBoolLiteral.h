#ifndef OIL_OILBOOLLITERAL_H
#define OIL_OILBOOLLITERAL_H

#include <OIL/IOilPrimary.h>

#include <Tokenization/SourceRef.h>

class OilBoolLiteral : public virtual IOilPrimary
{
public:
	
	OilBoolLiteral ( const SourceRef & Ref, bool Value );
	~OilBoolLiteral ();
	
	bool GetValue () const;
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	bool Value;
	
	SourceRef Ref;
	
};

#endif
