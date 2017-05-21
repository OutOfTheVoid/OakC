#ifndef OIL_OILSTRINGLITERAL_H
#define OIL_OILSTRINGLITERAL_H

#include <OIL/IOilPrimary.h>

#include <string>

#include <Tokenization/SourceRef.h>

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
	
	OilStringLiteral ( const SourceRef & Ref, EncodingType Type, const std :: u32string & Value );
	~OilStringLiteral ();
	
	void SetType ( EncodingType Type );
	EncodingType GetType () const;
	
	const std :: u32string GetValue () const;
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	EncodingType Type;
	
	const std :: u32string Value;
	
	SourceRef Ref;
	
};

#endif
