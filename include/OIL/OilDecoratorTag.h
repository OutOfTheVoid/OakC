#ifndef OIL_OILDECORTATORTAG_H
#define OIL_OILDECORTATORTAG_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilDecoratorTag
{
public:
	
	enum TagKind
	{
		
		kTagKind_Simple,
		kTagKind_Parametric_1
		
	};
	
	OilDecoratorTag ( const SourceRef & Ref, const std :: u32string & ID );
	OilDecoratorTag ( const SourceRef & Ref, const std :: u32string & ID, const std :: u32string & Param1 );
	~OilDecoratorTag ();
	
	TagKind GetKind () const;
	
	const std :: u32string & GetID () const;
	
	const SourceRef & GetSourceRef () const;
	
	const std :: u32string & GetParam1 () const;
	
private:
	
	const std :: u32string ID;
	const std :: u32string Param1;
	
	SourceRef Ref;
	
	TagKind Kind;
	
};

#endif
