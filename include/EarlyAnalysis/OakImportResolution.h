#ifndef EARLYANALYSYS_OAKIMPORTRESOLUTION_H
#define EARLYANALYSYS_OAKIMPORTRESOLUTION_H

#include <EarlyAnalysis/FileTable.h>

#include <string>
#include <vector>

class ASTElement;

bool OakResolveImports ( const ASTElement * FileRootElement, const std :: string & SourceFileName, const std :: vector <std :: string> & SearchPaths, FileTable & GlobalFileTable, std :: vector <CompilationUnit *> & UnitsOut, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount );

#endif
