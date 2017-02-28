#ifndef OIL_OILSTRINGLITERAL_H
#define OIL_OILSTRINGLITERAL_H

#include <OIL/IOilPrimary.h>

#include <string>

class OilStringLiteral : public virtual IOilPrimary
{
public:
	
	typedef enum
	{
		
		kEncodingType_UTF8,
		kEncodingType_UTF16,
		kEncodingType_UTF32,
		kEncodingType_Indeterminate
		
	} EncodingType;
	
	OilStringLiteral ( EncodingType Type, const std :: u32string & Value );
	~OilStringLiteral ();
	
	void SetType ( EncodingType Type );
	EncodingType GetType () const;
	
	const std :: u32string GetValue () const;
	
	bool IsConstant () const;
	
private:
	
	EncodingType Type;
	
	const std :: u32string Value;
	
};

#endif
