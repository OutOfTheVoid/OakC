#ifndef EARLYANALYSIS_OAKDECORATORS_H
#define EARLYANALYSIS_OAKDECORATORS_H

#include <OIL/OilDecoratorTag.h>

const std :: u32string kDecoratorID_Builtin = U"builtin";

bool IsSimpleDecoratorWithID ( const OilDecoratorTag * Decorator, const std :: u32string & ID );

#endif
