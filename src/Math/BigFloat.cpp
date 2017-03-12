#include <Math/BigFloat.h>

#include <Logging/Logging.h>

BigFloat :: BigFloat ( const BigInteger & Significand, int64_t Power2, int64_t Power10 ):
	Significand ( Significand ),
	Power10 ( Power10 ),
	Power2 ( Power2 )
{
}

BigFloat :: BigFloat ( const BigInteger & Significand, int64_t Power2 ):
	Significand ( Significand ),
	Power10 ( 0 ),
	Power2 ( Power2 )
{
}


BigFloat :: BigFloat ( const BigFloat & CopyFrom ):
	Significand ( CopyFrom.Significand ),
	Power10 ( CopyFrom.Power10 ),
	Power2 ( CopyFrom.Power2 )
{
}

BigFloat :: ~BigFloat ()
{
}

void BigFloat :: Set ( const BigInteger & Significand, int64_t Power2, int64_t Power10 )
{
	
	this -> Significand = Significand;
	this -> Power10 = Power10;
	this -> Power2 = Power2;
	
}

void BigFloat :: Set ( const BigInteger & Significand, int64_t Power2 )
{
	
	this -> Significand = Significand;
	this -> Power10 = 0LL;
	this -> Power2 = Power2;
	
}

void BigFloat :: Set ( const BigInteger & Significand )
{
	
	this -> Significand = Significand;
	this -> Power10 = 0LL;
	this -> Power2 = 0LL;
	
}

void BigFloat :: Set ( const BigFloat & CopyFrom )
{
	
	this -> Significand = CopyFrom.Significand;
	this -> Power10 = CopyFrom.Power10;
	this -> Power2 = CopyFrom.Power2;
	
}

void BigFloat :: operator = ( const BigFloat & Value )
{
	
	Set ( Value );
	
}

void BigFloat :: operator = ( const BigInteger & Value )
{
	
	Set ( Value );
	
}

void BigFloat :: operator = ( int64_t Value )
{
	
	Set ( BigInteger ( Value ) );
	
}

bool BigFloat :: IsFractional () const
{
	
	return ( Power10 < 0 ) || ( ( Power2 < ( - Power10 ) ) && ( Power2 != 0 ) );
	
}

bool BigFloat :: HasPower10Component () const
{
	
	return Power10 < 0;
	
}

const BigInteger & BigFloat :: GetSignificand () const
{
	
	return Significand;
	
}

int64_t BigFloat :: GetPower10 () const
{
	
	return Power10;
	
}

int64_t BigFloat :: GetPower2 () const
{
	
	return Power2;
	
}

void BigFloat :: MatchScale ( BigFloat & Other )
{
	
	if ( Other.Power10 < Power10 )
	{
		
		LOG_VERBOSE ( std :: string ( "MS: 0, P10: " ) + std :: to_string ( Power10 ) + " O_P10: " + std :: to_string ( Other.Power10 ) );
		
		while ( Other.Power10 < Power10 )
		{
			
			Significand *= 10LL;
			Power10 --;
			
		}
		
	}
	else if ( Other.Power10 > Power10 )
	{
		
		LOG_VERBOSE ( std :: string ( "MS: 1, P10: " ) + std :: to_string ( Power10 ) + " O_P10: " + std :: to_string ( Other.Power10 ) );
		
		while ( Other.Power10 > Power10 )
		{
			
			Other.Significand *= 10LL;
			Other.Power10 --;
			
		}
		
	}
	
	if ( Other.Power2 < Power2 )
	{
		
		LOG_VERBOSE ( std :: string ( "MS: 2, P2: " ) + std :: to_string ( Power2 ) + " O_P2: " + std :: to_string ( Other.Power2 ) );
		
		while ( Other.Power2 < Power2 )
		{
			
			Significand <<= 1;
			Power2 --;
			
		}
		
	}
	else if ( Other.Power2 > Power2 )
	{
		
		LOG_VERBOSE ( std :: string ( "MS: 3, P2: " ) + std :: to_string ( Power2 ) + " O_P2: " + std :: to_string ( Other.Power2 ) );
		
		while ( Other.Power2 > Power2 )
		{
			
			Other.Significand <<= 1;
			Other.Power2 --;
			
		}
		
	}
	
	LOG_VERBOSE ( "MS: R" );
	
}

void BigFloat :: Add ( const BigFloat & RValue )
{
	
	BigFloat Temporary ( RValue );
	MatchScale ( Temporary );
	
	Significand += Temporary.Significand;
	
}

void BigFloat :: Subtract ( const BigFloat & RValue )
{
	
	BigFloat Temporary ( RValue );
	MatchScale ( Temporary );
	
	Significand -= Temporary.Significand;
	
}

void BigFloat :: Multiply ( const BigFloat & RValue )
{
	
	Significand *= RValue.Significand;
	Power2 += RValue.Power2;
	Power10 += RValue.Power10;
	
}

#define BIGFLOAT_DIVIDE_POWER2_PRECISIONEXPANSION 128

void BigFloat :: Divide ( const BigFloat & RValue )
{
	
	BigFloat Temporary ( RValue );
	MatchScale ( Temporary );
	
	int64_t TopBit = static_cast <int64_t> ( Temporary.Significand.GetTopSetBit () ) + BIGFLOAT_DIVIDE_POWER2_PRECISIONEXPANSION;
	
	Significand <<= TopBit;
	Power2 -= TopBit;
	
	Power2 -= Temporary.Power2;
	Power10 -= Temporary.Power10;
	Significand /= Temporary.Significand;
	
}

bool BigFloat :: Equal ( const BigFloat & RValue )
{
	
	LOG_VERBOSE ( "EQ: A" );
	
	BigFloat Temporary ( RValue );
	
	LOG_VERBOSE ( "EQ: B" );
	
	MatchScale ( Temporary );
	
	LOG_VERBOSE ( "EQ: C" );
	
	return Temporary.Significand == Significand;
	
}
