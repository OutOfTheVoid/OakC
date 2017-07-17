#ifndef FILESYSTEM_PATH_H
#define FILESYSTEM_PATH_H

#include <string>
#include <vector>

std :: string CanonicalizePath ( const std :: string & Path );

std :: string GetCurrentWorkingDirectory ();

bool CheckFileExists ( const std :: string & Path );

bool FindFirstMatchingFileInDirectories ( const std :: string & Path, const std :: vector <std :: string> & Directories, std :: string & OutPath );

std :: string SplitPathAtEnd ( const std :: string & Path );

#endif
