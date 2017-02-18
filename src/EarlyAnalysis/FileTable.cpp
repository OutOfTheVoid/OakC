#include <EarlyAnalysis/FileTable.h>

#include <Compilation/CompilationUnit.h>

#include <Filesystem/Path.h>

#ifndef NULL
	#define NULL nullptr
#endif

FileTable :: FileTable ():
	FileMap ()
{
}

FileTable :: ~FileTable ()
{
}

void FileTable :: AddFile ( const std :: string & RFileName, CompilationUnit * FileComilationUnit )
{
	
	std :: string FileName = CanonicalizePath ( RFileName );
	
	FileMap [ FileName ] = FileComilationUnit;
	
}

CompilationUnit * FileTable :: GetUnit ( const std :: string RFileName )
{
	
	std :: string FileName = CanonicalizePath ( RFileName );
	
	if ( FileMap.count ( FileName ) == 0 )
		return NULL;
	
	return FileMap [ FileName ];
	
}

void FileTable :: DestroyAll ()
{
	
	for ( std::map <std :: string, CompilationUnit *> :: iterator Iter = FileMap.begin (); Iter != FileMap.end (); ++ Iter )
	{
		
		delete Iter -> second;
		
	}
	
}
