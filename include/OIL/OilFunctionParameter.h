#ifndef OIL_OILFUNCTIONPARAMETER_H
#define OIL_OILFUNCTIONPARAMETER_H

#include <string>

class OilTypeRef;

class OilFunctionParameter
{
public:
	
	OilFunctionParameter ( const std :: u32string Name, OilTypeRef * Type );
	~OilFunctionParameter ();
	
	const OilTypeRef * GetType () const;
	OilTypeRef * GetType ();
	
	const std :: u32string & GetName () const;
	
private:
	
	const std :: u32string Name;
	
	OilTypeRef * Type;
	
};

#endif
