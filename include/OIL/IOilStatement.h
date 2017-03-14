#ifndef OIL_IOILSTATEMENT_H
#define OIL_IOILSTATEMENT_H

class IOilStatement
{
public:
	
	typedef enum
	{
		
		kStatementType_Body,
		kStatementType_Binding,
		kStatementType_Expression,
		kStatementType_ImplicitLocalInitialization,
		kStatementType_ImplicitBindingInitialization
		
	} StatementType;
	
	inline virtual ~IOilStatement ()
	{
	}
	
	virtual StatementType GetStatementType () const = 0;
	
};

#endif
