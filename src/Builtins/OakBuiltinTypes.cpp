#include <Builtins/OakBuiltinTypes.h>

#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilBuiltinStructDefinition.h>
#include <OIL/OilTraitFunction.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilTemplateSpecification.h>
#include <OIL/OilImplementBlock.h>

#include <Compilation/Targets.h>
#include <Compilation/CompilationUnit.h>

#include <Logging/Logging.h>

#ifndef NULL
	#define NULL nullptr
#endif

bool AddTypesX86_32 ( OilNamespaceDefinition & RootNS );
bool AddTypesX86_64 ( OilNamespaceDefinition & RootNS );

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS );

void AddFunctionTypes ( OilNamespaceDefinition & RootNS, uint32_t PTRSize, uint32_t PTRAlignment );
void AddArrayType ( OilNamespaceDefinition & RootNS, uint32_t PTRSize, uint32_t PTRAlignment );

bool OakAddBuiltinTypes ( OilNamespaceDefinition & RootNS )
{
	
	if ( ! AddUniversalTypes ( RootNS ) )
		return false;
	
	switch ( TargetArch )
	{
		
		case kTargetArch_X86_32:
			return AddTypesX86_32 ( RootNS );
			
		case kTargetArch_X86_64:
			return AddTypesX86_64 ( RootNS );
		
	}
	
	LOG_FATALERROR_NOFILE ( "Unsupported target architecture!" );
	
	return false;
	
}

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS )
{
	
	(void) RootNS;
	
	return true;
	
}

bool AddTypesX86_32 ( OilNamespaceDefinition & RootNS )
{
	
	SourceRef NullRef { 0, 0, NULL };
	
	OilTypeDefinition * BoolType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"bool", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( BoolType );
	
	OilTypeDefinition * Int8Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int8Type );
	
	OilTypeDefinition * Int16Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int16Type );
	
	OilTypeDefinition * Int32Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int32Type );
	
	OilTypeDefinition * Int64Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i64", 8, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int64Type );
	
	OilTypeDefinition * IntPtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"iptr", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( IntPtrType );
	
	OilTypeDefinition * UInt8Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt8Type );
	
	OilTypeDefinition * UInt16Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt16Type );
	
	OilTypeDefinition * UInt32Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt32Type );
	
	OilTypeDefinition * UInt64Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u64", 8, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt64Type );
	
	OilTypeDefinition * UIntPtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"uptr", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UIntPtrType );
	
	OilTypeDefinition * PtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"ptr", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	PtrType -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"T" ) );
	
	RootNS.AddTypeDefinition ( PtrType );
	
	OilTypeDefinition * TraitPtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"trait_ptr", 8, 4, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	TraitPtrType -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"TRAIT" ) );
	
	RootNS.AddTypeDefinition ( TraitPtrType );
	
	AddFunctionTypes ( RootNS, 4, 4 );
	AddArrayType ( RootNS, 4, 4 );
	
	return true;
	
}

bool AddTypesX86_64 ( OilNamespaceDefinition & RootNS )
{
	
	SourceRef NullRef { 0, 0, NULL };
	
	OilTypeDefinition * BoolType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"bool", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( BoolType );
	
	OilTypeDefinition * Int8Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int8Type );
	
	OilTypeDefinition * Int16Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int16Type );
	
	OilTypeDefinition * Int32Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int32Type );
	
	OilTypeDefinition * Int64Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"i64", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( Int64Type );
	
	OilTypeDefinition * IntPtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"iptr", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( IntPtrType );
	
	OilTypeDefinition * UInt8Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt8Type );
	
	OilTypeDefinition * UInt16Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt16Type );
	
	OilTypeDefinition * UInt32Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt32Type );
	
	OilTypeDefinition * UInt64Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"u64", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UInt64Type );
	
	OilTypeDefinition * UIntPtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"uptr", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ), true );
	RootNS.AddTypeDefinition ( UIntPtrType );
	
	OilTypeDefinition * PtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"ptr", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	PtrType -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"T" ) );
	
	RootNS.AddTypeDefinition ( PtrType );
	
	OilTypeDefinition * TraitPtrType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"trait_ptr", 16, 8, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	TraitPtrType -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"TRAIT" ) );
	
	RootNS.AddTypeDefinition ( TraitPtrType );
	
	AddFunctionTypes ( RootNS, 8, 8 );
	AddArrayType ( RootNS, 8, 8 );
	
	return true;
	
}

void AddArrayType ( OilNamespaceDefinition & RootNS, uint32_t PTRSize, uint32_t PTRAlignment )
{
	
	SourceRef NullRef { 0, 0, NULL };
	
	OilTypeDefinition * ArrayType = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"array", PTRSize * 2, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	ArrayType -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"T" ) );
	
	RootNS.AddTypeDefinition ( ArrayType );
	
}

void AddFunctionTypes ( OilNamespaceDefinition & RootNS, uint32_t PTRSize, uint32_t PTRAlignment )
{
	
	SourceRef NullRef { 0, 0, NULL };
	
	OilTypeDefinition * Func0Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_0", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func0Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	
	RootNS.AddTypeDefinition ( Func0Type );
	
	OilTypeDefinition * Func1Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_1", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func1Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func1Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM_T" ) );
	
	RootNS.AddTypeDefinition ( Func1Type );
	
	OilTypeDefinition * Func2Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_2", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func2Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func2Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func2Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	
	RootNS.AddTypeDefinition ( Func2Type );
	
	OilTypeDefinition * Func3Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_3", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func3Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func3Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func3Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func3Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	
	RootNS.AddTypeDefinition ( Func3Type );
	
	OilTypeDefinition * Func4Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_4", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func4Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func4Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func4Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func4Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func4Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	
	RootNS.AddTypeDefinition ( Func4Type );
	
	OilTypeDefinition * Func5Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_5", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func5Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func5Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func5Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func5Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func5Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func5Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	
	RootNS.AddTypeDefinition ( Func5Type );
	
	OilTypeDefinition * Func6Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_6", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	
	RootNS.AddTypeDefinition ( Func6Type );
	
	OilTypeDefinition * Func7Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_7", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func7Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func7Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func7Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func7Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func7Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func7Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func6Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	
	RootNS.AddTypeDefinition ( Func7Type );
	
	OilTypeDefinition * Func8Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_8", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func8Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	
	RootNS.AddTypeDefinition ( Func8Type );
	
	OilTypeDefinition * Func9Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_9", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func9Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	
	RootNS.AddTypeDefinition ( Func9Type );
	
	OilTypeDefinition * Func10Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_10", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func10Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	
	OilTypeDefinition * Func11Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_11", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func11Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	
	RootNS.AddTypeDefinition ( Func11Type );
	
	OilTypeDefinition * Func12Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_12", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func12Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	
	RootNS.AddTypeDefinition ( Func12Type );
	
	OilTypeDefinition * Func13Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_13", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func13Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	
	RootNS.AddTypeDefinition ( Func13Type );
	
	OilTypeDefinition * Func14Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_14", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func14Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	
	RootNS.AddTypeDefinition ( Func14Type );
	
	OilTypeDefinition * Func15Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_15", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func15Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	
	RootNS.AddTypeDefinition ( Func15Type );
	
	OilTypeDefinition * Func16Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_16", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func16Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	
	RootNS.AddTypeDefinition ( Func16Type );
	
	OilTypeDefinition * Func17Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_17", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func17Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	
	RootNS.AddTypeDefinition ( Func17Type );
	
	OilTypeDefinition * Func18Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_18", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func18Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	
	RootNS.AddTypeDefinition ( Func18Type );
	
	OilTypeDefinition * Func19Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_19", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func19Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	
	RootNS.AddTypeDefinition ( Func19Type );
	
	OilTypeDefinition * Func20Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_20", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func20Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	
	RootNS.AddTypeDefinition ( Func20Type );
	
	OilTypeDefinition * Func21Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_21", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func21Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	
	RootNS.AddTypeDefinition ( Func21Type );
	
	OilTypeDefinition * Func22Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_22", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func22Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	
	RootNS.AddTypeDefinition ( Func22Type );
	
	OilTypeDefinition * Func23Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_23", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func23Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	
	RootNS.AddTypeDefinition ( Func23Type );
	
	OilTypeDefinition * Func24Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_24", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func24Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	
	RootNS.AddTypeDefinition ( Func24Type );
	
	OilTypeDefinition * Func25Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_25", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func25Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	
	RootNS.AddTypeDefinition ( Func25Type );
	
	OilTypeDefinition * Func26Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_26", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	Func26Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM26_T" ) );
	
	RootNS.AddTypeDefinition ( Func26Type );
	
	OilTypeDefinition * Func27Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_27", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM26_T" ) );
	Func27Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM27_T" ) );
	
	RootNS.AddTypeDefinition ( Func27Type );
	
	OilTypeDefinition * Func28Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_28", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM26_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM27_T" ) );
	Func28Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM28_T" ) );
	
	RootNS.AddTypeDefinition ( Func28Type );
	
	OilTypeDefinition * Func29Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_29", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM26_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM27_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM28_T" ) );
	Func29Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM29_T" ) );
	
	RootNS.AddTypeDefinition ( Func29Type );
	
	OilTypeDefinition * Func30Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_30", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM26_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM27_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM28_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM29_T" ) );
	Func30Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM30_T" ) );
	
	RootNS.AddTypeDefinition ( Func30Type );
	
	OilTypeDefinition * Func31Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_31", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM26_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM27_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM28_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM29_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM30_T" ) );
	Func31Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM31_T" ) );
	
	RootNS.AddTypeDefinition ( Func31Type );
	
	OilTypeDefinition * Func32Type = new OilTypeDefinition ( NullRef, new OilBuiltinStructDefinition ( U"func_32", PTRSize, PTRAlignment, OilBuiltinStructDefinition :: kTypeFlag_None, new OilTemplateDefinition ( NullRef ) ), true );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"RETURN_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM1_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM2_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM3_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM4_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM5_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM6_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM7_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM8_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM9_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM10_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM11_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM12_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM13_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM14_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM15_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM16_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM17_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM18_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM19_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM20_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM21_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM22_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM23_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM24_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM25_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM26_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM27_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM28_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM29_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM30_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM31_T" ) );
	Func32Type -> GetBuiltinStructDefinition () -> GetTemplateDefinition () -> AddParameter ( new OilTemplateDefinitionParameter ( NullRef, U"PARAM32_T" ) );
	
	RootNS.AddTypeDefinition ( Func32Type );
	
}

