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

uint32_t FileTable :: GetCount ()
{
	
	return FileMap.size ();
	
}

CompilationUnit * FileTable :: GetUnit ( const std :: string RFileName )
{
	
	std :: string FileName = CanonicalizePath ( RFileName );
	
	if ( FileMap.count ( FileName ) == 0 )
		return NULL;
	
	return FileMap [ FileName ];
	
}

CompilationUnit * FileTable :: GetUnit ( uint32_t Index )
{
	
	std :: map <std :: string, CompilationUnit *> :: iterator Iter = FileMap.begin ();
	
	std :: advance ( Iter, Index );
	
	if ( Iter == FileMap.end () )
		return NULL;
	
	return Iter -> second;
	
}

void FileTable :: DestroyAll ()
{
	
	for ( std::map <std :: string, CompilationUnit *> :: iterator Iter = FileMap.begin (); Iter != FileMap.end (); ++ Iter )
	{
		
		delete Iter -> second;
		
	}
	
}
