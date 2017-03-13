#ifndef OIL_OILFLOATLITERAL_H
#define OIL_OILFLOATLITERAL_H

#include <Math/BigFloat.h>

#include <OIL/IOilPrimary.h>

class OilFloatLiteral : public virtual IOilPrimary
{
public:
	
	typedef enum
	{
		
		kFloatType_Indeterminate,
		kFloatType_32,
		kFloatType_64
		
	} FloatType;
	
	OilFloatLiteral ( const BigFloat & Value, FloatType Type );
	~OilFloatLiteral ();
	
	void SetValue ( const BigFloat & Value, FloatType Type );
	
	const BigFloat & GetValue () const;
	
	FloatType GetType ();
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
private:
	
	BigFloat Value;
	
	FloatType Type;
	
};

#endif
