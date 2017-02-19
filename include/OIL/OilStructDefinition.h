#ifndef OIL_OILSTRUCTDEFINITION_H
#define OIL_OILSTRUCTDEFINITION_H

#include <string>
#include <map>

class OilStructBinding;

class OilStructDefinition
{
public:
		
	OilStructDefinition ( const std :: u32string & ID );
	~OilStructDefinition ();
	
	//void SetTemplateDefinition (  );
	
	void AddBinding ( OilStructBinding * Binding );
	
	uint32_t GetBindingCount ();
	
	OilStructBinding * GetBinding ( const std :: u32string Name );
	OilStructBinding * GetBinding ( uint32_t Index );
	
	const std :: u32string GetID () const;
	
private:
	
	const std :: u32string ID;
	
	std :: map <std :: u32string, OilStructBinding *> Bindings;
	
};

#endif
