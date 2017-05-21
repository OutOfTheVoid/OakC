#ifndef OIL_OILFLOATLITERAL_H
#define OIL_OILFLOATLITERAL_H

#include <Math/BigFloat.h>

#include <OIL/IOilPrimary.h>

#include <Tokenization/SourceRef.h>

class OilFloatLiteral : public virtual IOilPrimary
{
public:
	
	typedef enum
	{
		
		kFloatType_Indeterminate,
		kFloatType_32,
		kFloatType_64
		
	} FloatType;
	
	OilFloatLiteral ( const SourceRef & Ref, const BigFloat & Value, FloatType Type );
	~OilFloatLiteral ();
	
	void SetValue ( const BigFloat & Value, FloatType Type );
	
	const BigFloat & GetValue () const;
	
	FloatType GetType () const;
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	BigFloat Value;
	
	FloatType Type;
	
	SourceRef Ref;
	
};

#endif
