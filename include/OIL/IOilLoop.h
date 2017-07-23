#ifndef OIL_IOILLOOP_H
#define OIL_IOILLOOP_H

#include <string>

#include <OIL/IOilStatement.h>

class IOilLoop : public virtual IOilStatement
{
public:
	
	inline virtual ~IOilLoop () {};
	
	virtual bool HasLoopLabel () const = 0;
	virtual const std :: u32string & GetLoopLabel () const = 0;
	
};

#endif
