#ifndef OIL_OILLITERAL_H
#define OIL_OILLITERAL_H

#include <OIL/IOilPrimary.h>

#include <stdint.h>

class OilIntegerLiteral : public virtual IOilPrimary
{
public:
	
	typedef enum
	{
		
		kIntType_Explicit_I8 = 0x00,
		kIntType_Explicit_I16 = 0x01,
		kIntType_Explicit_I32 = 0x02,
		kIntType_Explicit_I64 = 0x03,
		kIntType_Explicit_U8 = 0x04,
		kIntType_Explicit_U16 = 0x05,
		kIntType_Explicit_U32 = 0x06,
		kIntType_Explicit_U64 = 0x07,
		
		kIntType_Flag_Implied = 0x10,
		
		kIntType_Implied_MinI8 = 0x10,
		kIntType_Implied_MinI16 = 0x11,
		kIntType_Implied_MinI32 = 0x12,
		kIntType_Implied_MinI64 = 0x13,
		kIntType_Implied_MinU8 = 0x14,
		kIntType_Implied_MinU16 = 0x15,
		kIntType_Implied_MinU32 = 0x16,
		//kIntType_Implied_MinU64 = 0x17,
		
		kIntType_Flag_ValidIfNegative = 0x20,
		
		kIntType_Explicit_I8_IfNegative = 0x20,
		kIntType_Explicit_I16_IfNegative = 0x21,
		kIntType_Explicit_I32_IfNegative = 0x22,
		kIntType_Explicit_I64_IfNegative = 0x23,
		
		kIntType_Implied_MinI8_IfNegative = 0x30,
		kIntType_Implied_MinI16_IfNegative = 0x31,
		kIntType_Implied_MinI32_IfNegative = 0x32,
		kIntType_Implied_MinI64_IfNegative = 0x33,
		
		kIntType_Indeterminate_MinI8 = 0x40,
		kIntType_Indeterminate_MinI16 = 0x41,
		kIntType_Indeterminate_MinI32 = 0x42,
		kIntType_Indeterminate_MinI64 = 0x43,
		
		kIntType_Indeterminate_MinI8_IfNegative = 0x60,
		kIntType_Indeterminate_MinI16_IfNegative = 0x61,
		kIntType_Indeterminate_MinI32_IfNegative = 0x62,
		kIntType_Indeterminate_MinI64_IfNegative = 0x63,
		
	} IntType;
	
	OilIntegerLiteral ( IntType Type, uint64_t UValue );
	OilIntegerLiteral ( IntType Type, int64_t SValue );
	
	void Set ( IntType Type, uint64_t UValue );
	void Set ( IntType Type, int64_t SValue );
	
	uint64_t GetUValue () const;
	int64_t GetSValue () const;
	
	IntType GetType () const;
	
	bool IsConstant () const;
	PrimaryType GetPrimaryType () const;
	
private:
	
	union
	{
		
		uint64_t UValue;
		int64_t SValue;
		
	};
	
	IntType Type;
	
};

#endif
