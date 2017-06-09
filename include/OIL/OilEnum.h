#ifndef OIL_OILENUM
#define OIL_OILENUM

#include <Tokenization/SourceRef.h>

#include <string>
#include <map>

class OilNamespaceDefinition;
class OilTypeRef;
class OilTemplateDefinition;

class OilEnum
{
public:
	
	OilEnum ( const SourceRef & Ref, const std :: u32string & Name );
	OilEnum ( const SourceRef & Ref, const std :: u32string & Name, OilTemplateDefinition * Template );
	~OilEnum ();
	
	const std :: u32string & GetName () const;
	
	bool IsTemplated () const;
	
	OilTemplateDefinition * GetTemplateDefinition ();
	const OilTemplateDefinition * GetTemplateDefinition () const;
	
	uint32_t GetBranchCount () const;
	
	void AddBranch ( const SourceRef & Ref, const std :: u32string & BranchName );
	void AddDataBranch ( const SourceRef & Ref, const std :: u32string & BranchName, OilTypeRef * DataType );
	
	const std :: u32string & GetBranchName ( uint32_t Index ) const;
	
	bool HasBranch ( const std :: u32string & Name ) const;
	bool HasBranch ( uint32_t Index ) const;
	
	const SourceRef & GetBranchSourceRef ( const std :: u32string & Name ) const;
	const SourceRef & GetBranchSourceRef ( uint32_t Index ) const;
	
	bool BranchHasData ( uint32_t Index ) const;
	
	const OilTypeRef * GetBranchDataType ( uint32_t Index ) const;
	OilTypeRef * GetBranchDataType ( uint32_t Index );
	
	const OilTypeRef * GetBranchDataType ( const std :: u32string & Name ) const;
	OilTypeRef * GetBranchDataType ( const std :: u32string & Name );
	
	const SourceRef & GetSourceRef () const;
	
	const OilNamespaceDefinition * GetParentNamespace () const;
	OilNamespaceDefinition * GetParentNamespace ();
	
private:
	
	static const std :: u32string NullStringRef;
	static const SourceRef NullSourceRef;
	
	const std :: u32string Name;
	
	OilTemplateDefinition * Template;
	
	typedef struct
	{
		
		OilTypeRef * DataType;
		SourceRef Ref;
		
	} BranchData;
	
	std :: map <std :: u32string, BranchData> Branches;
	
	const SourceRef Ref;
	
	OilNamespaceDefinition * ParentNamespace;
	
};

#endif
