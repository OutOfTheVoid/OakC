#ifndef OIL_OILFUNCTIONCALLPARAMETERLIST_H
#define OIL_OILFUNCTIONCALLPARAMETERLIST_H

#include <stdint.h>
#include <vector>

class OilExpression;

class OilFunctionCallParameterList
{
public:
	
	OilFunctionCallParameterList ();
	~OilFunctionCallParameterList ();
	
	void AddParameter ( OilExpression * ParamExpression );
	
	uint32_t GetParameterCount () const;
	
	const OilExpression * GetParameter ( uint32_t Index ) const;
	OilExpression * GetParameter ( uint32_t Index );
	
private:
	
	std :: vector <OilExpression *> Parameters;
	
};

#endif
