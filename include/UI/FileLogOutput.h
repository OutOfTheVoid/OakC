#ifndef UI_FILELOGOUTPUT_H
#define UI_FILELOGOUTPUT_H

#include <Logging/ILogOutput.h>
#include <Filesystem/File.h>

class FileLogOutput : public virtual ILogOutput
{
public:
	
	FileLogOutput ( const std :: string & File );
	~FileLogOutput ();
	
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
	
private:
	
	File OutputFile;
	
};

#endif
