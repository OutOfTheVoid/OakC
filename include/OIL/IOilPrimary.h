#ifndef OIL_IOILPRIMARY_H
#define OIL_IOILPRIMARY_H

class IOilPrimary
{
public:
	
	typedef enum
	{
		
		kPrimaryType_BoolLiteral,
		kPrimaryType_IntegerLiteral,
		kPrimaryType_FloatLiteral,
		kPrimaryType_StringLiteral,
		kPrimaryType_CharLiteral,
		kPrimaryType_ArrayLiteral,
		kPrimaryType_StructLiteral,
		kPrimaryType_NullPointerLiteral,
		kPrimaryType_Expression,
		kPrimaryType_Allusion,
		
	} PrimaryType;
	
	inline virtual ~IOilPrimary () {};
	
	virtual bool IsConstant () const = 0;
	virtual PrimaryType GetPrimaryType () const = 0;
	
};

#endif
