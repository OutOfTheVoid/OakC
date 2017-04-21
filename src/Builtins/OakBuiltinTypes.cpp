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

#include <Compilation/Targets.h>
#include <Compilation/CompilationUnit.h>

#include <Logging/Logging.h>

#ifndef NULL
	#define NULL nullptr
#endif

bool AddTypesX86_32 ( OilNamespaceDefinition & RootNS, TargetArchFlags Flags );
bool AddTypesX86_64 ( OilNamespaceDefinition & RootNS, TargetArchFlags Flags );

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS );

bool OakAddBuiltinTypes ( OilNamespaceDefinition & RootNS, TargetArchID Arch, TargetArchFlags Flags )
{
	
	if ( ! AddUniversalTypes ( RootNS ) )
		return false;
	
	switch ( Arch )
	{
		
		case kTargetArch_X86_32:
			return AddTypesX86_32 ( RootNS, Flags );
			
		case kTargetArch_X86_64:
			return AddTypesX86_64 ( RootNS, Flags );
		
	}
	
	LOG_FATALERROR_NOFILE ( "Unsupported target architecture!" );
	
	return false;
	
}

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS )
{
	
	return true;
	
}

bool AddTypesX86_32 ( OilNamespaceDefinition & RootNS, TargetArchFlags Flags )
{
	
	// TODO
	(void) RootNS;
	(void) Flags;
	
	//RootNS.AddTypeDefinition (  );
	
	return true;
	
}

bool AddTypesX86_64 ( OilNamespaceDefinition & RootNS, TargetArchFlags Flags )
{
	// TODO
	(void) RootNS;
	(void) Flags;
	
	//OilTypeDefinition * BoolType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"bool", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	
	//RootNS.AddTypeDefinition ( BoolType );
	
	return true;
	
}

