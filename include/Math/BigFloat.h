#ifndef MATH_BIGFLOAT_H
#define MATH_BIGFLOAT_H

#include <Math/BigInteger.h>

class BigFloat
{
public:
	
	explicit BigFloat ( const BigInteger & Significand, int64_t Power10, int64_t Power2 );
	explicit BigFloat ( const BigInteger & Significand, int64_t Power2 );
	explicit BigFloat ( const BigFloat & CopyFrom );
	
	~BigFloat ();
	
	bool IsFractional () const;
	bool HasPower10Component () const;
	
	const BigInteger & GetSignificand () const;
	int64_t GetPower10 () const;
	int64_t GetPower2 () const;
	
	void Add ( const BigFloat & RValue );
	void Subtract ( const BigFloat & RValue );
	void Multiply ( const BigFloat & RValue );
	void Divide ( const BigFloat & RValue );
	
private:
	
	BigInteger Significand;
	
	int64_t Power10;
	int64_t Power2;
	
};

#endif
