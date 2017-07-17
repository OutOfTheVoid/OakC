#ifndef FILESYSTEM_PATH_H
#define FILESYSTEM_PATH_H

#include <string>

std :: string CanonicalizePath ( const std :: string & Path );

std :: string GetCurrentWorkingDirectory ();

std :: string SplitPathAtEnd ( const std :: string & Path );

#endif
