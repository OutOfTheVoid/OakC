#include <OIL/OilDecoratorTag.h>

OilDecoratorTag :: OilDecoratorTag ( const SourceRef & Ref, const std :: u32string & ID ):
	ID ( ID ),
	Param1 ( U"" ),
	Ref ( Ref ),
	Kind ( kTagKind_Simple )
{
}

OilDecoratorTag :: OilDecoratorTag ( const SourceRef & Ref, const std :: u32string & ID, const std :: u32string & Param1 ):
	ID ( ID ),
	Param1 ( Param1 ),
	Ref ( Ref ),
	Kind ( kTagKind_Parametric_1 )
{
	
	
	
}

OilDecoratorTag :: ~OilDecoratorTag ()
{
}

OilDecoratorTag :: TagKind OilDecoratorTag :: GetKind () const
{
	
	return Kind;
	
}

const std :: u32string & OilDecoratorTag :: GetID () const
{
	
	return ID;
	
}

const std :: u32string & OilDecoratorTag :: GetParam1 () const
{
	
	return Param1;
	
}

const SourceRef & OilDecoratorTag :: GetSourceRef () const
{
	
	return Ref;
	
}
