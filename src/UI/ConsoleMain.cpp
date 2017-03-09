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

#include <Math/BigInteger.h>

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
	
	BigInteger A ( 0x7FFFFFFFFFFFFFFFULL );
	BigInteger B ( 2LL );
	
	if ( A.Get64Bits ( 0 ) != 0x7FFFFFFFFFFFFFFFULL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Increment ();
	
	if ( A.Get64Bits ( 0 ) != 0x8000000000000000ULL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Decrement ();
	
	if ( A.Get64Bits ( 0 ) != 0x7FFFFFFFFFFFFFFFULL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Add ( B );
	
	if ( A.Get64Bits ( 0 ) != 0x8000000000000001ULL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Subtract ( B );
	
	if ( A.Get64Bits ( 0 ) != 0x7FFFFFFFFFFFFFFFULL )
		LOG_FATALERROR ( "bigint failed" );
	
	A = 80LL;
	B = 5LL;
	
	A.Subtract ( B );
	
	if ( A.Get64Bits ( 0 ) != 75ULL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( { 0xFFFFFFFFFFFFFFFFULL }, BigInteger :: kSign_Positive );
	A.Increment ();
	
	if ( ( A.Get64Bits ( 0 ) != 0ULL ) || ( A.Get64Bits ( 64 ) != 1ULL ) )
		LOG_FATALERROR ( "bigint failed" );
	
	B.Set ( 200LL );
	A.Add ( B );
	
	if ( ( A.Get64Bits ( 0 ) != 200ULL ) || ( A.Get64Bits ( 64 ) != 1ULL ) )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Subtract ( B );
	
	if ( ( A.Get64Bits ( 0 ) != 0ULL ) || ( A.Get64Bits ( 64 ) != 1ULL ) )
		LOG_FATALERROR ( "bigint failed" );
	
	B.Set ( - 1LL );
	A.Add ( B );
	
	if ( ( A.Get64Bits ( 0 ) != 0xFFFFFFFFFFFFFFFFULL ) || ( A.Get64Bits ( 64 ) != 0ULL ) )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( 1 );
	
	//LOG_VERBOSE ( std :: to_string ( A.Get64Bits ( 0 ) ) );
	
	A.LeftShift ( 1 );
	
	if ( A.Get64Bits ( 0 ) != 2 )
		LOG_FATALERROR ( "bigint failed" );
	
	A.LeftShift ( 2 );
	
	if ( A.Get64Bits ( 0 ) != 8 )
		LOG_FATALERROR ( "bigint failed" );
	
	A.RightShift ( 3 );
	
	if ( A.Get64Bits ( 0 ) != 1 )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( - 3LL );
	B.Set ( - 9LL );
	
	A.Multiply ( B );
	
	if ( A.Get64Bits ( 0 ) != 27ULL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( 0LL );
	
	if ( A <= - 1LL )
		LOG_FATALERROR ( "bigint failed" );
	
	if ( A != 0LL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( 6 );
	B.Set ( 2 );
	
	if ( ! ( A > B ) )
		LOG_FATALERROR ( "bigint failed" );
	
	if ( B > A )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( { 0xFFFFFFFFFFFFFFFFULL, 0x7FFFFFFFFFFFFFFFULL, 0x7FFFFFFFFFFFFFFFULL }, BigInteger :: kSign_Positive );
	B.Set ( { 0xEFFFFFFFFFFFFFFFULL, 0x7FFFFFFFFFFFFFFFULL, 0x7FFFFFFFFFFFFFFFULL }, BigInteger :: kSign_Positive );
	
	if ( A <= B )
		LOG_FATALERROR ( "bigint failed" );
	
	if ( B >= A )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( 6LL );
	B.Set ( 2LL );
	
	A.Divide ( B );
	
	if ( A != 3LL )
	{
		
		LOG_FATALERROR ( "bigint failed" );
		
		LOG_VERBOSE ( std :: string ( "A: " ) + std :: to_string ( A.Get64Bits ( 0 ) ) );
		LOG_VERBOSE ( std :: string ( "B: " ) + std :: to_string ( B.Get64Bits ( 0 ) ) );
		
	}
	
	A.Set ( { 0x8000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL }, BigInteger :: kSign_Positive );
	B.Set ( { 0x1000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL }, BigInteger :: kSign_Positive );
	
	A.Divide ( B );
	
	if ( A != 8LL )
		LOG_FATALERROR ( "bigint failed" );
	
	A.Set ( { 0x8000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL }, BigInteger :: kSign_Positive );
	B.FlipSign ();
	
	A.Divide ( B );
	
	if ( A != - 8LL )
		LOG_FATALERROR ( "bigint failed" );
	
	return 0;
	
}
