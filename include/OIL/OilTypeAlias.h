#ifndef OIL_OILTYPEALIAS_H
#define OIL_OILTYPEALIAS_H

#include <string>

#include <Tokenization/SourceRef.h>

class OilTypeRef;
class OilTemplateDefinition;

class OilTypeAlias
{
public:
	
	OilTypeAlias ( const SourceRef & Ref, const std :: u32string & AliasName, OilTypeRef * AliasedType, OilTemplateDefinition * TemplateDefinition, bool Builtin = false );
	~OilTypeAlias ();
	
	const std :: u32string & GetName () const;
	
	const OilTypeRef * GetAliasedType () const;
	OilTypeRef * GetAliasedType ();
	
	bool IsTemplated () const;
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	bool IsBuiltin () const;
	
	const SourceRef & GetSourceRef ();
	
private:
	
	OilTypeRef * AliasedType;
	OilTemplateDefinition * TemplateDefinition;
	
	const std :: u32string AliasName;
	
	bool Builtin;
	
	const SourceRef Ref;
	
};

#endif
