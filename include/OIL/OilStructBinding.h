#ifndef OIL_OILSTRUCTBINDING_H
#define OIL_OILSTRUCTBINDING_H

#include <string>

class OilTypeRef;

class OilStructBinding
{
public:
	
	OilStructBinding ( const std :: u32string & Name, OilTypeRef * TypeRef );
	~OilStructBinding ();
	
	const std :: u32string & GetName ();
	
	OilTypeRef * GetTypeRef ();
	
private:
	
	const std :: u32string Name;
	OilTypeRef * TypeRef;
	
};

#endif
