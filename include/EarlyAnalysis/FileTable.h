#ifndef EARLYANALYSYS_FILETABLE_H
#define EARLYANALYSYS_FILETABLE_H

#include <string>
#include <map>

class CompilationUnit;

/*
* @brief A table of files being compiled
* @detail A table of files currently already active in compilation units, named for their system path.
*/
class FileTable
{
public:
	
	//! Constructor
	FileTable ();
	
	//! Destructor
	~FileTable ();
	
	/*
	* @brief Adds a file to the table.
	* 
	* @param FileName the path to the file, used as a key to the compilation unit.
	* @param FileComilationUnit The compilation unit that the file is being compiled in.
	*/
	void AddFile ( const std :: string & FileName, CompilationUnit * FileComilationUnit );
	
	/*
	* @brief Gets the number of files in the table.
	* 
	* @return The number of files.
	*/
	uint32_t GetCount ();
	
	/*
	* @brief Finds an active compilation unit for the file.
	* @details Searches for a compilation unit for the file, if there is one.
	* 
	* @param FileName The path to the file.
	* 
	* @return A pointer to the compilation unit if it exists, otherwise NULL.
	*/
	CompilationUnit * GetUnit ( const std :: string & FileName );
	
	/*
	* @brief Gets the nth file added to the table.
	* 
	* @param Index the index of the file to get.
	* 
	* @return The compilation unit for that file, if it exists, otherwise NULL.
	*/
	CompilationUnit * GetUnit ( uint32_t Index );
	
	/*
	* @brief Destroys all compilation units in the table.
	* @details Deletes all compilation units added to the table, freeing their resources.
	*/
	void DestroyAll ();
	
private:
	
	std :: map <std :: string, CompilationUnit *> FileMap;
	
};

#endif
