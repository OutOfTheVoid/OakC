#ifndef OIL_OILMETHODPARAMETERLIST_H
#define OIL_OILMETHODPARAMETERLIST_H

class OilFunctionParameter;

#include <stdint.h>

#include <string>
#include <map>

class OilMethodParameterList
{
public:
	
	OilMethodParameterList ( bool SelfIsReference );
	~OilMethodParameterList ();
	
	void AddParameter ( OilFunctionParameter * AddParameter );
	
	bool IsSelfReference () const;
	
	uint32_t GetParameterCount () const;
	
	const OilFunctionParameter * GetFunctionParameter ( uint32_t Index ) const;
	OilFunctionParameter * GetFunctionParameter ( uint32_t Index );
	
	const OilFunctionParameter * FindFunctionParameter ( const std :: u32string & Name ) const;
	OilFunctionParameter * FindFunctionParameter ( const std :: u32string & Name );
	
private:
	
	bool SelfIsReference;
	
	std :: map <std :: u32string, OilFunctionParameter *> Parameters;
	
};

#endif
