#include <Filesystem/Path.h>

#include <Encoding/CodeConversion.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <stdlib.h>
	#include <unistd.h>
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
		
		WResult = GetFullPathNameW ( WidePath.c_str (), WResult + 1, Temporary, NULL );
		
		AbsPathUTF16.assign ( reinterpret_cast <const char16_t *> ( Temporary ) );
		
		delete [] Temporary;
		
	}
	else if ( WResult == 0 )
		return "";
	else
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


std :: string GetCurrentWorkingDirectory ()
{
	
#ifdef _WIN32
	
	wchar_t OutBuff [ OAKC_MAX_PATH ];
	
	uint32_t WResult = GetCurrentDirectoryW ( OutBuff, OAKC_MAX_PATH );
	
	std :: u16string OutStr16;
	
	if ( WResult > OAKC_MAX_PATH )
	{
		
		wchar_t * Temporary = new wchar_t [ WResult + 1 ];
		
		WResult = GetCurrentDirectoryW ( Temporary, WResult + 1 );
		
		OutStr16.assign ( reinterpret_cast <const char16_t *> ( Temporary ) );
		
		delete [] Temporary;
		
	}
	else if ( WResult == 0 )
		return "";
	else 
		OutStr16.assign ( OutBuff );
	
	return CodeConversion :: ConvertUTF16ToUTF8 ( OutStr16 );
	
#else
	
	char OutBuff [ OAKC_MAX_PATH ];
	
	char * Result = getcwd ( OutBuff, OAKC_MAX_PATH );
	
	if ( Result == NULL )
		return "";
	
	return std :: string ( OutBuff );
	
#endif
	
}
