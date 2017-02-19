#ifndef OIL_OILTYPELIST_H
#define OIL_OILTYPELIST_H

#include <map>
#include <string>

// TODO: Finish

class OilStructDefinition;
class OilBuiltinTypeDefinition;
class OilAliasedTypeDefinition;

class OilTypeList
{
public:
	
	
	
private:
	
	typedef struct
	{
		
		bool Struct;
		
		union
		{
			
			OilStructDefinition * StructDefinition;
			OilBuiltinTypeDefinition * BuiltinTypeDefinition;
			OilAliasedTypeDefinition * AliasedTypeDeifnition;
			
		};
		
	} TypeRecord;
	
	std :: map <std :: u32string, TypeRecord> Types;
	
};

#endif
