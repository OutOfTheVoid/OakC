#ifndef OIL_OILSTATEMENTBODY_H
#define OIL_OILSTATEMENTBODY_H

#include <OIL/IOilStatement.h>

#include <vector>
#include <string>

#include <Tokenization/SourceRef.h>

class OilBindingStatement;
class OilConstStatement;

class OilStatementBody : public virtual IOilStatement
{
public:
	
	OilStatementBody ( const SourceRef & Ref );
	~OilStatementBody ();
	
	bool IsRootBody () const;
	OilStatementBody * GetParentBody () const;
	uint64_t GetParentBodySelfIndex () const;
	
	void AddIgnoredParameter ( const std :: u32string & ParameterName );
	
	uint32_t GetIgnoredParamCount () const;
	const std :: u32string & GetIgnoredParamName ( uint32_t Index ) const;
	
	void TakeIgnoredParams ( OilStatementBody & SubBody );
	
	void AddStatement ( IOilStatement * Statement );
	
	uint64_t GetStatementCount () const;
	const IOilStatement * GetStatement ( uint64_t Index ) const;
	IOilStatement * GetStatement ( uint64_t Index );
	
	void AddLocalBinding ( OilBindingStatement * LocalBinding );
	
	uint64_t GetLocalBindingCount () const;
	
	const OilBindingStatement * GetLocalBinding ( uint64_t Index ) const;
	OilBindingStatement * GetLocalBinding ( uint64_t Index );
	
	const OilBindingStatement * FindLocalBinding ( const std :: u32string & ID ) const;
	OilBindingStatement * FindLocalBinding ( const std :: u32string & ID );
	
	uint64_t GetLocalInitializationStatementIndex ( uint64_t Index ) const;
	
	uint64_t GetLocalConstCount () const;
	
	void AddLocalConst ( OilConstStatement * Const );
	
	const OilConstStatement * GetLocalConst ( uint64_t Index ) const;
	OilConstStatement * GetLocalConst ( uint64_t Index );
	
	const OilConstStatement * FindLocalConst ( const std :: u32string & ID ) const;
	OilConstStatement * FindLocalConst ( const std :: u32string & ID );
	
	StatementType GetStatementType () const;
	
	const SourceRef & GetSourceRef () const;
	
private:
	
	typedef struct
	{
		
		uint64_t InitializationStatementIndex;
		OilBindingStatement * Binding;
		
	} LocalData;
	
	std :: vector <std :: u32string> IgnoredParameters;
	std :: vector <IOilStatement *> Statements;
	
	std :: vector <LocalData> Locals;
	std :: vector <OilConstStatement *> Constants;
	
	OilStatementBody * ParentBody;
	uint64_t ParentSelfIndex;
	
	SourceRef Ref;
	
};

#endif
