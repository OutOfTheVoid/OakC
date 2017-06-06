#ifndef EARLYANALYSIS_OILDECORATORS_H
#define EARLYANALYSIS_OILDECORATORS_H

#include <OIL/OilDecoratorTag.h>

const std :: u32string kDecoratorID_Builtin = U"builtin";

const std :: u32string kDecoratorID_ConditionalCompilation_KeepIf = U"keep_if";

bool IsSimpleDecoratorWithID ( const OilDecoratorTag * Decorator, const std :: u32string & ID );
bool IsParametric1DecoratorWithID ( const OilDecoratorTag * Decorator, const std :: u32string & ID, std :: u32string & Param1Out );

bool IsConditionalCompilationDecorator ( const OilDecoratorTag * Decorator );

bool TestConditionalCompilationDecorators ( const OilDecoratorTag ** Decorators, uint32_t DecoratorCount, const std :: u32string * CompilationConditions, uint32_t CompilationConditionCount );

#endif
