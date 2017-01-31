#ifndef UI_STDLOGOUTPUT_H
#define UI_STDLOGOUTPUT_H

#include <Logging/ILogOutput.h>

class STDLogOutput : public virtual ILogOutput
{
public:
	
	/**
	 * @brief Writes log output to std::cout
	 * @details Writes log output to std::cout
	 * 
	 * @param Output The message to write
	 */
	void Write ( const std :: string & Output );
	
	/**
	 * @brief Writes log output to std::cerr
	 * @details Writes log output to std::cerr
	 * 
	 * @param Output The message to write
	 */
	void WriteError ( const std :: string & Output );
	
};

#endif
