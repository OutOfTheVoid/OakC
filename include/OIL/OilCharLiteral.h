#ifndef OIL_OILCHARLITERAL_H
#define OIL_OILCHARLITERAL_H

#include <OIL/IOilPrimary.h>

class OilCharLiteral : public virtual IOilPrimary
{
public:
	
	OilCharLiteral ( char32_t Value );
	~OilCharLiteral ();
	
	char32_t GetValue () const;
	
	bool IsConstant () const;
	
private:
	
	char32_t Value;
	
};

#endif
