#ifndef OIL_OILSTRUCTDEFINITION_H
#define OIL_OILSTRUCTDEFINITION_H

#include <string>
#include <map>

#include <Tokenization/SourceRef.h>

class OilStructBinding;
class OilTemplateDefinition;

class OilStructDefinition
{
public:
		
	OilStructDefinition ( const SourceRef & Ref, const std :: u32string & ID );
	OilStructDefinition ( const SourceRef & Ref, const std :: u32string & ID, OilTemplateDefinition * TemplateDefinition );
	~OilStructDefinition ();
	
	void AddBinding ( OilStructBinding * Binding );
	
	uint32_t GetBindingCount () const;
	
	OilStructBinding * GetBinding ( const std :: u32string Name );
	OilStructBinding * GetBinding ( uint32_t Index );
	
	const OilStructBinding * GetBinding ( const std :: u32string Name ) const;
	const OilStructBinding * GetBinding ( uint32_t Index ) const;
	
	const std :: u32string GetID () const;
	
	bool IsTemplated () const;
	
	OilTemplateDefinition * GetTemplateDefinition ();
	const OilTemplateDefinition * GetTemplateDefinition () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string ID;
	
	OilTemplateDefinition * TemplateDefinition;
	
	std :: map <std :: u32string, OilStructBinding *> Bindings;
	
	SourceRef Ref;
	
};

#endif
