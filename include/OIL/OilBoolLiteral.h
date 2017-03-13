#ifndef OIL_OILBOOLLITERAL_H
#define OIL_OILBOOLLITERAL_H

#include <OIL/IOilPrimary.h>

class OilBoolLiteral : public virtual IOilPrimary
{
public:
	
	OilBoolLiteral ( bool Value );
	~OilBoolLiteral ();
	
	bool GetValue () const;
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
private:
	
	bool Value;
	
};

#endif
