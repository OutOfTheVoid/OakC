#ifndef OIL_OILFUNCTIONPARAMETER_H
#define OIL_OILFUNCTIONPARAMETER_H

#include <string>

class OilTypeRef;

class OilFunctionParameter
{
public:
	
	OilFunctionParameter ( const std :: u32string Name, OilTypeRef * Type, bool Mut );
	~OilFunctionParameter ();
	
	const OilTypeRef * GetType () const;
	OilTypeRef * GetType ();
	
	const std :: u32string & GetName () const;
	
	bool GetMut () const;
	
private:
	
	const std :: u32string Name;
	
	OilTypeRef * Type;
	
	bool Mut;
	
};

#endif
