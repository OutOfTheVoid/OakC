#ifndef OIL_OILFUNCTIONPARAMETER_H
#define OIL_OILFUNCTIONPARAMETER_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilTypeRef;

class OilFunctionParameter
{
public:
	
	OilFunctionParameter ( const SourceRef & Ref, const std :: u32string Name, OilTypeRef * Type, bool Mut );
	~OilFunctionParameter ();
	
	const OilTypeRef * GetType () const;
	OilTypeRef * GetType ();
	
	const std :: u32string & GetName () const;
	
	bool GetMut () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string Name;
	
	OilTypeRef * Type;
	
	bool Mut;
	
	SourceRef Ref;
	
};

#endif
