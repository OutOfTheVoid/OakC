#ifndef OIL_OILBUILTINSTRUCTDEFINITION_H
#define OIL_OILBUILTINSTRUCTDEFINITION_H

#include <stdint.h>
#include <string>

class OilStructDefinition;
class OilTemplateDefinition;

class OilBuiltinStructDefinition
{
public:
	
	typedef uint32_t TypeFlag;
	
	static const TypeFlag kTypeFlag_None = 0;
	static const TypeFlag kTypeFlag_RequiredAlignment = 1;
	
	OilBuiltinStructDefinition ( const std :: u32string & Name, uint32_t Size, uint32_t Alignment, TypeFlag Flags, OilTemplateDefinition * TemplateDefinition = NULL );
	OilBuiltinStructDefinition ( const std :: u32string & Name, uint32_t Size, uint32_t Alignment, TypeFlag Flags, OilStructDefinition * UnderlyingStructure );
	
	~OilBuiltinStructDefinition ();
	
	const std :: u32string & GetName () const;
	
	uint32_t GetSize () const;
	uint32_t GetAlignment () const;
	
	TypeFlag GetFlags () const;
	
	bool HasUnderlyingStructure () const;
	
	const OilStructDefinition * GetUnderlyingStructure () const;
	OilStructDefinition * GetUnderlyingStructure ();
	
	bool IsTemplated () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	
private:
	
	const std :: u32string Name;
	
	uint32_t Size;
	uint32_t Alignment;
	
	uint32_t Flags;
	
	OilStructDefinition * UnderlyingStructure;
	OilTemplateDefinition * TemplateDefinition;
	
};

#endif
