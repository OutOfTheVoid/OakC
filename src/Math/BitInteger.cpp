#include <Math/BigInteger.h>
#include <math.h>

BigInteger :: BigInteger ( int64_t Value ):
	Sign ( Value >= 0 ),
	BitCount ( 64 ),
	Data ()
{
	
	if ( Value == INT64_MIN )
		Data.push_back ( 0x8000000000000000 );
	else
		Data.push_back ( Sign ? Value : - Value );
	
}

BigInteger :: BigInteger ( std :: initializer_list <uint64_t> WordData, bool Sign ):
	Sign ( Sign ),
	BitCount ( WordData.size () * 64 ),
	Data ( WordData )
{
}

BigInteger :: BigInteger ( const BigInteger & Value ):
	Sign ( Value.Sign ),
	BitCount ( Value.BitCount ),
	Data ( Value.Data )
{
}

void BigInteger :: Set ( std :: initializer_list <uint64_t> WordData, bool Sign )
{
	
	Data.assign ( WordData );
	
	this -> Sign = Sign;
	this -> BitCount = WordData.size () * 64;
	
}

void BigInteger :: Set ( int64_t RValue )
{
	
	Data.resize ( 1 );
	
	Sign = RValue >= 0;
	
	if ( RValue == INT64_MIN )
		Data [ 0 ] = 0x8000000000000000ULL;
	else
		Data [ 0 ] = Sign ? RValue : - RValue;
	
	BitCount = 64;
	
}

void BigInteger :: Set ( const BigInteger & Value )
{
	
	Data = Value.Data;
	Sign = Value.Sign;
	BitCount = Value.BitCount;
}

BigInteger :: ~BigInteger ()
{
}

BigInteger & BigInteger :: operator= ( int64_t RValue )
{
	
	Data.resize ( 1 );
	
	Sign = RValue >= 0;
	
	if ( RValue == INT64_MIN )
		Data [ 0 ] = 0x8000000000000000ULL;
	else
		Data [ 0 ] = Sign ? RValue : - RValue;
	
	BitCount = 64;
	
	return * this;
	
}

void BigInteger :: TruncateRep ()
{
	
	for ( uint64_t I = Data.size () - 1; I != 0; I -- )
	{
		
		if ( Data [ I ] != 0 )
		{
			
			Data.resize ( I + 1 );
			
			BitCount = 64 * ( I + 1 );
			
			break;
			
		}
		
	}
	
}

uint64_t BigInteger :: Get64Bits ( uint64_t BitOffset ) const
{
	
	uint64_t WordOffsetLow = BitOffset & 0x3F;
	uint64_t WordIndexLow = BitOffset >> 6;
	
	if ( WordIndexLow >= Data.size () )
		return 0;
	
	if ( WordOffsetLow == 0 )
	{
		
		if ( WordIndexLow >= Data.size () )
			return 0;
		
		return Data [ WordIndexLow ];
		
	}
	
	uint64_t WordIndexHigh = WordIndexLow + 1;
	uint64_t WordPortionLow = 64 - WordOffsetLow;
	
	if ( WordIndexHigh >= Data.size () )
		return Data [ WordIndexLow ] >> WordOffsetLow;
	
	return ( Data [ WordIndexLow ] >> WordOffsetLow ) | ( Data [ WordIndexHigh ] << WordPortionLow );
	
}

inline bool BigInteger :: GetBit ( uint64_t Position ) const
{
	
	uint64_t Major = Position >> 6;
	uint64_t Minor = Position & 0x3F;
	
	if ( Major > Data.size () )
		return false;
	
	return ( ( Data [ Major ] >> Minor ) & 1ULL ) != 0;
	
}

inline void BigInteger :: SetBit ( uint64_t Position, bool Value )
{
	
	uint64_t Major = Position >> 6;
	uint64_t Minor = Position & 0x3F;
	
	if ( Major >= Data.size () )
	{
		
		if ( ! Value )
			return;
		
		uint64_t SDiff = ( Major + 1 ) - Data.size ();
		
		Data.insert ( Data.end (), SDiff, 0ULL );
		
		BitCount = ( Major + 1 ) * 64;
		
	}
	
	if ( Value )
		Data [ Major ] |= 1ULL << Minor;
	else
		Data [ Major ] &= ~ ( 1ULL << Minor );
	
}

void BigInteger :: ForceWordCount ( uint64_t Count )
{
	
	if ( Count > Data.size () )
	{
		
		uint64_t SDiff = Count - Data.size ();
		
		Data.insert ( Data.end (), SDiff, 0ULL );
		
		BitCount = Count * 64;
		
	}
	
}

void BigInteger :: FlipSign ()
{
	
	Sign = ! Sign;
	
}

bool BigInteger :: GetSign () const
{
	
	return Sign;
	
}

void BigInteger :: Add ( int64_t RValue )
{
	
	BigInteger BigRValue ( RValue );
	Subtract ( BigRValue );
	
}

void BigInteger :: Add ( const BigInteger & RValue )
{
	
	if ( RValue.Sign == Sign )
		AddMagnitude ( RValue );
	else
	{
		
		if ( Sign )
		{
			
			SubtractMagnitude ( RValue, Sign );
			Sign = ! Sign;
			
		}
		else
			SubtractMagnitude ( RValue, Sign );
		
	}
	
}

void BigInteger :: AddMagnitude ( const BigInteger & RValue )
{
	
	bool Carry = false;
	
	uint64_t I;
	
	for ( I = 0; I < RValue.BitCount; I ++ )
	{
		
		bool A = GetBit ( I );
		bool B = RValue.GetBit ( I );
		
		if ( Carry )
		{
			
			if ( A )
			{
				
				if ( ! B )
					SetBit ( I, false );
				
			}
			else
			{
				
				if ( ! B )
				{
					
					SetBit ( I, true );
					
					Carry = false;
					
				}
				
			}
			
		}
		else
		{
			
			if ( A )
			{
				
				if ( B )
				{
					
					SetBit ( I, false );
					
					Carry = true;
					
				}
				
			}
			else
			{
				
				if ( B )
					SetBit ( I, true );
				
			}
			
		}
		
	}
	
	while ( Carry )
	{
		
		if ( GetBit ( I ) )
			SetBit ( I, false );
		else
		{
			
			SetBit ( I, true );
			
			return;
			
		}
		
		I ++;
		
	}
	
}

void BigInteger :: SubtractMagnitude ( const BigInteger & RValue, bool & Negative )
{
	
	BigInteger Subtractant ( RValue );
	
	if ( Subtractant.Data.size () < Data.size () )
		Subtractant.ForceWordCount ( Data.size () );
	else if ( Data.size () < Subtractant.Data.size () )
		ForceWordCount ( Subtractant.Data.size () );
	
	uint64_t DataSize = Data.size ();
	
	Subtractant.BinaryNOT ();
	Subtractant.Increment ();
	
	AddMagnitude ( Subtractant );
	
	if ( Data.size () != DataSize )
	{
		
		Data.pop_back ();
		BitCount -= 64;
		
	}
	
	Negative = GetBit ( BitCount - 1 );
	SetBit ( BitCount - 1, false );
	
}

void BigInteger :: RightSubtractMagnitude ( const BigInteger & RValue )
{
	
	(void) RValue;
	
}

void BigInteger :: Subtract ( int64_t Value )
{
	
	BigInteger BigRValue ( Value );
	Subtract ( BigRValue );
	
}

void BigInteger :: Subtract ( const BigInteger & RValue )
{
	
	if ( Sign != RValue.Sign )
		AddMagnitude ( RValue );
	else
	{
		
		if ( Sign )
		{
			
			SubtractMagnitude ( RValue, Sign );
			Sign = ! Sign;
			
		}
		else
			SubtractMagnitude ( RValue, Sign );
		
	}
	
}

void BigInteger :: RightSubtract ( int64_t Value )
{
	
	BigInteger BigRValue ( Value );
	RightSubtract ( BigRValue );
	
}

void BigInteger :: RightSubtract ( const BigInteger & RValue )
{
	
	FlipSign ();
	Add ( RValue );
	
}

void BigInteger :: Multiply ( int64_t RValue )
{
	
	BigInteger BigRValue ( RValue );
	Multiply ( BigRValue );
	
}

void BigInteger :: Multiply ( const BigInteger & RValue )
{
	
	if ( RValue == 0LL )
	{
		
		Set ( 0 );
		
		return;
		
	}
	
	if ( RValue == 1LL )
		return;
	
	BigInteger SelfCopy ( * this );
	Set ( 0 );
	
	for ( uint64_t I = 0; I < RValue.BitCount; I ++ )
	{
		
		if ( RValue.GetBit ( I ) )
			Add ( SelfCopy );
		
		if ( I != ( RValue.BitCount - 1 ) )
			SelfCopy.LeftShift ( 1ULL );
		
	}
	
}

void BigInteger :: LeftShift ( uint64_t Count )
{
	
	if ( Count == 0 )
		return;
	
	uint64_t I = BitCount;
	
	do
	{
		
		I --;
		SetBit ( I + Count, GetBit ( I ) );
		
	}
	while ( I != 0 );
	
	I = Count;
	
	do
	{
		
		I --;
		SetBit ( I, false );
		
	}
	while ( I != 0 );
	
}

void BigInteger :: RightShift ( uint64_t Count )
{
	
	if ( Count >= BitCount )
	{
		
		Set ( 0 );
		
		return;
		
	}
	
	for ( uint64_t I = 0; I < BitCount; I ++ )
		SetBit ( I, GetBit ( I + Count ) );
	
}

void BigInteger :: BinaryNOT ()
{
	
	for ( uint64_t I = 0; I < Data.size (); I ++ )
		Data [ I ] = ~ Data [ I ];
	
}

void BigInteger :: BinaryOR ( const BigInteger & RValue )
{
	
	uint64_t MinSize = RValue.Data.size () < Data.size () ? RValue.Data.size () : Data.size ();
	
	for ( uint64_t I = 0; I < MinSize; I ++ )
		Data [ I ] |= RValue.Data [ I ];
	
	for ( uint64_t I = Data.size (); I < RValue.Data.size (); I ++ )
		Data.push_back ( RValue.Data [ I ] );
	
	BitCount = Data.size () * 64;
	
}

void BigInteger :: BinaryXOR ( const BigInteger & RValue )
{
	
	uint64_t MinSize = RValue.Data.size () < Data.size () ? RValue.Data.size () : Data.size ();
	
	for ( uint64_t I = 0; I < MinSize; I ++ )
		Data [ I ] ^= RValue.Data [ I ];
	
	for ( uint64_t I = Data.size (); I < RValue.Data.size (); I ++ )
		Data.push_back ( RValue.Data [ I ] );
	
	BitCount = Data.size () * 64;
	
}

void BigInteger :: BinaryAND ( const BigInteger & RValue )
{
	
	uint64_t MinSize = RValue.Data.size () < Data.size () ? RValue.Data.size () : Data.size ();
	
	for ( uint64_t I = 0; I < MinSize; I ++ )
		Data [ I ] &= RValue.Data [ I ];
	
	if ( MinSize < Data.size () )
		Data.resize ( MinSize );
	
	BitCount = MinSize * 64;
	
}

void BigInteger :: Increment ()
{
	
	uint64_t I = 0;
	
	while ( I < BitCount )
	{
		
		if ( GetBit ( I ) )
			SetBit ( I, false );
		else
		{
			
			SetBit ( I, true );
			
			return;
			
		}
		
		I ++;
		
	}
	
	SetBit ( I, true );
	
}

void BigInteger :: Decrement ()
{
	
	bool Carry = true;
	
	for ( uint64_t I = 0; Carry && ( I < BitCount ); I ++ )
	{
		
		if ( Carry && ( ! GetBit ( I ) ) )
			SetBit ( I, true );
		else
		{
			
			if ( Carry )
				SetBit ( I, false );
			
			return;
			
		}
		
	}
	
}

int64_t BigInteger :: GetValue64 () const
{
	
	return Sign ? Data [ 0 ] : - static_cast <int64_t> ( Data [ 0 ] );
	
}

uint64_t BigInteger :: GetMagnitude64 () const
{
	
	return Data [ 0 ];
	
}

bool BigInteger :: operator== ( int64_t RValue ) const
{
	
	return Equal ( RValue );
	
}

bool BigInteger :: operator== ( const BigInteger & RValue ) const
{
	
	return Equal ( RValue );
	
}

bool BigInteger :: Equal ( int64_t Value ) const
{
	
	if ( Value < 0 )
	{
		
		if ( Sign )
			return false;
		
	}
	else if ( Value != 0 )
	{
		
		if ( ! Sign )
			return false;
		
	}
	
	if ( Data [ 0 ] != static_cast <uint64_t> ( Value ) )
		return false;
	
	for ( uint64_t I = 1; I < Data.size (); I ++ )
		if ( Data [ I ] != 0ULL )
			return false;
		
	return true;
	
}

bool BigInteger :: Equal ( const BigInteger & Value ) const
{
	
	if ( Value.Sign != Sign )
		return false;
	
	uint64_t Count = Value.Data.size () < Data.size () ? Value.Data.size () : Data.size ();
	
	for ( uint64_t I = 0; I < Count; I ++ )
		if ( Value.Data [ I ] != Data [ I ] )
			return false;
		
	if ( Value.Data.size () < Data.size () )
	{
		
		for ( uint64_t I = Count; I < Data.size (); I ++ )
			if ( Data [ I ] != 0 )
				return false;
		
	}
	else if ( Value.Data.size () > Data.size () )
	{
		
		for ( uint64_t I = Count; I < Value.Data.size (); I ++ )
			if ( Value.Data [ I ] != 0 )
				return false;
		
	}
	
	return true;
	
}

uint64_t BigInteger :: GetRepSizeBits () const
{
	
	return Data.size () * 64;
	
}

uint64_t BigInteger :: GetOrder2 () const
{
	
	return log2 ( Data.size () ) + 7;
	
}
