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
	
	virtual bool ConstantTerms () const = 0;
	virtual OperatorType GetOperatorType () const = 0;
	
};

#endif
