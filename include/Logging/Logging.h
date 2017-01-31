#ifndef LOGGING_LOGGING_H
#define LOGGING_LOGGING_H

#include <stdint.h>
#include <string>

#include <Logging/ILogOutput.h>

#define LOG_FATALERROR_NOFILE( message ) Logging :: LogError ( message, Logging :: kLevel_FatalError, 0, "" )
#define LOG_FATALERROR_VERBOSE_NOFILE( message ) Logging :: LogError ( message, Logging :: kLevel_FatalError_Verbose, 0, "" )
#define LOG_ERROR_NOFILE( message ) Logging :: LogError ( message, Logging :: kLevel_Error, 0, "" )
#define LOG_ERROR_VERBOSE_NOFILE( message ) Logging :: LogError ( message, Logging :: kLevel_Error_Verbose, 0, "" )
#define LOG_WARNING_NOFILE( message ) Logging :: LogError ( message, Logging :: kLevel_Warning, 0, "" )
#define LOG_WARNING_VERBOSE_NOFILE( message ) Logging :: LogError ( message, Logging :: kLevel_Warning_Verbose, 0, "" )

#define LOG_FATALERROR( message ) Logging :: LogError ( message, Logging :: kLevel_FatalError, __LINE__, __FILE__ )
#define LOG_FATALERROR_VERBOSE( message ) Logging :: LogError ( message, Logging :: kLevel_FatalError_Verbose, __LINE__, __FILE__ )
#define LOG_ERROR( message ) Logging :: LogError ( message, Logging :: kLevel_Error, __LINE__, __FILE__ )
#define LOG_ERROR_VERBOSE( message ) Logging :: LogError ( message, Logging :: kLevel_Error_Verbose, __LINE__, __FILE__ )
#define LOG_WARNING( message ) Logging :: LogError ( message, Logging :: kLevel_Warning, __LINE__, __FILE__ )
#define LOG_WARNING_VERBOSE( message ) Logging :: LogError ( message, Logging :: kLevel_Warning_Verbose, __LINE__, __FILE__ )
#define LOG_DEBUG( message ) Logging :: LogError ( message, Logging :: kLevel_Debug, __LINE__, __FILE__ )
#define LOG_DEBUG_VERBOSE( message ) Logging :: LogError ( message, Logging :: kLevel_Debug_Verbose, __LINE__, __FILE__ )

#define LOG( message ) Logging :: Log ( message, false )
#define LOG_VERBOSE( message ) Logging :: Log ( message, true )


class Logging
{
public:
	
	enum ErrorLevel
	{
		
		kLevel_FatalError = 0x0000,
		kLevel_FatalError_Verbose = 0x1000,
		kLevel_Error = 0x0001,
		kLevel_Error_Verbose = 0x1001,
		kLevel_Warning = 0x0002,
		kLevel_Warning_Verbose = 0x1002,
		kLevel_Debug = 0x0003,
		kLevel_Debug_Verbose = 0x1003
		
	};
	
	/**
	 * @brief Sets the global output of the logger.
	 * @details Sets which output mechanism will be used to report logs (std::cout for example). If this is not set, it will default to null.
	 * 
	 * @param LogOutput The output object to print logging output
	 */
	static void SetGlobalLogOutput ( ILogOutput * LogOutput );
	
	/**
	 * @brief Sets maximum error level that should be logged.
	 * @details Sets the error level at which no lesser error should be logged. This does not consider verbosity, so you can pass with or without the _Verbose. If this is not set, it will default to kLevel_Warning
	 * 
	 * @param Level The maximum error level, irrespective of verbosity
	 */
	static void SetAllowedErrorLevel ( ErrorLevel Level );
	
	/**
	 * @brief Sets whether the logger should pass verbose messages.
	 * @details Sets whether the logger should pass verbose messages.
	 * 
	 * @param Verbose Whether or not verbose messages should be passed
	 */
	static void SetVerbose ( bool Verbose );
	
	/**
	 * @brief Logs a message.
	 * @details Logs a message to the regular output, assuming that if it is verbose, verbose logging is enabled.
	 * 
	 * @param Message The message to log
	 * @param Verbose Whether this message is a verbose message or not
	 */
	static void Log ( const std :: string & Message, bool Verbose );
	
	/**
	 * @brief Logs an error.
	 * @details Logs an error at a specified error level, recording the line number and file name that triggered it.
	 * 
	 * @param Message The error message
	 * @param ErrorLevel The level of the error
	 * @param LineNumber The line number the error occured on
	 * @param FileName The name of the file the error occcured in
	 */
	static void LogError ( const std :: string & Message, ErrorLevel Level, uint32_t LineNumber = 0, const std :: string & FileName = "" );
	
private:
	
	static bool Verbosity;
	static ErrorLevel MaxLevel;
	
	static ILogOutput * LogOutput;
	
};

#endif
