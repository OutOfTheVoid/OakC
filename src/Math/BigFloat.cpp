#include <Math/BigFloat.h>

BigFloat :: BigFloat ( const BigInteger & Significand, int64_t Power10, int64_t Power2 ):
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

void BigFloat :: Add ( const BigFloat & RValue )
{
	
	BigFloat Temporary ( RValue );
	
	// Take significands to same power 10 and 2
	if ( Temporary.Power10 < Power10 )
	{
		
		while ( Temporary.Power10 < Power10 )
		{
			
			Significand *= 10LL;
			Power10 --;
			
		}
		
	}
	else if ( Temporary.Power10 > Power10 )
	{
		
		while ( Temporary.Power10 > Power10 )
		{
			
			Temporary.Significand *= 10LL;
			Temporary.Power10 --;
			
		}
		
	}
	
	if ( Temporary.Power2 < Power2 )
	{
		
		while ( Temporary.Power2 < Power2 )
		{
			
			Significand <<= 2;
			Power2 --;
			
		}
		
	}
	else if ( Temporary.Power2 > Power2 )
	{
		
		while ( Temporary.Power2 > Power2 )
		{
			
			Temporary.Significand <<= 2;
			Temporary.Power2 --;
			
		}
		
	}
	
	Significand += Temporary.Significand;
	
}

void BigFloat :: Subtract ( const BigFloat & RValue )
{
	
	BigFloat Temporary ( RValue );
	
	// Take significands to same powers
	if ( Temporary.Power10 < Power10 )
	{
		
		while ( Temporary.Power10 < Power10 )
		{
			
			Significand *= 10LL;
			Power10 --;
			
		}
		
	}
	else if ( Temporary.Power10 > Power10 )
	{
		
		while ( Temporary.Power10 > Power10 )
		{
			
			Temporary.Significand *= 10LL;
			Temporary.Power10 --;
			
		}
		
	}
	
	if ( Temporary.Power2 < Power2 )
	{
		
		while ( Temporary.Power2 < Power2 )
		{
			
			Significand <<= 2;
			Power2 --;
			
		}
		
	}
	else if ( Temporary.Power2 > Power2 )
	{
		
		while ( Temporary.Power2 > Power2 )
		{
			
			Temporary.Significand <<= 2;
			Temporary.Power2 --;
			
		}
		
	}
	
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
	
	// Take significands to same powers
	if ( Temporary.Power10 < Power10 )
	{
		
		while ( Temporary.Power10 < Power10 )
		{
			
			Significand *= 10LL;
			Power10 --;
			
		}
		
	}
	else if ( Temporary.Power10 > Power10 )
	{
		
		while ( Temporary.Power10 > Power10 )
		{
			
			Temporary.Significand *= 10LL;
			Temporary.Power10 --;
			
		}
		
	}
	
	if ( Temporary.Power2 < Power2 )
	{
		
		while ( Temporary.Power2 < Power2 )
		{
			
			Significand <<= 2;
			Power2 --;
			
		}
		
	}
	else if ( Temporary.Power2 > Power2 )
	{
		
		while ( Temporary.Power2 > Power2 )
		{
			
			Temporary.Significand <<= 2;
			Temporary.Power2 --;
			
		}
		
	}
	
	Significand <<= BIGFLOAT_DIVIDE_POWER2_PRECISIONEXPANSION;
	Power2 -= BIGFLOAT_DIVIDE_POWER2_PRECISIONEXPANSION;
	
	Power2 -= Temporary.Power2;
	Power10 -= Temporary.Power10;
	Significand /= Temporary.Significand;
	
}
