#ifndef OIL_OILFUNCTIONDEFINITION_H
#define OIL_OILFUNCTIONDEFINITION_H

#include <string>
#include <map>

#include <Tokenization/SourceRef.h>

class OilFunctionParameterList;
class OilStatementBody;
class OilTemplateDefinition;
class OilTypeRef;

class OilFunctionDefinition
{
public:
	
	OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType, bool ReturnTypeMutable );
	OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition );
	OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, void * NativeFunctionData, uint64_t NativeFunctionTag, OilTypeRef * ReturnType, bool ReturnTypeMutable );
	OilFunctionDefinition ( const SourceRef & Ref, const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, void * NativeFunctionData, uint64_t NativeFunctionTag, OilTypeRef * ReturnType, bool ReturnTypeMutable, OilTemplateDefinition * TemplateDefinition );
	~OilFunctionDefinition ();
	
	const std :: u32string GetName () const;
	
	const OilFunctionParameterList * GetParameterList () const;
	OilFunctionParameterList * GetParameterList ();
	
	bool IsNative () const;
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	const OilTypeRef * GetReturnType () const;
	OilTypeRef * GetReturnType ();
	
	bool GetReturnTypeMutable () const;
	
	void * GetNativeFunctionData ();
	const void * GetNativeFunctionData () const;
	
	uint64_t GetNativeFunctionTag () const;
	
	bool IsTemplated () const;
	bool ConstantTerms () const;
	
	bool IsPublic () const;
	bool IsInline () const;
	
	bool HasReturnType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	const std :: u32string Name;
	
	bool Public;
	bool Inline;
	
	OilTemplateDefinition * TemplateDefinition;
	OilFunctionParameterList * ParameterList;
	OilTypeRef * ReturnType;
	bool ReturnTypeMutable;
	
	bool NativeFunction;
	
	union
	{
		
		OilStatementBody * StatementBody;
		void * NativeFunctionData;
		
	};
	
	uint64_t NativeFunctionTag;
	
	SourceRef Ref;
	
};

#endif
