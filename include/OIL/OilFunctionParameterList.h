#ifndef OIL_OILFUNCTIONPARAMETERLIST_H
#define OIL_OILFUNCTIONPARAMETERLIST_H

#include <stdint.h>
#include <string>
#include <map>

class OilFunctionParameter;

class OilFunctionParameterList
{
public:
	
	OilFunctionParameterList ();
	~OilFunctionParameterList ();
	
	void AddParameter ( OilFunctionParameter * AddParameter );
	
	uint32_t GetParameterCount () const;
	
	const OilFunctionParameter * GetFunctionParameter ( uint32_t Index ) const;
	OilFunctionParameter * GetFunctionParameter ( uint32_t Index );
	
	const OilFunctionParameter * FindFunctionParameter ( const std :: u32string & Name ) const;
	OilFunctionParameter * FindFunctionParameter ( const std :: u32string & Name );
	
private:
	
	std :: map <std :: u32string, OilFunctionParameter *> Parameters;
	
};

#endif
