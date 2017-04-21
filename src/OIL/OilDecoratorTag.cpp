#include <OIL/OilDecoratorTag.h>

OilDecoratorTag :: OilDecoratorTag ( const std :: u32string & ID ):
	ID ( ID )
{
}

OilDecoratorTag :: ~OilDecoratorTag ()
{
}

const std :: u32string & OilDecoratorTag :: GetID () const
{
	
	return ID;
	
}
