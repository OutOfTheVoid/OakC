#ifndef OIL_OILFUNCTIONDEFINITION_H
#define OIL_OILFUNCTIONDEFINITION_H

#include <string>
#include <map>

class OilFunctionParameterList;
class OilStatementBody;
class OilTemplateDefinition;
class OilTypeRef;

class OilFunctionDefinition
{
public:
	
	OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType );
	OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, OilStatementBody * Body, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition );
	OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, void * NativeFunctionData, uint64_t NativeFunctionTag, OilTypeRef * ReturnType );
	OilFunctionDefinition ( const std :: u32string & Name, bool Public, bool Inline, OilFunctionParameterList * ParameterList, void * NativeFunctionData, uint64_t NativeFunctionTag, OilTypeRef * ReturnType, OilTemplateDefinition * TemplateDefinition );
	~OilFunctionDefinition ();
	
	const std :: u32string GetName () const;
	
	const OilFunctionParameterList * GetParameterList () const; // 1:15:09 West World
	OilFunctionParameterList * GetParameterList ();
	
	bool IsNative () const;
	
	const OilStatementBody * GetStatementBody () const;
	OilStatementBody * GetStatementBody ();
	
	const OilTemplateDefinition * GetTemplateDefinition () const;
	OilTemplateDefinition * GetTemplateDefinition ();
	
	const OilTypeRef * GetReturnType () const;
	
	OilTypeRef * GetReturnType ();
	
	void * GetNativeFunctionData ();
	const void * GetNativeFunctionData () const;
	
	uint64_t GetNativeFunctionTag () const;
	
	bool IsTemplated () const;
	bool ConstantTerms () const;
	
	bool IsPublic () const;
	bool IsInline () const;
	
	bool HasReturnType () const;
	
private:
	
	const std :: u32string Name;
	
	bool Public;
	bool Inline;
	
	OilTemplateDefinition * TemplateDefinition;
	OilFunctionParameterList * ParameterList;
	OilTypeRef * ReturnType;
	
	bool NativeFunction;
	
	union
	{
		
		OilStatementBody * StatementBody;
		void * NativeFunctionData;
		
	};
	
	uint64_t NativeFunctionTag;
};

#endif
