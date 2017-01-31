#include <UI/ConsoleUtils.h>

bool ConsoleUtils :: TestArgumentFlag ( const std :: string & ArgumentString, const std :: string & FlagName, uint32_t Nesting, bool Exclusive, char FlagChar )
{
	
	// No flags can even exist
	if ( ArgumentString.size () < Nesting + 2 )
		return false;
	
	// Make sure that all the delimiter charachters are FlagChar
	while ( Nesting > 0 )
	{
		
		if ( ArgumentString.at ( Nesting ) != FlagChar )
			return false;
		
		Nesting --;
		
	}
	
	if ( ArgumentString.at ( 0 ) != FlagChar )
		return false;
	
	// Get the flags without the delimiters
	std :: string ArgumentSubstring = ArgumentString.substr ( Nesting + 1 );
	
	// See if the flag is the only one
	if ( Exclusive )
		return ArgumentSubstring.compare ( FlagName ) == 0;
	
	// Is the flag there at all?
	return ArgumentSubstring.find ( FlagName ) != std::string :: npos;
	
}
