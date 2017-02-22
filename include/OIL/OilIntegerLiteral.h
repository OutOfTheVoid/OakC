#ifndef OIL_OILLITERAL_H
#define OIL_OILLITERAL_H

#include <IOilPrimary.h>

class OilIntegerLiteral : public virtual IOilPrimary
{
public:
	
	typedef struct
	{
		
		kIntType_Explicit_U8 = 0x00,
		kIntType_Explicit_U16 = 0x01,
		kIntType_Explicit_U32 = 0x02,
		kIntType_Explicit_U64 = 0x03,
		kIntType_Explicit_I8 = 0x04,
		kIntType_Explicit_I16 = 0x05,
		kIntType_Explicit_I32 = 0x06,
		kIntType_Explicit_I64 = 0x07,
		
		kIntType_Flag_Implied = 0x10,
		
		kIntType_Implied_MinI8 = 0x10,
		kIntType_Implied_MinI16 = 0x11,
		kIntType_Implied_MinI32 = 0x12,
		kIntType_Implied_MinI64 = 0x13,
		kIntType_Implied_MinU8 = 0x14,
		kIntType_Implied_MinU16 = 0x15,
		kIntType_Implied_MinU32 = 0x16,
		kIntType_Implied_MinU64 = 0x17,
		
	} IntType;
	
	OilIntegerLiteral ( IntType Type, uint64_t UValue );
	OilIntegerLiteral ( IntType Type, int64_t SValue );
	
	void Set ( IntType Type, uint64_t UValue );
	void Set ( IntType Type, int64_t SValue );
	
	uint64_t GetUValue () const;
	int64_t GetSValue () const;
	
	IntType GetType () const;
	
	bool IsConstant () const;
	
private:
	
	union
	{
		
		uint64_t UValue;
		uint64_t IValue;
		
	};
	
	IntType Type;
	
};

#endif
