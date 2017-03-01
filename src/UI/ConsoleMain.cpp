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

#define VERSION_STRING "0.0.1b"

void PrintHelp ();
void TestArea ();

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
	
	std :: vector <std :: string> SourceFileNames;
	
	for ( uint32_t I = 1; I < argc; I ++ )
	{
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "h", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "help", 0, true ) )
		{
			
			PrintHelp ();
			
			return 0;
			
		}
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "t", 0, true ) )
		{
			
			TestArea ();
			
			return 0;
			
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
			return 0;
		
	}
	
	OilNamespaceDefinition OilRoot ( U"[global]" );
	
	for ( uint32_t I = 0; I < Files.GetCount (); I ++ )
	{
		
		CompilationUnit * Unit = Files.GetUnit ( I );
		
		if ( ! Unit -> RunAnalysis ( OilRoot ) )
			return 0;
		
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

void TestArea ()
{
	
	uint64_t Value;
	bool Overflow64;
	
	OakParseIntegerLiteral ( U"0", Value, Overflow64 );
	
	if ( ( Value != 0 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"1000_000", Value, Overflow64 );
	
	if ( ( Value != 1000000 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0xF00", Value, Overflow64 );
	
	if ( ( Value != 0xF00 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0xF_00_00_00_00_00", Value, Overflow64 );
	
	if ( ( Value != 0xF0000000000 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0x10000000000000000", Value, Overflow64 );
	
	if ( ! Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"18_446_744_073_709_551_615", Value, Overflow64 );
	
	if ( ( Value != 0xFFFFFFFFFFFFFFFF ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"18_446_744_073_709_551_617", Value, Overflow64 );
	
	if ( ! Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0b100", Value, Overflow64 );
	
	if ( ( Value != 4 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0b1000_0000_0000", Value, Overflow64 );
	
	if ( ( Value != 2048 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0b1_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000_00000000", Value, Overflow64 );
	
	if ( ! Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0o10", Value, Overflow64 );
	
	if ( ( Value != 8 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0o100", Value, Overflow64 );
	
	if ( ( Value != 64 ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0o17_7777_7777_7777_7777_7777", Value, Overflow64 );
	
	if ( ( Value != 0xFFFFFFFFFFFFFFFF ) || Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
	OakParseIntegerLiteral ( U"0o2000000000000000000000", Value, Overflow64 );
	
	if ( ! Overflow64 )
		LOG_FATALERROR ( std :: string ( "Parsing error! value: " ) + std :: to_string ( Value ) + ( Overflow64 ? " <Overflow64>" : "" ) );
	
}
