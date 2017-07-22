#include <Logging/Logging.h>
#include <sstream>

bool Logging :: Verbosity = false;
Logging :: ErrorLevel Logging :: MaxLevel = kLevel_Warning;
	
ILogOutput * Logging :: LogOutput = NULL;

void Logging :: SetGlobalLogOutput ( ILogOutput * LogOutput )
{
	
	Logging :: LogOutput = LogOutput;
	
}

void Logging :: SetAllowedErrorLevel ( ErrorLevel MaxLevel )
{
	
	Logging :: MaxLevel = static_cast <ErrorLevel> ( static_cast <uint32_t> ( MaxLevel ) & 0xFFF );
	
}

void Logging :: SetVerbose ( bool Verbose )
{
	
	Logging :: Verbosity = Verbose;
	
}

void Logging :: Log ( const std :: string & Message, bool Verbose )
{
	
	if ( ( ! Logging :: Verbosity ) && Verbose )
		return;
	
	if ( LogOutput == NULL )
		return;
	
	std :: stringstream FormatStream;
	
	FormatStream << Message << std :: endl;
	
	LogOutput -> Write ( FormatStream.str () );
	
}

void Logging :: LogError ( const std :: string & Message, ErrorLevel Level, uint32_t LineNumber, const std :: string & FileName )
{
	
	ErrorLevel UnVerboseLevel = static_cast <ErrorLevel> ( static_cast <uint32_t> ( Level ) & 0xFFF );
	
	if ( UnVerboseLevel > MaxLevel )
		return;
	
	if ( ! Verbosity && ( UnVerboseLevel != Level ) )
		return;
	
	if ( LogOutput == NULL )
		return;
	
	std :: stringstream FormatStream;
	
	if ( FileName.size () != 0 )
		FormatStream << FileName << ", " << LineNumber << ": ";
	
	switch ( UnVerboseLevel )
	{
		
		case kLevel_FatalError:
			FormatStream << "fatal error: ";
			break;
			
		case kLevel_Error:
			FormatStream << "error: ";
			break;
		
		case kLevel_Warning:
			FormatStream << "warning: ";
			break;
			
		case kLevel_Debug:
			FormatStream << "debug: ";
			break;
		
		default:
			break;
		
	}
	
	FormatStream << Message << std :: endl;
	
	if ( UnVerboseLevel != kLevel_Debug )
		LogOutput -> WriteError ( FormatStream.str () );
	else
		LogOutput -> Write ( FormatStream.str () );
	
}
