#include <EarlyAnalysis/OilDecorators.h>

bool IsSimpleDecoratorWithID ( const OilDecoratorTag * Decorator, const std :: u32string & ID )
{
	
	return ( Decorator -> GetID () == ID ) && ( Decorator -> GetKind () == OilDecoratorTag :: kTagKind_Simple );
	
}

bool IsParametric1DecoratorWithID ( const OilDecoratorTag * Decorator, const std :: u32string & ID, std :: u32string & Param1Out )
{
	
	if ( ( Decorator -> GetKind () != OilDecoratorTag :: kTagKind_Parametric_1 ) || ( Decorator -> GetID () != ID ) )
		return false;
	
	Param1Out = Decorator -> GetParam1 ();
	
	return true;
	
}

bool IsConditionalCompilationDecorator ( const OilDecoratorTag * Decorator )
{
	
	return Decorator -> GetID () == kDecoratorID_ConditionalCompilation_KeepIf;
	
}

bool TestConditionalCompilationDecorators ( const OilDecoratorTag ** Decorators, uint32_t DecoratorCount, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount )
{
	
	for ( uint32_t I = 0; I < DecoratorCount; I ++ )
	{
		
		std :: u32string Condition;
		
		if ( IsParametric1DecoratorWithID ( Decorators [ I ], kDecoratorID_ConditionalCompilation_KeepIf, Condition ) )
		{
			
			for ( uint32_t J = 0; J < CompilationConditionCount; J ++ )
			{
				
				if ( Condition == CompilationConditions [ J ] )
					return true;
				
			}
			
		}
		
	}
	
	return false;
	
}
