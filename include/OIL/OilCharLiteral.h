#ifndef OIL_OILCHARLITERAL_H
#define OIL_OILCHARLITERAL_H

#include <OIL/IOilPrimary.h>

#include <Tokenization/SourceRef.h>

class OilCharLiteral : public virtual IOilPrimary
{
public:
	
	OilCharLiteral ( const SourceRef & Ref, char32_t Value );
	~OilCharLiteral ();
	
	char32_t GetValue () const;
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	char32_t Value;
	
	SourceRef Ref;
	
};

#endif
