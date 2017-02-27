#ifndef OIL_OILSTATEMENTBODY_H
#define OIL_OILSTATEMENTBODY_H

#include <OIL/IOilStatement.h>

#include <vector>
#include <string>

class OilStatementBody : public virtual IOilStatement
{
public:
	
	OilStatementBody ();
	~OilStatementBody ();
	
	void AddIgnoredParameter ( const std :: u32string & ParameterName );
	
	uint32_t GetIgnoredParamCount () const;
	const std :: u32string & GetIgnoredParamName ( uint32_t Index ) const;
	
	void TakeIgnoredParams ( OilStatementBody & SubBody );
	
	void AddStatement ( IOilStatement * Statement );
	
	uint64_t GetStatementCount () const;
	const IOilStatement * GetStatement ( uint64_t Index ) const;
	IOilStatement * GetStatement ( uint64_t Index );
	
	StatementType GetStatementType () const;
	
private:
	
	std :: vector <std :: u32string> IgnoredParameters;
	std :: vector <IOilStatement *> Statements;
	
};

#endif
