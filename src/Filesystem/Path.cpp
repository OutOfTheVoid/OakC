#include <Filesystem/Path.h>

#include <Encoding/CodeConversion.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <stdlib.h>
#endif

#ifndef NULL
	#define NULL nullptr
#endif

#define OAKC_MAX_PATH 4096

std :: string CanonicalizePath ( const std :: string & Path )
{
	
#ifdef _WIN32
	
	std :: u16string WidePath = CodeConversion :: ConvertUTF8ToUTF16 ( Path );
	
	wchar_t OutBuff [ OAKC_MAX_PATH ];
	
	uint32_t WResult = GetFullPathNameW ( WidePath.c_str (), OAKC_MAX_PATH, OutBuff, NULL );
	
	std :: u16string AbsPathUTF16;
	
	if ( WResult > OAKC_MAX_PATH )
	{
		
		wchar_t * Temporary = new wchar_t [ WResult + 1 ];
		
		GetFullPathNameW ( WidePath.c_str (), WResult + 1, Temporary, NULL );
		
		AbsPathUTF16.assign ( reinterpret_cast <const char16_t *> ( Temporary ) );
		
		delete Temporary;
		
	}
	
	if ( WResult == 0 )
		return "";
	
	AbsPathUTF16.assign ( OutBuff );
	
	return CodeConversion :: ConvertUTF16ToUTF8 ( AbsPathUTF16 );
	
#else
	
	char OutBuff [ OAKC_MAX_PATH ];
	
	char * Result = realpath ( Path.c_str (), OutBuff );
	
	if ( Result == NULL )
		return "";
	
	return std :: string ( OutBuff );
	
#endif
	
}
