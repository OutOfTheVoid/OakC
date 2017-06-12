#ifndef OIL_IOILSTATEMENT_H
#define OIL_IOILSTATEMENT_H

class IOilStatement
{
public:
	
	typedef enum
	{
		
		kStatementType_Body,
		kStatementType_Binding,
		kStatementType_Const,
		kStatementType_Expression,
		kStatementType_Return,
		kStatementType_IfElse,
		kStatementType_Match,
		kStatementType_WhileLoop,
		kStatementType_DoWhileLoop,
		kStatementType_Loop,
		kStatementType_Break,
		kStatementType_ImplicitLocalInitialization,
		kStatementType_ImplicitBindingInitialization
		
	} StatementType;
	
	inline virtual ~IOilStatement ()
	{
	}
	
	virtual StatementType GetStatementType () const = 0;
	
};

#endif
