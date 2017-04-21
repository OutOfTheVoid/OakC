#include <EarlyAnalysis/OakDecorators.h>

bool IsSimpleDecoratorWithID ( const OilDecoratorTag * Decorator, const std :: u32string & ID )
{
	
	return ( Decorator -> GetID () == ID );
	
}
