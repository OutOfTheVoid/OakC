#ifndef OIL_OILBINDING_H
#define OIL_OILBINDING_H

#include <string>

class OilTypeRef;

class OilBinding
{
public:
	
	OilBinding ( const std :: u32string & Name, OilTypeRef * Type, bool Mutable, bool Public );
	~OilBinding ();
	
	const std :: u32string & GetName () const;
	
	const OilTypeRef * GetTypeRef () const;
	OilTypeRef * GetTypeRef ();
	
	bool GetMutable () const;
	bool GetPublic () const;
	
private:
	
	const std :: u32string Name;
	
	OilTypeRef * Type;
	
	bool Mutable;
	bool Public;
	
};

#endif
