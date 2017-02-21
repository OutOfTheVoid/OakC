#ifndef OIL_OILSTRUCTDEFINITION_H
#define OIL_OILSTRUCTDEFINITION_H

#include <string>
#include <map>

class OilStructBinding;
class OilTemplateDefinition;

class OilStructDefinition// public virtual IOilTypeDefinition
{
public:
		
	OilStructDefinition ( const std :: u32string & ID );
	OilStructDefinition ( const std :: u32string & ID, OilTemplateDefinition * TemplateDefinition );
	~OilStructDefinition ();
	
	void AddBinding ( OilStructBinding * Binding );
	
	uint32_t GetBindingCount () const;
	
	OilStructBinding * GetBinding ( const std :: u32string Name );
	OilStructBinding * GetBinding ( uint32_t Index );
	
	const OilStructBinding * GetBinding ( const std :: u32string Name ) const;
	const OilStructBinding * GetBinding ( uint32_t Index ) const;
	
	const std :: u32string GetID () const;
	
	OilTemplateDefinition * GetTemplateDefinition ();
	const OilTemplateDefinition * GetTemplateDefinition () const;
	
private:
	
	const std :: u32string ID;
	
	OilTemplateDefinition * TemplateDefinition;
	
	std :: map <std :: u32string, OilStructBinding *> Bindings;
	
};

#endif
