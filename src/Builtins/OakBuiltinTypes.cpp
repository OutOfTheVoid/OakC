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
	
	//RootNS.AddTypeDefinition (  );
	
	return true;
	
}

bool AddTypesX86_64 ( OilNamespaceDefinition & RootNS )
{
	
	OilTypeDefinition * BoolType = new OilTypeDefinition ( new OilBuiltinStructDefinition ( U"bool", 1, 1, OilBuiltinStructDefinition :: kTypeFlag_None ) );
	RootNS.AddTypeDefinition ( BoolType );
	
	//OilImplementBlock * BoolPrincipalImplementBlock = new OilImplementBlock ( new OilTypeRef ( U"bool" ) );
	//BoolPrincipalImplementBlock -> AddFunction (  );
	
	//RootNS.AddTypeDefinition ( BoolType );
	
	return true;
	
}

