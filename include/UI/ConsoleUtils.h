#ifndef UI_CONSOLEUTILS_H
#define UI_CONSOLEUTILS_H

#include <string>
#include <stdint.h>

namespace ConsoleUtils
{
	
	/**
	 * @brief Tests for a flag in a command-line argument.
	 * @details Tests for the presence of a flag <FlagName> in <ArgumentString> delimited as a flag list by the <FlagChar>, making sure to only count those flags nested <Nesting> times. If the <Exclusive> flag is set, only return true if the flag is the only one in the list.
	 * 
	 * @param ArgumentString The tested argument
	 * @param FlagName The name of the flag to look for
	 * @param Nesting How many times + 1 <FlagChar> should appear to verify this argument is a flag list (defaults to 0)
	 * @param Exclusive Whether or not other flags can appear in the list (defaults to true)
	 * @param FlagChar The charachter that delimits a flag list (defaults to '-')
	 * @return Whether or not the flag was found in the argument
	 */
	bool TestArgumentFlag ( const std :: string & ArgumentString, const std :: string & FlagName, uint32_t Nesting = 0, bool Exclusive = true, char FlagChar = '-' );
	
}

#endif
