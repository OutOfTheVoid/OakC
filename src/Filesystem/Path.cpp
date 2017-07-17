#include <Filesystem/Path.h>

#include <Encoding/CodeConversion.h>

#ifdef _WIN32
	#include <windows.h>
#else
	#include <stdlib.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
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

bool CheckFileExists ( const std :: string & Path )
{
	
	#if defined ( __APPLE__ )
	
	struct stat FStatData;
	
#elif defined ( _WIN32 )
	
	struct __stat64 FStatData;
	
#else
	
	struct stat64 FStatData;
	
#endif
	
	int ReturnCode;
		
#if defined ( __APPLE__ )
	
	ReturnCode = stat ( Path.c_str (), & FStatData );
	
#elif defined ( _WIN32 )
	
	ReturnCode = _stat64 ( Path.c_str (), & FStatData );
	
#else
	
	ReturnCode = stat64 ( Path.c_str (), & FStatData );
	
#endif
	
	if ( ReturnCode == - 1 )
		return false;
	
	return true;
	
}

bool IsAbsolutePath ( const std :: string & Path )
{
	
	if ( Path.size () == 0 )
		return false;
	
	char C0 = Path.at ( 0 );
	
	if ( C0 == '/' )
		return true;
	
#ifdef _WIN32
	
	if ( C0 == '\\' )
		return true;
	
	if ( Path.size () < 3 )
		return false;
	
	char C1 = Path.at ( 1 );
	char C2 = Path.at ( 2 );
	
	if ( ( ( C0 >= 'a' ) && ( C0 <= 'z' ) ) || ( ( C0 >= 'A' ) && ( C0 <= 'Z' ) ) )
	{
		
		if ( ( C1 == ':' ) && ( C2 == '\\' ) )
			return true;
		
	}
	
#endif
	
	return false;
	
}

bool EndsInSeperator ( const std :: string & Path )
{
	
	if ( Path.size () == 0 )
		return false;
	
	char C = Path.at ( Path.size () - 1 );
	
	if ( C == '/' )
		return true;
	
	#ifdef _WIN32
	
	if ( C == '\\' )
		return true;
	
	#endif
	
	return false;
	
}

bool FindFirstMatchingFileInDirectories ( const std :: string & Path, const std :: vector <std :: string> & Directories, std :: string & OutPath )
{
	
	if ( IsAbsolutePath ( Path ) )
	{
		
		OutPath = Path;
		
		return CheckFileExists ( Path );
		
	}
	
	std :: string Temp;
	
	Temp = CanonicalizePath ( Path );
	
	if ( CheckFileExists ( Temp ) )
	{
		
		OutPath = Temp;
		
		return true;
		
	}
	
	for ( uint32_t I = 0; I < Directories.size (); I ++ )
	{
		
		Temp = EndsInSeperator ( Directories [ I ] ) ? Directories [ I ] : ( Directories [ I ] + "/" );
		Temp += Path;
		Temp = CanonicalizePath ( Temp );
		
		if ( CheckFileExists ( Temp ) )
		{
			
			OutPath = Temp;
			
			return true;
			
		}
		
	}
	
	return false;
	
}
