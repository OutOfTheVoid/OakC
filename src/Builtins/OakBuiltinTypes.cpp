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
	
	OilTypeDefinition * BoolType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"bool", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( BoolType );
	
	OilTypeDefinition * Int8Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int8Type );
	
	OilTypeDefinition * Int16Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int16Type );
	
	OilTypeDefinition * Int32Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int32Type );
	
	OilTypeDefinition * Int64Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i64", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int64Type );
	
	OilTypeDefinition * IntPtrType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"iptr", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( IntPtrType );
	
	OilTypeDefinition * UInt8Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt8Type );
	
	OilTypeDefinition * UInt16Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt16Type );
	
	OilTypeDefinition * UInt32Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt32Type );
	
	OilTypeDefinition * UInt64Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u64", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt64Type );
	
	OilTypeDefinition * UIntPtrType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"uptr", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UIntPtrType );
	
	return true;
	
}

bool AddTypesX86_64 ( OilNamespaceDefinition & RootNS )
{
	
	OilTypeDefinition * BoolType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"bool", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( BoolType );
	
	OilTypeDefinition * Int8Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int8Type );
	
	OilTypeDefinition * Int16Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int16Type );
	
	OilTypeDefinition * Int32Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int32Type );
	
	OilTypeDefinition * Int64Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"i64", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( Int64Type );
	
	OilTypeDefinition * IntPtrType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"iptr", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( IntPtrType );
	
	OilTypeDefinition * UInt8Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u8", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt8Type );
	
	OilTypeDefinition * UInt16Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u16", 2, 2, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt16Type );
	
	OilTypeDefinition * UInt32Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u32", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt32Type );
	
	OilTypeDefinition * UInt64Type = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"u64", 8, 8, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UInt64Type );
	
	OilTypeDefinition * UIntPtrType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"uptr", 4, 4, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( UIntPtrType );
	
	//OilImplementBlock * BoolPrincipalImplementBlock = new OilImplementBlock ( new OilTypeRef ( U"bool" ) );
	//BoolPrincipalImplementBlock -> AddFunction (  );
	
	//RootNS.AddTypeDefinition ( BoolType );
	
	return true;
	
}

