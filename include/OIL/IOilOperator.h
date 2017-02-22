#ifndef OIL_IOILOPERATOR_H
#define OIL_IOILOPERATOR_H

class IOilOperator
{
public:
	
	typedef enum
	{
		
		kOperatorType_Unary,
		kOperatorType_Binary,
		
	} OperatorType;
	
	inline virtual ~IOilOperator () {};
	
	virtual bool ConstantTerms () = 0;
	virtual OperatorType GetOperatorType () = 0;
	
};

#endif
