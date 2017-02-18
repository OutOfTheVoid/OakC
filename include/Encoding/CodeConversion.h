#ifndef ENCODING_CODECONVERSION_H
#define ENCODING_CODECONVERSION_H

#include <string>

namespace CodeConversion
{
	
	/**
	 * @brief Converts a UTF-8 string to a UTF-32 string.
	 * 
	 * @param UTF8String The string to be converted
	 * @return A u32string with the UTF-32 formatted data
	 */
	std :: u32string ConvertUTF8ToUTF32 ( const std :: string & UTF8String );
	
	/**
	 * @brief Converts a UTF-32 string to a UTF-8 string.
	 * 
	 * @param UTF32String The string to be converted
	 * @return A string with the UTF-8 formatted data
	 */
	std :: string ConvertUTF32ToUTF8 ( const std :: u32string & UTF32String );
	
	/**
	 * @brief Converts a UTF-16 string to a UTF-32 string.
	 * 
	 * @param UTF16String The string to be converted
	 * @return A u32string with the UTF-32 formatted data
	 */
	std :: u32string ConvertUTF16ToUTF32 ( const std :: u16string & UTF16String );
	
	/**
	 * @brief Converts a UTF-32 string to a UTF-16 string.
	 * 
	 * @param UTF32String The string to be converted
	 * @return A string with the UTF-16 formatted data
	 */
	std :: u16string ConvertUTF32ToUTF16 ( const std :: u32string & UTF32String );
	
	/**
	 * @brief Converts a UTF-8 string to a UTF-16 string.
	 * 
	 * @param UTF8String The string to be converted
	 * @return A u16string with the UTF-16 formatted data
	 */
	std :: u16string ConvertUTF8ToUTF16 ( const std :: string & UTF8String );
	
	/**
	 * @brief Converts a UTF-16 string to a UTF-8 string.
	 * 
	 * @param UTF16String The string to be converted
	 * @return A string with the UTF formatted data
	 */
	std :: string ConvertUTF16ToUTF8 ( const std :: u16string & UTF16String );
	
}

#endif
