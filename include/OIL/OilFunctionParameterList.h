#ifndef OIL_OILFUNCTIONPARAMETERLIST_H
#define OIL_OILFUNCTIONPARAMETERLIST_H

#include <stdint.h>
#include <string>
#include <map>

#include <Tokenization/SourceRef.h>

class OilFunctionParameter;

class OilFunctionParameterList
{
public:
	
	OilFunctionParameterList ( const SourceRef & Ref );
	~OilFunctionParameterList ();
	
	void AddParameter ( OilFunctionParameter * AddParameter );
	
	uint32_t GetParameterCount () const;
	
	const OilFunctionParameter * GetFunctionParameter ( uint32_t Index ) const;
	OilFunctionParameter * GetFunctionParameter ( uint32_t Index );
	
	const OilFunctionParameter * FindFunctionParameter ( const std :: u32string & Name ) const;
	OilFunctionParameter * FindFunctionParameter ( const std :: u32string & Name );
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	std :: map <std :: u32string, OilFunctionParameter *> Parameters;
	
	SourceRef Ref;
	
};

#endif
