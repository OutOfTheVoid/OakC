#ifndef EARLYANALYSIS_OAKOILTRANSLATION_H
#define EARLYANALYSIS_OAKOILTRANSLATION_H

#include <Parsing/ASTElement.h>

class OilNamespaceDefinition;
class OilDecoratorTag;

// Needed for import resolution to have conditional compilation
OilDecoratorTag * OakTranslateDecoratorTagToOil ( const ASTElement * DecoratorTagElement );

bool OakTranslateFileTreeToOil ( const ASTElement * TreeRoot, OilNamespaceDefinition & GlobalNS, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount );

#endif
