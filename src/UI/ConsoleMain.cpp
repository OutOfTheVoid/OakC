#include <Logging/Logging.h>

#include <Compilation/CompilationUnit.h>

#include <UI/ConsoleUtils.h>
#include <UI/FileLogOutput.h>
#include <UI/STDLogOutput.h>

#include <Utils/Trie.h>

#include <vector>

#include <EarlyAnalysis/FileTable.h>

#define VERSION_STRING "0.0.1a"

void PrintHelp ();

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
		
		CompilationUnit * FileUnit = new CompilationUnit ( SourceFileNames [ I ], & Files );
		
		if ( ! FileUnit -> RunIndependantCompilationSteps () )
			return 0;
		
	}
	
	Files.DestroyAll ();
	
	return 0;
	
}

void PrintHelp ()
{
	
	LOG ( "OakC: Oak Compiler." );
	LOG ( "Usage: oakc [-<h|help>] [-v] [-l logfile] source.oak" );
	
}
