#ifndef EARLYANALYSIS_OAKOILTRANSLATION_H
#define EARLYANALYSIS_OAKOILTRANSLATION_H

#include <Parsing/ASTElement.h>

class OilNamespaceDefinition;

bool OakTranslateFileTreeToOil ( const ASTElement * TreeRoot, OilNamespaceDefinition & GlobalNS );

#endif
