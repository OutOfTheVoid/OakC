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

OilTraitDefinition * BuildWildcardBinOpTrait ( const std :: u32string & Name, const std :: u32string & TraitFuncName );
OilTraitDefinition * BuildLogicalBinOpTrait ( const std :: u32string & Name, const std :: u32string & TraitFuncName );

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

OilTraitDefinition * BuildWildcardBinOpTrait ( const std :: u32string & Name, const std :: u32string & TraitFuncName )
{
	
	OilTemplateDefinition * TraitTemplate = new OilTemplateDefinition ();
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RHS_T" ) );
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RESULT_T" ) );
	OilFunctionParameterList * PrincipalFunctionParams = new OilFunctionParameterList ();
	PrincipalFunctionParams -> AddParameter ( new OilFunctionParameter ( U"LHS", new OilTypeRef ( OilTypeRef :: kReference, new OilTypeRef ( U"Self" ) ), false ) );
	PrincipalFunctionParams -> AddParameter ( new OilFunctionParameter ( U"RHS", new OilTypeRef ( OilTypeRef :: kReference, new OilTypeRef ( U"RHS_T" ) ), false ) );
	OilTraitFunction * PrincipalFunction = new OilTraitFunction ( TraitFuncName, PrincipalFunctionParams, new OilTypeRef ( U"RESULT_T" ) );
	return new OilTraitDefinition ( Name, NULL, 0, & PrincipalFunction, 1, NULL, 0, TraitTemplate, true );
	
}

OilTraitDefinition * BuildLogicalBinOpTrait ( const std :: u32string & Name, const std :: u32string & TraitFuncName )
{
	
	OilTemplateDefinition * TraitTemplate = new OilTemplateDefinition ();
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RHS_T" ) );
	OilFunctionParameterList * PrincipalFunctionParams = new OilFunctionParameterList ();
	PrincipalFunctionParams -> AddParameter ( new OilFunctionParameter ( U"LHS", new OilTypeRef ( OilTypeRef :: kReference, new OilTypeRef ( U"Self" ) ), false ) );
	PrincipalFunctionParams -> AddParameter ( new OilFunctionParameter ( U"RHS", new OilTypeRef ( OilTypeRef :: kReference, new OilTypeRef ( U"RHS_T" ) ), false ) );
	OilTraitFunction * PrincipalFunction = new OilTraitFunction ( TraitFuncName, PrincipalFunctionParams, new OilTypeRef ( U"bool" ) );
	return new OilTraitDefinition ( Name, NULL, 0, & PrincipalFunction, 1, NULL, 0, TraitTemplate, true );
	
}

OilTraitDefinition * BuildWildcardUnOpTrait ( const std :: u32string & Name, const std :: u32string & TraitFuncName )
{
	
	OilTemplateDefinition * TraitTemplate = new OilTemplateDefinition ();
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RESULT_T" ) );
	OilFunctionParameterList * PrincipalFunctionParams = new OilFunctionParameterList ();
	PrincipalFunctionParams -> AddParameter ( new OilFunctionParameter ( U"LHS", new OilTypeRef ( OilTypeRef :: kReference, new OilTypeRef ( U"Self" ) ), false ) );
	OilTraitFunction * PrincipalFunction = new OilTraitFunction ( TraitFuncName, PrincipalFunctionParams, new OilTypeRef ( U"RESULT_T" ) );
	return new OilTraitDefinition ( Name, NULL, 0, & PrincipalFunction, 1, NULL, 0, TraitTemplate, true );
	
}

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS )
{
	
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Add", U"op_add" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Subtract", U"op_subtract" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Multiply", U"op_multiply" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Divide", U"op_divide" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Modulus", U"op_modulus" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"LeftShift", U"op_leftshift" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"RightShiftA", U"op_rightshift_arithmetic" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"RightShiftL", U"op_rightshift_logical" ) );
	
	RootNS.AddTraitDefinition ( BuildLogicalBinOpTrait ( U"CompareGT", U"op_greaterthan" ) );
	RootNS.AddTraitDefinition ( BuildLogicalBinOpTrait ( U"CompareLT", U"op_lessthan" ) );
	RootNS.AddTraitDefinition ( BuildLogicalBinOpTrait ( U"CompareGTorEq", U"op_greaterthan_or_equal" ) );
	RootNS.AddTraitDefinition ( BuildLogicalBinOpTrait ( U"CompareLTorEq", U"op_lessthan_or_equal" ) );
	RootNS.AddTraitDefinition ( BuildLogicalBinOpTrait ( U"CompareNEq", U"op_not_equal" ) );
	RootNS.AddTraitDefinition ( BuildLogicalBinOpTrait ( U"CompareEq", U"op_equal" ) );
	
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"BitwiseAnd", U"op_bitwise_and" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"BitwiseOr", U"op_bitwise_or" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"BitwiseXor", U"op_bitwise_xor" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"LogicalAnd", U"op_logical_and" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"LogicalOr", U"op_logical_or" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Assign", U"op_assign" ) );
	
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundAdd", U"op_compound_add" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundSubtract", U"op_compound_subtract" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundMultiply", U"op_compound_multiply" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundDivide", U"op_compound_divide" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundModulus", U"op_compound_modulus" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundLeftShift", U"op_compound_leftshift" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundRightShiftA", U"op_compound_rightshift_arithmetic" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundRightShiftL", U"op_compound_rightshift_logical" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundBitwiseAnd", U"op_compound_bitwise_and" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundBitwiseOr", U"op_compound_bitwise_or" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundBitwiseXor", U"op_compound_bitwise_xor" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundLogicalAnd", U"op_compound_logical_and" ) );
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"CompoundLogicalOr", U"op_compound_logical_or" ) );
	
	RootNS.AddTraitDefinition ( BuildWildcardUnOpTrait ( U"Increment", U"op_increment" ) );
	RootNS.AddTraitDefinition ( BuildWildcardUnOpTrait ( U"Decrement", U"op_decrement" ) );
	RootNS.AddTraitDefinition ( BuildWildcardUnOpTrait ( U"BitwiseNot", U"op_bitwise_not" ) );
	RootNS.AddTraitDefinition ( BuildWildcardUnOpTrait ( U"LogicalNot", U"op_logical_not" ) );
	RootNS.AddTraitDefinition ( BuildWildcardUnOpTrait ( U"UnaryPositive", U"op_unary_positive" ) );
	RootNS.AddTraitDefinition ( BuildWildcardUnOpTrait ( U"UnaryNegative", U"op_unary_negative" ) );
	RootNS.AddTraitDefinition ( BuildWildcardUnOpTrait ( U"ArrayAccess", U"op_array_access" ) );
	
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

