#ifndef OIL_IOILPRIMARY_H
#define OIL_IOILPRIMARY_H

class IOilPrimary
{
public:
	
	inline virtual ~IOilPrimary () {};
	
	virtual bool IsConstant () const = 0;
	
};

#endif
