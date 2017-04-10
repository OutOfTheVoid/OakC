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

#include <Compilation/Targets.h>

#include <Logging/Logging.h>

#ifndef NULL
	#define NULL nullptr
#endif

bool AddTypesX86_32 ( OilNamespaceDefinition & RootNS, TargetArchFlags Flags );
bool AddTypesX86_64 ( OilNamespaceDefinition & RootNS, TargetArchFlags Flags );

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS );

OilTraitDefinition * BuildWildcardBinOpTrait ( const std :: u32string & Name, const std :: u32string TraitFuncName );

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

OilTraitDefinition * BuildWildcardBinOpTrait ( const std :: u32string & Name, const std :: u32string TraitFuncName )
{
	
	OilTemplateDefinition * TraitTemplate = new OilTemplateDefinition ();
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RHS_T" ) );
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RESULT_T" ) );
	OilFunctionParameterList * PrincipalFunctionParams = new OilFunctionParameterList ();
	PrincipalFunctionParams -> AddParameter ( new OilFunctionParameter ( U"LHS", new OilTypeRef ( OilTypeRef :: kReference, new OilTypeRef ( U"Self" ) ), false ) );
	PrincipalFunctionParams -> AddParameter ( new OilFunctionParameter ( U"RHS", new OilTypeRef ( OilTypeRef :: kReference, new OilTypeRef ( U"RHS_T" ) ), false ) );
	OilTraitFunction * PrincipalFunction = new OilTraitFunction ( TraitFuncName, PrincipalFunctionParams, new OilTypeRef ( U"RESULT_T" ) );
	return new OilTraitDefinition ( Name, & PrincipalFunction, 1, NULL, 0, TraitTemplate );
	
}

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS )
{
	
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Add", U"op_add" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Subtract", U"op_subtract" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Multiplu", U"op_multiply" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Divide", U"op_divide" ) );
	
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

