#ifndef FLOATINGPOINT_BIGINTEGER_H
#define FLOATINGPOINT_BIGINTEGER_H

#include <vector>
#include <stdint.h>
#include <string>

#include <initializer_list>

class BigInteger
{
public:
	
	static const bool kSign_Positive = true;
	static const bool kSign_Negative = false;
	
	explicit BigInteger ( std :: initializer_list <uint64_t> WordData, bool Sign );
	BigInteger ( int64_t Value );
	BigInteger ( const BigInteger & Value );
	~BigInteger ();
	
	BigInteger & operator = ( int64_t RValue );
	
	bool operator == ( int64_t RValue ) const;
	bool operator == ( const BigInteger & RValue ) const;
	bool operator != ( int64_t RValue ) const;
	bool operator != ( const BigInteger & RValue ) const;
	
	bool operator > ( int64_t RValue ) const;
	bool operator > ( const BigInteger & RValue ) const;
	bool operator >= ( int64_t RValue ) const;
	bool operator >= ( const BigInteger & RValue ) const;
	
	bool operator < ( int64_t RValue ) const;
	bool operator < ( const BigInteger & RValue ) const;
	bool operator <= ( int64_t RValue ) const;
	bool operator <= ( const BigInteger & RValue ) const;
	
	void operator += ( int64_t RValue );
	void operator += ( const BigInteger & RValue );
	void operator -= ( int64_t RValue );
	void operator -= ( const BigInteger & RValue );
	
	void operator >>= ( int64_t RValue );
	void operator >>= ( const BigInteger & RValue );
	void operator <<= ( int64_t RValue );
	void operator <<= ( const BigInteger & RValue );
	
	void operator *= ( int64_t RValue );
	void operator *= ( const BigInteger & RValue );
	void operator /= ( int64_t RValue );
	void operator /= ( const BigInteger & RValue );
	
	void operator |= ( int64_t RValue );
	void operator |= ( const BigInteger & RValue );
	void operator &= ( int64_t RValue );
	void operator &= ( const BigInteger & RValue );
	void operator ^= ( int64_t RValue );
	void operator ^= ( const BigInteger & RValue );
	
	void Set ( std :: initializer_list <uint64_t> WordData, bool Sign );
	void Set ( int64_t Value );
	void Set ( const BigInteger & Value );
	
	void TruncateRep ();
	
	void Absolute ();
	void FlipSign ();
	bool GetSign () const;
	
	void Add ( int64_t RValue );
	void Add ( const BigInteger & RValue );
	void Subtract ( int64_t Value );
	void Subtract ( const BigInteger & RValue );
	void RightSubtract ( int64_t Value );
	void RightSubtract ( const BigInteger & RValue );
	void Multiply ( int64_t RValue );
	void Multiply ( const BigInteger & RValue );
	bool Divide ( int64_t RValue );
	bool Divide ( const BigInteger & RValue );
	
	void BinaryNOT ();
	
	void Increment ();
	void Decrement ();
	
	void BinaryOR ( const BigInteger & RValue );
	void BinaryOR ( uint64_t RValue );
	void BinaryXOR ( const BigInteger & RValue );
	void BinaryXOR ( uint64_t RValue );
	void BinaryAND ( const BigInteger & RValue );
	void BinaryAND ( uint64_t RValue );
	
	void LeftShift ( uint64_t Count );
	void RightShift ( uint64_t Count );
	
	bool Equal ( const BigInteger & RValue ) const;
	bool Equal ( int64_t Value ) const;
	
	bool GreaterThan ( int64_t Value ) const;
	bool GreaterThan ( const BigInteger & RValue ) const;
	
	bool LessThan ( int64_t Value ) const;
	bool LessThan ( const BigInteger & RValue ) const;
	
	uint64_t GetTopSetBit () const;
	uint64_t GetRepSizeBits () const;
	uint64_t GetOrder2 () const;
	
	uint64_t Get64Bits ( uint64_t BitOffset ) const;
	int64_t GetValue64 () const;
	uint64_t GetMagnitude64 () const;
	
	inline bool GetBit ( uint64_t Position ) const;
	inline void SetBit ( uint64_t Position, bool Value );
	
	std :: string ToHexString () const;
	
private:
	
	void ForceWordCount ( uint64_t Count );
	void AddMagnitude ( const BigInteger & RValue );
	void SubtractMagnitude ( const BigInteger & RValue, bool & Negative );
	void RightSubtractMagnitude ( const BigInteger & RValue );
	
	bool Sign;
	
	uint64_t BitCount;
	std :: vector <uint64_t> Data;
	
};

#endif