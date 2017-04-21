#ifndef OIL_OILDECORTATORTAG_H
#define OIL_OILDECORTATORTAG_H

#include <string>

class OilDecoratorTag
{
public:
	
	OilDecoratorTag ( const std :: u32string & ID );
	~OilDecoratorTag ();
	
	const std :: u32string & GetID () const;
	
private:
	
	const std :: u32string ID;
	
};

#endif
