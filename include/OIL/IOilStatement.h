#ifndef OIL_IOILSTATEMENT_H
#define OIL_IOILSTATEMENT_H

class IOilStatement
{
public:
	
	typedef enum
	{
		
		kStatementType_Body,
		kStatementType_Binding
		
	} StatementType;
	
	inline virtual ~IOilStatement ()
	{
	}
	
	virtual StatementType GetStatementType () const = 0;
	
};

#endif