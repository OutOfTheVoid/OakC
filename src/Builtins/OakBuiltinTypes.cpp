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

OilTraitDefinition * CreateCompositeWildcardBinOpCompositeTrait ( const std :: u32string & Name, const std :: u32string RequiredTraitNameList [], uint32_t RequiredTraitCount )
{
	
	OilTemplateDefinition * TraitTemplate = new OilTemplateDefinition ();
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RHS_T" ) );
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RESULT_T" ) );
	
	OilTypeRef ** RequiredTraitRefs = new OilTypeRef * [ RequiredTraitCount ];
	
	for ( uint32_t I = 0; I < RequiredTraitCount; I ++ )
	{
		
		OilTypeRef * TemplateTypes [ 2 ] = { new OilTypeRef ( U"RHS_T" ), new OilTypeRef ( U"RESULT_T" ) };
		
		RequiredTraitRefs [ I ] = new OilTypeRef ( RequiredTraitNameList [ I ], new OilTemplateSpecification ( TemplateTypes, 2 ) );
		
	}
	
	OilTraitDefinition * OutTrait = new OilTraitDefinition ( Name, RequiredTraitRefs, RequiredTraitCount, NULL, 0, NULL, 0, TraitTemplate, true );
	
	delete [] RequiredTraitRefs;
	
	return OutTrait;
	
}

OilTraitDefinition * CreateCompositeLogicalBinOpCompositeTrait ( const std :: u32string & Name, const std :: u32string RequiredTraitNameList [], uint32_t RequiredTraitCount )
{
	
	OilTemplateDefinition * TraitTemplate = new OilTemplateDefinition ();
	TraitTemplate -> AddParameter ( new OilTemplateDefinitionParameter ( U"RHS_T" ) );
	
	OilTypeRef * *RequiredTraitRefs = new OilTypeRef * [ RequiredTraitCount ];
	
	for ( uint32_t I = 0; I < RequiredTraitCount; I ++ )
	{
		
		OilTypeRef * TemplateTypes = new OilTypeRef ( U"RESULT_T" );
		
		RequiredTraitRefs [ I ] = new OilTypeRef ( RequiredTraitNameList [ I ], new OilTemplateSpecification ( & TemplateTypes, 1 ) );
		
	}
	
	OilTraitDefinition * OutTrait = new OilTraitDefinition ( Name, RequiredTraitRefs, RequiredTraitCount, NULL, 0, NULL, 0, TraitTemplate, true );
	
	delete [] RequiredTraitRefs;
	
	return OutTrait;
	
}

bool AddUniversalTypes ( OilNamespaceDefinition & RootNS )
{
	
	/*RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"Add", U"op_add" ) );
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
	RootNS.AddTraitDefinition ( BuildWildcardBinOpTrait ( U"LogicalOr", U"op_logical_or" ) );*/
	
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
	
	const std :: u32string UniqueComparableRequirements [] = { U"CompareGT", U"CompareLT" };
	RootNS.AddTraitDefinition ( CreateCompositeLogicalBinOpCompositeTrait ( U"UniqueComparable", UniqueComparableRequirements, 2 ) );
	
	const std :: u32string DuplicateComparableRequirements [] = { U"UniqueComparable", U"CompareGTorEq", U"CompareLTorEq" };
	RootNS.AddTraitDefinition ( CreateCompositeLogicalBinOpCompositeTrait ( U"DuplicateComparable", DuplicateComparableRequirements, 3 ) );
	
	const std :: u32string CompleteComparableRequirements [] = { U"DuplicateComparable", U"CompareEq" };
	RootNS.AddTraitDefinition ( CreateCompositeLogicalBinOpCompositeTrait ( U"CompleteComparable", CompleteComparableRequirements, 2 ) );
	
	const std :: u32string SteppingRequirements [] = { U"Increment", U"Decrement" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"Stepping", SteppingRequirements, 2 ) );
	
	const std :: u32string PartialCountingRequirements [] = { U"Add", U"Subtract" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"PartialCounting", SteppingRequirements, 2 ) );
	
	const std :: u32string CountingRequirements [] = { U"Stepping", U"PartialCounting" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"Counting", CountingRequirements, 2 ) );
	
	const std :: u32string ScalableRequirements [] = { U"Multiply", U"Divide" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"Scalable", ScalableRequirements, 2 ) );
	
	const std :: u32string ModularScalableRequirements [] = { U"Scalable", U"Modulus" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"ModularScalable", ModularScalableRequirements, 2 ) );
	
	const std :: u32string ArithmeticRequirements [] = { U"Scalable", U"Counting" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"Arithmetic", ArithmeticRequirements, 2 ) );
	
	const std :: u32string ModularArithmeticRequirements [] = { U"Arithmetic", U"Modulus" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"ModularArithmetic", ModularArithmeticRequirements, 2 ) );
	
	const std :: u32string NumericRequirements [] = { U"ModularArithmetic", U"CompleteComparable" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"Numeric", NumericRequirements, 2 ) );
	
	const std :: u32string PartialBitsetRequirements [] = { U"BitwiseNot", U"BitwiseXor", U"BitwiseOr", U"BitwiseAnd" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"PartialBitset", PartialBitsetRequirements, 4 ) );
	
	const std :: u32string ShiftRequirements [] = { U"LeftShift", U"RightShiftL", U"RightShiftA" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"Shifting", ShiftRequirements, 3 ) );
	
	const std :: u32string CompleteBitsetRequirements [] = { U"PartialBitsetRequirements", U"Shifting" };
	RootNS.AddTraitDefinition ( CreateCompositeWildcardBinOpCompositeTrait ( U"CompleteBitset", CompleteBitsetRequirements, 2 ) );
	
	//const std :: u32string IntegerRequirements [] = {  };
	
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

