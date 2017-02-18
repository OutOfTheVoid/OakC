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
	
	CompilationUnit * GetUnit ( const std :: string FileName );
	
	void DestroyAll ();
	
private:
	
	std :: map <std :: string, CompilationUnit *> FileMap;
	
};

#endif
