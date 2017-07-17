#include <Logging/Logging.h>

#include <Compilation/CompilationUnit.h>
#include <Compilation/Targets.h>

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

#include <Filesystem/Path.h>

#define VERSION_STRING "0.0.2b"

int Test ();

int Compile ( const std :: vector <std :: string> & SourceFileNames, const std :: vector <std :: string> & SearchPaths, const OilPrintOptions & PrintOptions );

void PrintHelp ();
void ListArchitechtures ();
void ListOperatingSystems ();
void PrintVerboseHelp ();
void PrintLogHelp ();
void PrintBuiltinHelp ();
void PrintResolutionHelp ();
void BuildCompilationConditions ( std :: vector <std :: u32string> & Conditions );

typedef enum
{
	
	kMainAction_None,
	kMainAction_Compile,
	kMainAction_Test,
	kMainAction_Help,
	kMainAction_Help_Builtins,
	kMainAction_Help_Resolution,
	kMainAction_Help_Log,
	kMainAction_Help_Verbose,
	kMainAction_ListArchitechtures,
	kMainAction_ListOperatingSystems,
	
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
	bool Builtins = false;
	bool Resolution = false;
	bool LogFileSet = false;
	
	MainAction Action = kMainAction_None;
	
	std :: vector <std :: string> SourceFileNames;
	std :: vector <std :: string> SearchPaths;
	
	SearchPaths.push_back ( GetCurrentWorkingDirectory () );
	
	for ( int32_t I = 1; I < argc; I ++ )
	{
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "h", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "help", 0, true ) )
		{
			
			Action = kMainAction_Help;
			
			if ( I < argc - 1 )
			{
				
				if ( ( std :: string ( argv [ I + 1 ] ) == "l" ) || ( std :: string ( argv [ I + 1 ] ) == "log" ) )
				{
					
					I ++;
					
					Action = kMainAction_Help_Log;
					
				}
				else if ( std :: string ( argv [ I + 1 ] ) == "os" )
				{
					
					I ++;
					
					Action = kMainAction_ListOperatingSystems;
					
				}
				else if ( ( std :: string ( argv [ I + 1 ] ) == "a" ) || ( std :: string ( argv [ I + 1 ] ) == "arch" ) )
				{
					
					I ++;
					
					Action = kMainAction_ListArchitechtures;
					
				}
				else if ( ( std :: string ( argv [ I + 1 ] ) == "v" ) || ( std :: string ( argv [ I + 1 ] ) == "verbose" ) )
				{
					
					I ++;
					
					Action = kMainAction_Help_Verbose;
					
				}
				else if ( ( std :: string ( argv [ I + 1 ] ) == "sh_b" ) || ( std :: string ( argv [ I + 1 ] ) == "show_builtins" ) )
				{
					
					I ++;
					
					Action = kMainAction_Help_Builtins;
					
				}
				else if ( ( std :: string ( argv [ I + 1 ] ) == "sh_r" ) || ( std :: string ( argv [ I + 1 ] ) == "show_resolution" ) )
				{
					
					I ++;
					
					Action = kMainAction_Help_Resolution;
					
				}
				
			}
			
			continue;
			
		}
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "s", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "search", 0, true ) )
		{
			
			if ( I == ( argc - 1 ) )
			{
				
				LOG_FATALERROR_NOFILE ( "expected search path after search flag" );
				
				return 1;
				
			}
			
			SearchPaths.push_back ( argv [ I + 1 ] );
			
			I ++;
			
			continue;
			
		}
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "t", 0, true ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "test", 0, true ) )
		{
			
			Action = kMainAction_Test;
			
			continue;
			
		}
		
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
			else if ( ( ArchSwitch == "list" ) || ( ArchSwitch == "help" ) )
				Action = kMainAction_ListArchitechtures;
			else
			{
				
				LOG_FATALERROR_NOFILE ( std :: string ( "Architecture not recognized: " ) + ArchSwitch + "\nUse oakc \"-arch <list | help>\" to list supported architectures" );
				return 1;
				
			}
			
			I ++;
			
			continue;
			
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
			else if ( ( OSSwitch == "list" ) || ( OSSwitch == "help" ) )
				Action = kMainAction_ListOperatingSystems;
			else
			{
				
				LOG_FATALERROR_NOFILE ( std :: string ( "OS not recognized: " ) + OSSwitch );
				return 1;
				
			}
			
			I ++;
			
			continue;
			
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
		
		if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "sh_b", 0, false ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "show_builtins", 0, false ) )
			Builtins = true;
		else if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "sh_r", 0, false ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "show_resolution", 0, false ) )
			Resolution = true;
		else if ( ConsoleUtils :: TestArgumentFlag ( argv [ I ], "v", 0, false ) || ConsoleUtils :: TestArgumentFlag ( argv [ I ], "verbose", 0, false ) )
			Verbose = true;
		else
		{
			
			SourceFileNames.push_back ( argv [ I ] );
			
			if ( Action == kMainAction_None )
				Action = kMainAction_Compile;
			
		}
		
	}
	
	Logging :: SetVerbose ( Verbose );
	
	switch ( Action )
	{
		
		case kMainAction_None:
		case kMainAction_Compile:
		{
			
			OilPrintOptions PrintOptions;
			
			PrintOptions.ShowResolution = Resolution;
			PrintOptions.PrintBuiltins = Builtins;
			PrintOptions.HighlightBuiltins = true;
			
			return Compile ( SourceFileNames, SearchPaths, PrintOptions );
			
		}
			
		case kMainAction_Test:
			return Test ();
			
		case kMainAction_Help:
		{
			
			PrintHelp ();
			
			return 0;
			
		}
		
		case kMainAction_Help_Verbose:
		{
			
			PrintVerboseHelp ();
			
			return 0;
			
		}
		
		case kMainAction_Help_Log:
		{
			
			PrintLogHelp ();
			
			return 0;
			
		}
		
		case kMainAction_Help_Builtins:
		{
			
			PrintBuiltinHelp ();
			
			return 0;
			
		}
		
		case kMainAction_Help_Resolution:
		{
			
			PrintResolutionHelp ();
			
			return 0;
			
		}
		
		case kMainAction_ListArchitechtures:
		{
			
			ListArchitechtures ();
			
			return 0;
			
		}
		
		case kMainAction_ListOperatingSystems:
		{
			
			ListOperatingSystems ();
			
			return 0;
			
		}
		
	}
	
	return 0;
	
}



int Compile ( const std :: vector <std :: string> & SourceFileNames, const std :: vector <std :: string> & SearchPaths, const OilPrintOptions & PrintOptions )
{
	
	if ( SourceFileNames.size () == 0 )
	{
		
		LOG_FATALERROR_NOFILE ( "no input files!" );
		
		return 1;
		
	}
	
	std :: vector <std :: u32string> CompilationConditions;
	
	BuildCompilationConditions ( CompilationConditions );
	
	FileTable Files;
	
	for ( uint32_t I = 0; I < SourceFileNames.size (); I ++ )
	{
		
		CompilationUnit * FileUnit = new CompilationUnit ( SourceFileNames [ I ], SearchPaths );
		
		if ( ! FileUnit -> RunIndependantCompilationSteps ( Files, SearchPaths, & CompilationConditions [ 0 ], CompilationConditions.size () ) )
			return 1;
		
	}
	
	LOG_VERBOSE ( "\n[ ALL ]: compilation step: Early analysis." );
	
	OilNamespaceDefinition OilRoot ( { 0, 0, NULL }, U"[global]" );
	
	if ( ! CompilationUnit :: RunBuiltinAddition ( OilRoot ) )
		return 1;
	
	for ( uint32_t I = 0; I < Files.GetCount (); I ++ )
	{
		
		CompilationUnit * Unit = Files.GetUnit ( I );
		
		if ( ! Unit -> ApplyToOil ( OilRoot, & CompilationConditions [ 0 ], CompilationConditions.size () ) )
			return 1;
		
	}
	
	OilPrint ( OilRoot, PrintOptions );
	
	if ( ! CompilationUnit :: RunSourceAnalysis ( OilRoot ) )
		return 1;
	
	OilPrint ( OilRoot, PrintOptions );
	
	Files.DestroyAll ();
	
	return 0;
	
}

void BuildCompilationConditions ( std :: vector <std :: u32string> & Conditions )
{
	
	switch ( TargetOS )
	{
		
		case kTargetOS_None:
			Conditions.push_back ( U"target_os_none" );
			break;
			
		case kTargetOS_GNULinux:
			Conditions.push_back ( U"target_os_gnulinux" );
			break;
			
		case kTargetOS_Win32:
			Conditions.push_back ( U"target_os_win32" );
			break;
			
		case kTargetOS_MacOSX:
			Conditions.push_back ( U"target_os_macosx" );
			break;
			
		default:
			break;
		
	}
	
	switch ( TargetArch )
	{
		
		case kTargetArch_X86_32:
			Conditions.push_back ( U"target_arch_x86" );
			break;
			
		case kTargetArch_X86_64:
			Conditions.push_back ( U"target_arch_x86_64" );
			break;
			
		default:
			break;
		
	}
	
}

void PrintHelp ()
{
	
	LOG ( "OakC: Oak Compiler." );
	LOG ( "Usage: oakc [-<h|help> ?<flag name>] [-v] [-<l|log> logfile] [-<a|arch> <{target architecture}|list>] [-os <{target os}|list>] source.oak" );
	
}

void PrintVerboseHelp ()
{
	
	LOG ( "\nVerbose flag:" );
	LOG ( "=============" );
	LOG ( "Puts the compiler in verbose mode." );
	LOG ( "\nUsage: -<v|verbose>" );
	
}

void PrintLogHelp ()
{
	
	LOG ( "\nLog flag:" );
	LOG ( "=============" );
	LOG ( "Redirects all output to a log file." );
	LOG ( "\nUsage: -<l|log> {file to log to}" );
	
}

void PrintBuiltinHelp ()
{
	
	LOG ( "\nBuiltin flag:" );
	LOG ( "=============" );
	LOG ( "Shows builtin definitions in debug output." );
	LOG ( "\nUsage: -<sh_b|show_builtins>" );
	
};

void PrintResolutionHelp ()
{
	
	LOG ( "\nResolution flag:" );
	LOG ( "=============" );
	LOG ( "Shows resolution status of definitions in debug output." );
	LOG ( "\nUsage: -<sh_r|show_resolution>" );
	
}

inline std :: string RightPaddedString ( const std :: string & In, uint32_t Length, char Pad )
{
	
	std :: string Return = In;
	
	while ( Return.size () < Length )
		Return.push_back ( Pad );
	
	return Return;
	
}

void ListArchitechtures ()
{
	
	LOG ( "\nTarget architecture select" );
	LOG ( "==========================" );
	LOG ( "\nUsage: -<a|arch> {target architecture}" );
	LOG ( "\n--------------------------------------------------------------------------------" );
	LOG ( "Flag value | Description" );
	LOG ( "--------------------------------------------------------------------------------" );
	LOG ( RightPaddedString ( TARGET_ARCH_NAME_X86, 11, ' ' ) + "| Intel i686+" );
	LOG ( RightPaddedString ( TARGET_ARCH_NAME_X86_64, 11, ' ' ) + "| X86_64/AMD64" );
	
}

void ListOperatingSystems ()
{
	
	LOG ( "\nTarget OS select" );
	LOG ( "================" );
	LOG ( "\nUsage: -os {target_os}" );
	LOG ( "\n--------------------------------------------------------------------------------" );
	LOG ( "Flag value | Description" );
	LOG ( "--------------------------------------------------------------------------------" );
	LOG ( RightPaddedString ( TARGET_OS_NAME_NONE, 11, ' ' ) + "| No OS defined (implies no std library)" );
	LOG ( RightPaddedString ( TARGET_OS_NAME_GNULINUX, 11, ' ' ) + "| GNU/Linux" );
	LOG ( RightPaddedString ( TARGET_OS_NAME_MACOSX, 11, ' ' ) + "| Mac OS X" );
	LOG ( RightPaddedString ( TARGET_OS_NAME_WIN32, 11, ' ' ) + "| Windows" );
	
}

int Test ()
{
	
	return 0;
	
}
