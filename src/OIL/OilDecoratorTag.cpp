#include <OIL/OilDecoratorTag.h>

OilDecoratorTag :: OilDecoratorTag ( const SourceRef & Ref, const std :: u32string & ID ):
	ID ( ID ),
	Ref ( Ref )
{
}

OilDecoratorTag :: ~OilDecoratorTag ()
{
}

const std :: u32string & OilDecoratorTag :: GetID () const
{
	
	return ID;
	
}

const SourceRef & OilDecoratorTag :: GetSourceRef () const
{
	
	return Ref;
	
}
