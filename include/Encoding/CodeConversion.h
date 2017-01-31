#ifndef ENCODING_CODECONVERSION_H
#define ENCODING_CODECONVERSION_H

#include <string>

namespace CodeConversion
{
	
	/**
	 * @brief Converts a UTF8 string to a UTF32 string.
	 * 
	 * @param UTF8String The string to be converted
	 * @return A u32string with the UTF32 formatted data
	 */
	std :: u32string ConvertUTF8ToUTF32 ( std :: string UTF8String );
	
	/**
	 * @brief Converts a UTF32 string to a UTF8 string.
	 * 
	 * @param UTF32String The string to be converted
	 * @return A string with the UTF8 formatted data
	 */
	std :: string ConvertUTF32ToUTF8 ( std :: u32string UTF32String );
	
}

#endif
