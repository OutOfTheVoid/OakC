#ifndef OIL_OILSTRUCTBINDING_H
#define OIL_OILSTRUCTBINDING_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilTypeRef;

class OilStructBinding
{
public:
	
	OilStructBinding ( const SourceRef & Ref, const std :: u32string & Name, OilTypeRef * TypeRef, bool Public );
	~OilStructBinding ();
	
	const std :: u32string & GetName () const;
	
	const OilTypeRef * GetTypeRef () const;
	OilTypeRef * GetTypeRef ();
	
	const SourceRef & GetSourceRef () const;
	
	bool IsPublic () const;
	
private:
	
	const std :: u32string Name;
	OilTypeRef * TypeRef;
	
	SourceRef Ref;
	
	bool Public;
	
};

#endif
