#ifndef OIL_OILDECORTATORTAG_H
#define OIL_OILDECORTATORTAG_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilDecoratorTag
{
public:
	
	OilDecoratorTag ( const SourceRef & Ref, const std :: u32string & ID );
	~OilDecoratorTag ();
	
	const std :: u32string & GetID () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string ID;
	
	SourceRef Ref;
	
};

#endif
