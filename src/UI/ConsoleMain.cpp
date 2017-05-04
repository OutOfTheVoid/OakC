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
#include <Math/BigFloat.h>

#include <Encoding/CodeConversion.h>

#include <EarlyAnalysis/OakLiteralParsing.h>

#include <Compilation/Targets.h>

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
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "t", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "test", 0, true ) )
		{
			
			if ( Action == kMainAction_Compile )
				Action = kMainAction_Test;
			
			continue;
			
		}
		
		// TODO: ARCH AND OS PARSING
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "a", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "arch", 0, true ) )
		{
			
			if ( ( argc - 1 ) <= I )
			{
				
				LOG_FATALERROR_NOFILE ( "No architecture supplied" );
				return 1;
				
			}
			
			const std :: string ArchSwitch ( argv [ I + 1 ] );
			
			if ( ArchSwitch == TARGET_ARCH_NAME_X86 )
				TargetArch = kTargetArch_X86_32;
			else if ( ArchSwitch == TARGET_ARCH_NAME_X86_64 )
				TargetArch = kTargetArch_X86_64;
			else
			{
				
				LOG_FATALERROR_NOFILE ( std :: string ( "Architecture not recognized: " ) + ArchSwitch );
				return 1;
				
			}
			
		}
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "os", 0, true ) )
		{
			
			if ( ( argc - 1 ) <= I )
			{
				
				LOG_FATALERROR_NOFILE ( "No architecture supplied" );
				return 1;
				
			}
			
			const std :: string OSSwitch ( argv [ I + 1 ] );
			
			if ( OSSwitch == TARGET_OS_NAME_NONE )
				TargetOS = kTargetOS_None;
			else if ( OSSwitch == TARGET_OS_NAME_GNULINUX )
				TargetOS = kTargetOS_GNULinux;
			else if ( OSSwitch == TARGET_OS_NAME_WIN32 )
				TargetOS = kTargetOS_Win32;
			else if ( OSSwitch == TARGET_OS_NAME_MACOSX )
				TargetOS = kTargetOS_MacOSX;
			else
			{
				
				LOG_FATALERROR_NOFILE ( std :: string ( "OS not recognized: " ) + OSSwitch );
				return 1;
				
			}
			
		}
		
		if ( ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "l", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "log", 0, true ) ) && ( ! LogFileSet ) )
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
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "v", 0, false ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "verbose", 0, false ) )
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
	
	LOG_VERBOSE ( "\n[ ALL ]: compilation step: Early analysis." );
	
	OilNamespaceDefinition OilRoot ( U"[global]" );
	
	if ( ! CompilationUnit :: RunBuiltinAddition ( OilRoot ) )
		return 1;
	
	for ( uint32_t I = 0; I < Files.GetCount (); I ++ )
	{
		
		CompilationUnit * Unit = Files.GetUnit ( I );
		
		if ( ! Unit -> ApplyToOil ( OilRoot ) )
			return 1;
		
	}
	
	if ( ! CompilationUnit :: RunSourceAnalysis ( OilRoot ) )
		return 1;
	
	OilPrintOptions PrintOptions;
	
	PrintOptions.PrintBuiltins = true;
	PrintOptions.HighlightBuiltins = true;
	
	OilPrint ( OilRoot, PrintOptions );
	
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
	
	BigFloat C ( BigInteger ( 3LL ), -1, 0 ); // 0.3
	BigFloat D ( BigInteger ( 2LL ), 1, 0 ); // 20.0
	
	C.Multiply ( D );
	
	if ( ! C.Equal ( BigFloat ( BigInteger ( 6LL ), 0, 0 ) ) )
		LOG_FATALERROR ( "bigfloat failed" );
	
	D = BigFloat ( BigInteger ( 2LL ), 0, 0 );
	
	C.Divide ( D );
	
	if ( ! C.Equal ( BigFloat ( BigInteger ( 3LL ), 0, 0 ) ) )
		LOG_FATALERROR ( "bigfloat failed" );
	
	if ( ! OakParseFloatLiteral ( U"0.1f", C ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( "Z" );
	
	if ( ! C.Equal ( BigFloat ( 1LL, 0LL, - 1LL ) ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( std :: string ( "C: [ Sig: " ) + C.GetSignificand ().ToHexString () + ", P2: " + std :: to_string ( C.GetPower2 () ) + ", P10: " + std :: to_string ( C.GetPower10 () ) );
	
	if ( ! OakParseFloatLiteral ( U"0.12", C ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( std :: string ( "C: [ Sig: " ) + C.GetSignificand ().ToHexString () + ", P2: " + std :: to_string ( C.GetPower2 () ) + ", P10: " + std :: to_string ( C.GetPower10 () ) + " ]" );
	
	LOG_VERBOSE ( "Z" );
	
	if ( ! C.Equal ( BigFloat ( 12LL, 0LL, - 2LL ) ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( std :: string ( "C: [ Sig: " ) + C.GetSignificand ().ToHexString () + ", P2: " + std :: to_string ( C.GetPower2 () ) + ", P10: " + std :: to_string ( C.GetPower10 () ) );
	
	if ( ! OakParseFloatLiteral ( U"0x1p+0", C ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( "Z" );
	
	if ( ! C.Equal ( BigFloat ( 1LL, 0LL, 0LL ) ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( std :: string ( "C: [ Sig: " ) + C.GetSignificand ().ToHexString () + ", P2: " + std :: to_string ( C.GetPower2 () ) + ", P10: " + std :: to_string ( C.GetPower10 () ) + " ]" );
	
	if ( ! OakParseFloatLiteral ( U"0x10FF45p-2f64", C ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( "Z" );
	
	LOG_VERBOSE ( std :: string ( "C: [ Sig: " ) + C.GetSignificand ().ToHexString () + ", P2: " + std :: to_string ( C.GetPower2 () ) + ", P10: " + std :: to_string ( C.GetPower10 () ) + " ]" );
	
	if ( ! C.Equal ( BigFloat ( 0x10FF45LL, - 2LL, 0LL ) ) )
		LOG_FATALERROR ( "float parse failed" );
	
	LOG_VERBOSE ( std :: string ( "C: [ Sig: " ) + C.GetSignificand ().ToHexString () + ", P2: " + std :: to_string ( C.GetPower2 () ) + ", P10: " + std :: to_string ( C.GetPower10 () ) + " ]" );
	
	
	return 0;
	
}
