#ifndef LOGGING_ILOGOUTPUT_H
#define LOGGING_ILOGOUTPUT_H

#include <string>

class ILogOutput
{
public:
	
	/// virtual destructor
	virtual inline ~ILogOutput () {};
	
	/**
	 * @brief Writes a normal log to the output (pure virtual)
	 * 
	 * @param Message The message to be written
	 */
	virtual void Write ( const std :: string & Message ) = 0;
	
	/**
	 * @brief Writes a error log to the output (pure virtual)
	 * 
	 * @param Message The message to be written
	 */
	virtual void WriteError ( const std :: string & Output ) = 0;
	
};

#endif
