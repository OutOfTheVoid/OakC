#ifndef OIL_OILIMPLEMENTBLOCK_H
#define OIL_OILIMPLEMENTBLOCK_H

class OilMethodDefinition;
class OilFunctionDefinition;
class OilTypeRef;
class OilTemplateDefinition;

#include <stdint.h>
#include <string>
#include <map>

class OilImplementBlock
{
public:
	
	OilImplementBlock ( OilTypeRef * ImplementedType );
	OilImplementBlock ( OilTypeRef * ImplementedType, OilTemplateDefinition * WhereDefinition );
	OilImplementBlock ( OilTypeRef * ImplementedType, OilTypeRef * ForTrait );
	OilImplementBlock ( OilTypeRef * ImplementedType, OilTypeRef * ForTrait, OilTemplateDefinition * WhereDefinition );
	~OilImplementBlock ();
	
	const OilTypeRef * GetImplementedType () const;
	OilTypeRef * GetImplementedType ();
	
	const OilTypeRef * GetForTrait () const;
	OilTypeRef * GetForTrait ();
	
	bool IsForTrait () const;
	
	const OilTemplateDefinition * GetWhereDefinition () const;
	OilTemplateDefinition * GetWhereDefinition ();
	
	bool HasWhereDefinition () const;
	
	void AddFunction ( OilFunctionDefinition * Function );
	
	uint32_t GetFunctionCount () const;
	
	const OilFunctionDefinition * GetFunction ( uint32_t Index ) const;
	OilFunctionDefinition * GetFunction ( uint32_t Index );
	
	const OilFunctionDefinition * FindFunction ( const std :: u32string & Name ) const;
	OilFunctionDefinition * FindFunction ( const std :: u32string & Name );
	
	void AddMethod ( OilMethodDefinition * Method );
	
	uint32_t GetMethodCount () const;
	
	const OilMethodDefinition * GetMethod ( uint32_t Index ) const;
	OilMethodDefinition * GetMethod ( uint32_t Index );
	
	const OilMethodDefinition * FindMethod ( const std :: u32string & Name ) const;
	OilMethodDefinition * FindMethod ( const std :: u32string & Name );
	
	static bool AreBlocksAmbiguous ( const OilImplementBlock & A, const OilImplementBlock & B );
	
private:
	
	OilTypeRef * ImplementedType;
	OilTypeRef * ForTrait;
	
	OilTemplateDefinition * WhereDefinition;
	
	std :: map <std :: u32string, OilFunctionDefinition *> Functions;
	std :: map <std :: u32string, OilMethodDefinition *> Methods;
	
};

#endif
