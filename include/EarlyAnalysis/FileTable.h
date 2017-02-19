#ifndef EARLYANALYSYS_FILETABLE_H
#define EARLYANALYSYS_FILETABLE_H

#include <string>
#include <map>

class CompilationUnit;

class FileTable
{
public:
	
	FileTable ();
	~FileTable ();
	
	void AddFile ( const std :: string & FileName, CompilationUnit * FileComilationUnit );
	
	uint32_t GetCount ();
	
	CompilationUnit * GetUnit ( const std :: string FileName );
	CompilationUnit * GetUnit ( uint32_t Index );
	
	void DestroyAll ();
	
private:
	
	std :: map <std :: string, CompilationUnit *> FileMap;
	
};

#endif
