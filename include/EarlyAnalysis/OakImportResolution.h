#ifndef EARLYANALYSYS_OAKIMPORTRESOLUTION_H
#define EARLYANALYSYS_OAKIMPORTRESOLUTION_H

#include <EarlyAnalysis/FileTable.h>

#include <string>
#include <vector>

class ASTElement;

bool OakResolveImports ( const ASTElement * FileRootElement, const std :: string & SourceFileName, FileTable * GlobalFileTable, std :: vector <CompilationUnit *> & UnitsOut );

#endif
