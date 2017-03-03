#include <Logging/Logging.h>

#include <Compilation/CompilationUnit.h>

#include <UI/ConsoleUtils.h>
#include <UI/FileLogOutput.h>
#include <UI/STDLogOutput.h>

#include <Utils/Trie.h>

#include <vector>

#include <EarlyAnalysis/FileTable.h>

#include <OIL/OilDebugPrint.h>
#include <OIL/OilNamespaceDefinition.h>

#include <EarlyAnalysis/OakLiteralParsing.h>

#include <Encoding/CodeConversion.h>

#define VERSION_STRING "0.0.1b"

void PrintHelp ();
int Test ();
int Compile ( const std :: vector <std :: string> & SourceFileNames );

typedef enum
{
	
	kMainAction_Compile,
	kMainAction_Test,
	kMainAction_Help
	
} MainAction;

int main ( int argc, const char * argv [] )
{
	
	#ifdef DEBUG
		Logging :: SetAllowedErrorLevel ( Logging :: kLevel_Debug );
	#else
		Logging :: SetAllowedErrorLevel ( Logging :: kLevel_Warning );
	#endif
	
	Logging :: SetGlobalLogOutput ( new STDLogOutput () );
	
	bool Verbose = false;
	bool LogFileSet = false;
	
	MainAction Action = kMainAction_Compile;
	
	std :: vector <std :: string> SourceFileNames;
	
	for ( int32_t I = 1; I < argc; I ++ )
	{
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "h", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "help", 0, true ) )
		{
			
			Action = kMainAction_Help;
			
			continue;
			
		}
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "t", 0, true ) )
		{
			
			if ( Action == kMainAction_Compile )
				Action = kMainAction_Test;
			
			continue;
			
		}
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "l", 0, true ) && ( ! LogFileSet ) )
		{
			
			if ( ( argc - 1 ) <= I )
			{
				
				LOG_FATALERROR_NOFILE ( "No file supplied to log to." );
				return 1;
				
			}
			
			Logging :: SetGlobalLogOutput ( new FileLogOutput ( argv [ I + 1 ] ) );
			
			LogFileSet = true;
			
			I ++;
			continue;
			
		}
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "v", 0, false ) )
			Verbose = true;
		else
			SourceFileNames.push_back ( argv [ I ] );
		
	}
	
	Logging :: SetVerbose ( Verbose );
	
	switch ( Action )
	{
		
		case kMainAction_Compile:
			return Compile ( SourceFileNames );
			
		case kMainAction_Test:
			return Test ();
			
		case kMainAction_Help:
		{
			
			PrintHelp ();
			
			return 0;
			
		}
		
	}
	
	return 0;
	
}

int Compile ( const std :: vector <std :: string> & SourceFileNames )
{
	
	if ( SourceFileNames.size () == 0 )
	{
		
		LOG_FATALERROR_NOFILE ( "no input files!" );
		
		return 1;
		
	}
	
	FileTable Files;
	
	for ( uint32_t I = 0; I < SourceFileNames.size (); I ++ )
	{
		
		CompilationUnit * FileUnit = new CompilationUnit ( SourceFileNames [ I ] );
		
		if ( ! FileUnit -> RunIndependantCompilationSteps ( Files ) )
			return 1;
		
	}
	
	OilNamespaceDefinition OilRoot ( U"[global]" );
	
	for ( uint32_t I = 0; I < Files.GetCount (); I ++ )
	{
		
		CompilationUnit * Unit = Files.GetUnit ( I );
		
		if ( ! Unit -> RunAnalysis ( OilRoot ) )
			return 1;
		
	}
	
	LOG_VERBOSE ( "\n" );
	
	OilPrint ( OilRoot );
	
	Files.DestroyAll ();
	
	return 0;
	
}

void PrintHelp ()
{
	
	LOG ( "OakC: Oak Compiler." );
	LOG ( "Usage: oakc [-<h|help>] [-v] [-l logfile] source.oak" );
	
}

int Test ()
{
	
	std :: string ErrorString;
	std :: u32string OutString;
	
	if ( ! OakParseStringLiteral ( U"\"Hello world!\"", OutString, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	ErrorString = "";
	
	if ( ! OakParseStringLiteral ( U"\"\\u20B8\"", OutString, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	if ( OutString != U"₸" )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	ErrorString = "";
	
	if ( ! OakParseStringLiteral ( U"\"\\U00002211\"", OutString, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	if ( OutString != U"∑" )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	ErrorString = "";
	
	if ( ! OakParseStringLiteral ( U"\"\\x41\"", OutString, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	if ( OutString != U"A" )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	ErrorString = "";
	
	if ( ! OakParseStringLiteral ( U"\"\\x{000041}a\"", OutString, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	if ( OutString != U"Aa" )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	if ( ! OakParseStringLiteral ( U"\"\\x{00002211}a\"", OutString, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	if ( OutString != U"∑a" )
		LOG_FATALERROR ( std :: string ( "String parse failed: " ) + ErrorString + "\n* Value: \"" + CodeConversion :: ConvertUTF32ToUTF8 ( OutString ) + "\"" );
	
	char32_t OutChar = U' ';
	
	if ( ! OakParseCharLiteral ( U"\'a\'", OutChar, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	if ( OutChar != U'a' )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	if ( ! OakParseCharLiteral ( U"\'\\x41\'", OutChar, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	if ( OutChar != U'A' )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	if ( ! OakParseCharLiteral ( U"\'\\u0042\'", OutChar, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	if ( OutChar != U'B' )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	if ( ! OakParseCharLiteral ( U"\'\\U00000043\'", OutChar, ErrorString ) )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	if ( OutChar != U'C' )
		LOG_FATALERROR ( std :: string ( "Char parse failed: " ) + ErrorString + "\n* Value: \'" + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( OutChar, 1 ) ) + "\'" );
	
	
	return 0;
	
}
