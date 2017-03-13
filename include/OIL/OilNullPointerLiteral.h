#ifndef OIL_OILNULLPOINTERLITERAL_H
#define OIL_OILNULLPOINTERLITERAL_H

#include <OIL/IOilPrimary.h>

class OilNullPointerLiteral : public virtual IOilPrimary
{
public:
	
	OilNullPointerLiteral ();
	~OilNullPointerLiteral ();
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
};

#endif
