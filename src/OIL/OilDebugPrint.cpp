#include <OIL/OilDebugPrint.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilMethodParameterList.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateSpecification.h>
#include <OIL/OilStatementBody.h>
#include <OIL/IOilStatement.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraitFunction.h>
#include <OIL/OilTraitMethod.h>
#include <OIL/OilExpression.h>
#include <OIL/IOilOperator.h>
#include <OIL/OilBinaryOperator.h>
#include <OIL/OilUnaryOperator.h>
#include <OIL/OilBoolLiteral.h>
#include <OIL/OilAllusion.h>
#include <OIL/OilIntegerLiteral.h>
#include <OIL/OilFloatLiteral.h>
#include <OIL/OilStringLiteral.h>
#include <OIL/OilCharLiteral.h>
#include <OIL/OilArrayLiteral.h>
#include <OIL/OilReturn.h>
#include <OIL/OilImplicitLocalInitialization.h>
#include <OIL/OilImplicitBindingInitialization.h>
#include <OIL/OilIfElse.h>
#include <OIL/OilWhileLoop.h>
#include <OIL/OilDoWhileLoop.h>
#include <OIL/OilBreak.h>
#include <OIL/OilLoop.h>
#include <OIL/OilImplementBlock.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilMethodDefinition.h>
#include <OIL/OilBuiltinStructDefinition.h>
#include <OIL/OilConstStatement.h>
#include <OIL/OilTypeAlias.h>
#include <OIL/OilFunctionCallParameterList.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

#define OIL_PRINT_INDENTSTRING "    "

void OilPrintNamespace ( const OilNamespaceDefinition & Namespace, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintNamespaceMembers ( const OilNamespaceDefinition & Namespace, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintStruct ( const OilStructDefinition & Struct, uint32_t Indent, const OilPrintOptions & PrintOptions );
std :: string OilStringTemplateDefinition ( const OilTemplateDefinition & Template, const OilPrintOptions & PrintOptions );
std :: string OilStringTemplateSpecification ( const OilTemplateSpecification & Template, const OilPrintOptions & PrintOptions );
void OilPrintFunction ( const OilFunctionDefinition & Function, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintMethod ( const OilMethodDefinition & Method, uint32_t Indent, const OilPrintOptions & PrintOptions );
std :: string OilStringTypeRef ( const OilTypeRef & Ref, const OilPrintOptions & PrintOptions );
void OilPrintStatementBody ( const OilStatementBody & Body, uint32_t Indent, const OilPrintOptions & PrintOptions, const OilNamespaceDefinition * InitializedBindingContainer = NULL );
void OilPrintBindingStatement ( const OilBindingStatement & Binding, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintTrait ( const OilTraitDefinition & Trait, uint32_t Indent, const OilPrintOptions & PrintOptions );
std :: string OilStringTraitFunction ( const OilTraitFunction & Function, const OilPrintOptions & PrintOptions );
std :: string OilStringTraitMethod ( const OilTraitMethod & Method, const OilPrintOptions & PrintOptions );
std :: string OilStringExpression ( const OilExpression & Expression, const OilPrintOptions & PrintOptions );
std :: string OilStringPrimary ( const IOilPrimary & Primary, const OilPrintOptions & PrintOptions );
std :: string OilStringOperator ( const IOilOperator & Operator, const OilPrintOptions & PrintOptions );
std :: string OilStringFunctionCallParameterList ( const OilFunctionCallParameterList & List, const OilPrintOptions & PrintOptions );
void OilPrintIfElse ( const OilIfElse & IfElse, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintWhileLoop ( const OilWhileLoop & Loop, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintDoWhileLoop ( const OilWhileLoop & Loop, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintBreak ( const OilBreak & Break, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintLoop ( const OilLoop & Loop, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintImplementBlock ( const OilImplementBlock & Block, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintTypeDefinition ( const OilTypeDefinition & TypeDefinition, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintBuiltinStruct ( const OilBuiltinStructDefinition & StructDefinition, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintConstStatement ( const OilConstStatement & Constant, uint32_t Indent, const OilPrintOptions & PrintOptions );
void OilPrintTypeAlias ( const OilTypeAlias & Alias, uint32_t Indent, const OilPrintOptions & PrintOptions );

void OilPrint ( const OilNamespaceDefinition & RootNS, const OilPrintOptions & PrintOptions )
{
	
	LOG_VERBOSE ( "OIL TREE:" );
	
	OilPrintNamespace ( RootNS, 0, PrintOptions );
	
}

void OilPrintNamespaceMembers ( const OilNamespaceDefinition & Namespace, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	uint64_t TempCount = Namespace.GetBindingStatementCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilBindingStatement * Binding = Namespace.GetBindingStatement ( I );
		
		OilPrintBindingStatement ( * Binding, Indent, PrintOptions );
		
	}
	
	TempCount = Namespace.GetConstStatementCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilConstStatement * Constant = Namespace.GetConstStatement ( I );
		
		OilPrintConstStatement ( * Constant, Indent, PrintOptions );
		
	}
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "STATIC INITIALIZER BODY:";
	
	LOG_VERBOSE ( PrintString );
	
	OilPrintStatementBody ( Namespace.GetImplicitInitializationBody (), Indent, PrintOptions, & Namespace );
	
	TempCount = Namespace.GetTraitDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilTraitDefinition * Definition = Namespace.GetTraitDefinition ( I );
		
		if ( ( ! Definition -> IsBuiltin () ) || PrintOptions.PrintBuiltins )
			OilPrintTrait ( * Definition, Indent, PrintOptions );
		
	}
	
	TempCount = Namespace.GetTypeAliasCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilTypeAlias * Alias = Namespace.GetTypeAlias ( I );
		
		if ( ( ! Alias -> IsBuiltin () ) || PrintOptions.PrintBuiltins )
			OilPrintTypeAlias ( * Alias, Indent, PrintOptions );
		
	}
	
	TempCount = Namespace.GetTypeDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilTypeDefinition * Definition = Namespace.GetTypeDefinition ( I );
		
		if ( ( ! Definition -> IsBuiltinType () ) || PrintOptions.PrintBuiltins )
			OilPrintTypeDefinition ( * Definition, Indent, PrintOptions );
		
	}
	
	TempCount = Namespace.GetFunctionDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilFunctionDefinition * Definition = Namespace.GetFunctionDefinition ( I );
		
		OilPrintFunction ( * Definition, Indent, PrintOptions );
		
	}
	
	TempCount = Namespace.GetSubNamespaceDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilNamespaceDefinition * Definition = Namespace.GetNamespaceDefinition ( I );
		
		OilPrintNamespace ( * Definition, Indent, PrintOptions );
		
	}
	
	if ( Namespace.GetUnresolvedImplementBlockCount () != 0 )
	{
		
		PrintString = "";
		
		for ( uint32_t I = 0; I < Indent; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += "UNRESOLVED IMPLEMENT BLOCKS:";
		
		LOG_VERBOSE ( PrintString );
		
		for ( uint32_t I = 0; I < Namespace.GetUnresolvedImplementBlockCount (); I ++ )
			OilPrintImplementBlock ( * Namespace.GetUnresolvedImplementBlock ( I ), Indent, PrintOptions );
		
	}
	
}

void OilPrintNamespace ( const OilNamespaceDefinition & Namespace, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[NAMESPACE \"";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Namespace.GetID () );
	PrintString += "\"]\n";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
	
	OilPrintNamespaceMembers ( Namespace, Indent + 1, PrintOptions );
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintTrait ( const OilTraitDefinition & Trait, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
		PrintString += "[TRAIT \"";
	
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Trait.GetName () );
	PrintString += "\"";
	
	if ( Trait.IsTemplated () )
	{
		
		PrintString += " template: ";
		PrintString += OilStringTemplateDefinition ( * Trait.GetTemplateDefinition (), PrintOptions );
		
	}
	
	if ( Trait.IsBuiltin () && PrintOptions.HighlightBuiltins )
		PrintString += "] BUILTIN\n";
	else
		PrintString += "]\n";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
	
	PrintString = "";
	
	for ( uint32_t J = 0; J < Trait.GetRequiredTraitCount (); J ++ )
	{
		
		for ( uint32_t I = 0; I < Indent + 1; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += "[REQUIRE: ";
		
		PrintString += OilStringTypeRef ( * Trait.GetRequiredTrait ( J ), PrintOptions );
		PrintString += "]";
		LOG_VERBOSE ( PrintString );
		
		PrintString = "";
		
	}
	
	for ( uint32_t J = 0; J < Trait.GetFunctionCount (); J ++ )
	{
		
		for ( uint32_t I = 0; I < Indent + 1; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += OilStringTraitFunction ( * Trait.GetTraitFunction ( J ), PrintOptions );
		LOG_VERBOSE ( PrintString );
		
		PrintString = "";
		
	}
	
	for ( uint32_t J = 0; J < Trait.GetMethodCount (); J ++ )
	{
		
		for ( uint32_t I = 0; I < Indent + 1; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += OilStringTraitMethod ( * Trait.GetTraitMethod ( J ), PrintOptions );
		LOG_VERBOSE ( PrintString );
		
		PrintString = "";
		
	}
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

std :: string OilStringTraitMethod ( const OilTraitMethod & Method, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString = "[METHOD ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Method.GetName () );
	
	if ( Method.IsTemplated () )
		PrintString += std :: string ( " Template: " ) + OilStringTemplateDefinition ( * Method.GetTemplateDefinition (), PrintOptions );
	
	const OilMethodParameterList * ParamList = Method.GetParameterList ();
	
	if ( ParamList -> GetParameterCount () != 0 )
	{
		
		PrintString += ParamList -> IsSelfReference () ? " Parameters: ( &self, " : " Parameters: ( self, ";
		
		for ( uint32_t I = 0; I < ParamList -> GetParameterCount (); I ++ )
		{
			
			const OilFunctionParameter * Parameter = ParamList -> GetFunctionParameter ( I );
			
			PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Parameter -> GetName () );
			
			PrintString += ": ";
			
			PrintString += OilStringTypeRef ( * Parameter -> GetType (), PrintOptions );
			
			if ( I != ParamList -> GetParameterCount () - 1 )
				PrintString += ", ";
			
		}
		
		PrintString += " )";
		
	}
	else
		PrintString += ParamList -> IsSelfReference () ? " Parameters: ( &self )" : " Parameters: ( self )";
	
	if ( Method.HasReturnType () )
	{
		
		PrintString += " Return: ";
		PrintString += OilStringTypeRef ( * Method.GetReturnType (), PrintOptions );
		
	}
	
	PrintString += "]";
	
	return PrintString;
	
}

std :: string OilStringTraitFunction ( const OilTraitFunction & Function, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString = "[FUNCTION ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Function.GetName () );
	
	if ( Function.IsTemplated () )
		PrintString += std :: string ( " Template: " ) + OilStringTemplateDefinition ( * Function.GetTemplateDefinition (), PrintOptions );
	
	const OilFunctionParameterList * ParamList = Function.GetParameterList ();
	
	if ( ParamList -> GetParameterCount () != 0 )
	{
		
		PrintString += " Parameters: (";
		
		for ( uint32_t I = 0; I < ParamList -> GetParameterCount (); I ++ )
		{
			
			const OilFunctionParameter * Parameter = ParamList -> GetFunctionParameter ( I );
			
			PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Parameter -> GetName () );
			
			PrintString += ": ";
			
			PrintString += OilStringTypeRef ( * Parameter -> GetType (), PrintOptions );
			
			if ( I != ParamList -> GetParameterCount () - 1 )
				PrintString += ", ";
			
		}
		
		PrintString += " )";
		
	}
	
	if ( Function.HasReturnType () )
	{
		
		PrintString += " Return: ";
		PrintString += OilStringTypeRef ( * Function.GetReturnType (), PrintOptions );
		
	}
	
	PrintString += "]";
	
	return PrintString;
	
}

void OilPrintIfElse ( const OilIfElse & IfElse, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[IF Condition: ";
	PrintString += OilStringExpression ( * IfElse.GetIfClauseConditionExpression (), PrintOptions );
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	PrintString = "";
	
	OilPrintStatementBody ( * IfElse.GetIfClauseStatementBody (), Indent, PrintOptions );
	
	for ( uint32_t I = 0; I < IfElse.GetElseIfClauseCount (); I ++ )
	{
		
		for ( uint32_t I = 0; I < Indent; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += "[ELSE IF Condition: ";
		PrintString += OilStringExpression ( * IfElse.GetElseIfClauseConditionExpression ( I ), PrintOptions );
		PrintString += "]";
		
		LOG_VERBOSE ( PrintString );
		PrintString = "";
		
		OilPrintStatementBody ( * IfElse.GetElseIfClauseStatementBody ( I ), Indent, PrintOptions );
		
	}
	
	if ( IfElse.HasElseClause () )
	{
		
		for ( uint32_t I = 0; I < Indent; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += "[ELSE]";
		
		LOG_VERBOSE ( PrintString );
		PrintString = "";
		
		OilPrintStatementBody ( * IfElse.GetElseClauseStatementBody (), Indent, PrintOptions );
		
	}
	
}

void OilPrintWhileLoop ( const OilWhileLoop & Loop, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[WHILE Condition: ";
	PrintString += OilStringExpression ( * Loop.GetConditionExpression (), PrintOptions );
	
	if ( Loop.HasLoopLabel () )
	{
		
		PrintString += ", Label: ";
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Loop.GetLoopLabel () );
		
	}
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	PrintString = "";
	
	OilPrintStatementBody ( * Loop.GetStatementBody (), Indent, PrintOptions );
	
}

void OilPrintLoop ( const OilLoop & Loop, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[LOOP";
	
	if ( Loop.HasLoopLabel () )
	{
		
		PrintString += ", Label: ";
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Loop.GetLoopLabel () );
		
	}
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	PrintString = "";
	
	OilPrintStatementBody ( * Loop.GetStatementBody (), Indent, PrintOptions );
	
}

void OilPrintDoWhileLoop ( const OilDoWhileLoop & Loop, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[DO";
	
	if ( Loop.HasLoopLabel () )
	{
		
		PrintString += " Label: ";
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Loop.GetLoopLabel () );
		
	}
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	PrintString = "";
	
	OilPrintStatementBody ( * Loop.GetStatementBody (), Indent, PrintOptions );
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[WHILE Condition: ";
	PrintString += OilStringExpression ( * Loop.GetConditionExpression (), PrintOptions );
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintBreak ( const OilBreak & Break, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	(void) PrintOptions;
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[BREAK";
	
	if ( Break.HasLoopLabel () )
	{
		
		PrintString += " Label: ";
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Break.GetLoopLabel () );
		
	}
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintTraitImplementations ( const OilTypeDefinition & Root, std :: vector <std :: u32string> & Path, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	uint32_t NamespaceCount = Root.GetNamespaceCountAt ( & Path [ 0 ], Path.size () );
	
	if ( NamespaceCount == 0 )
	{
		
		std :: vector <const OilImplementBlock *> Blocks;
		
		Root.FindTraitImplementBlocks ( & Path [ 0 ], Path.size (), Blocks );
		
		for ( uint32_t I = 0; I < Blocks.size (); I ++ )
			OilPrintImplementBlock ( * Blocks [ I ], Indent, PrintOptions );
		
		return;
		
	}
	
	for ( uint32_t I = 0; I < NamespaceCount; I ++ )
	{
		
		std :: u32string SubNamespace = Root.GetImplementNamespaceAt ( & Path [ 0 ], Path.size (), I );
		Path.push_back ( SubNamespace );
		
		OilPrintTraitImplementations ( Root, Path, Indent, PrintOptions );
		
		Path.pop_back ();
		
	}
	
}

void OilPrintTypeDefinition ( const OilTypeDefinition & TypeDefinition, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[TYPE \"";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( TypeDefinition.GetName () );
	PrintString += "\"]\n";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
	
	if ( ! TypeDefinition.IsBuiltinStructure () )
	{
		
		if ( TypeDefinition.GetStructDefinition () != NULL )
			OilPrintStruct ( * TypeDefinition.GetStructDefinition (), Indent + 1, PrintOptions );
		
	}
	else
	{
		
		if ( TypeDefinition.GetBuiltinStructDefinition () != NULL )
			OilPrintBuiltinStruct ( * TypeDefinition.GetBuiltinStructDefinition (), Indent + 1, PrintOptions );
		
	}
	
	std :: vector <const OilImplementBlock *> Blocks;
	TypeDefinition.GetPrincipalImplementBlocks ( Blocks );
	
	for ( uint32_t I = 0; I < Blocks.size (); I ++ )
		OilPrintImplementBlock ( * Blocks [ I ], Indent + 1, PrintOptions );
	
	std :: vector <std :: u32string> RelativeNamePath;
	
	OilPrintTraitImplementations ( TypeDefinition, RelativeNamePath, Indent + 1, PrintOptions );
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintBuiltinStruct ( const OilBuiltinStructDefinition & Struct, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[BUILIN STRUCT ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Struct.GetName () );
	PrintString += " Size: ";
	PrintString += std :: to_string ( Struct.GetSize () );
	PrintString += ", Alignment: ";
	PrintString += std :: to_string ( Struct.GetAlignment () );
	
	if ( Struct.IsTemplated () )
	{
		
		PrintString += ", Template: ";
		PrintString += OilStringTemplateDefinition ( * Struct.GetTemplateDefinition (), PrintOptions );
		
	}
	
	if ( Struct.GetFlags () != 0 )
	{
		
		if ( ( Struct.GetFlags () & OilBuiltinStructDefinition :: kTypeFlag_RequiredAlignment ) != 0 )
			PrintString += ", alignment_required";
		
	}
	
	if ( Struct.HasUnderlyingStructure () )
	{
		
		PrintString += ", underlying_structure]\n";
		LOG_VERBOSE ( PrintString );
		
		OilPrintStruct ( * Struct.GetUnderlyingStructure (), Indent + 1, PrintOptions );
		
	}
	else
	{
		
		PrintString += "]";
		LOG_VERBOSE ( PrintString );
		
	}
	
}

void OilPrintStruct ( const OilStructDefinition & Struct, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[STRUCT";
	
	if ( Struct.IsTemplated () )
	{
		
		PrintString += " Template: ";
		PrintString += OilStringTemplateDefinition ( * Struct.GetTemplateDefinition (), PrintOptions );
		PrintString += "]\n";
		
	}
	else
		PrintString += "]\n";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
	
	for ( uint32_t I = 0; I < Struct.GetBindingCount (); I ++ )
	{
		
		const OilStructBinding * Binding = Struct.GetBinding ( I );
		
		PrintString = "";
	
		for ( uint32_t I = 0; I < Indent + 1; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += "[BINDING ";
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Binding -> GetName () );
		PrintString += ": ";
		PrintString += OilStringTypeRef ( * Binding -> GetTypeRef (), PrintOptions );
		PrintString += "]";
		
		LOG_VERBOSE ( PrintString );
		
	}
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintImplementBlock ( const OilImplementBlock & Block, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[IMPLEMENT ";
	PrintString += OilStringTypeRef ( * Block.GetImplementedType (), PrintOptions );
	
	if ( Block.IsForTrait () )
	{
		
		PrintString += " for ";
		PrintString += OilStringTypeRef ( * Block.GetForTrait (), PrintOptions );
		
	}
	
	if ( Block.HasWhereDefinition () )
	{
		
		PrintString += " where ";
		PrintString += OilStringTemplateDefinition ( * Block.GetWhereDefinition (), PrintOptions );
		
	}
	
	PrintString += "]\n";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
	PrintString = "";
	
	for ( uint32_t I = 0; I < Block.GetFunctionCount (); I ++ )
		OilPrintFunction ( * Block.GetFunction ( I ), Indent + 1, PrintOptions );
	
	for ( uint32_t I = 0; I < Block.GetMethodCount (); I ++ )
		OilPrintMethod ( * Block.GetMethod ( I ), Indent + 1, PrintOptions );
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

std :: string OilStringTemplateDefinition ( const OilTemplateDefinition & Template, const OilPrintOptions & PrintOptions )
{
	
	std :: string OutString;
	
	OutString += "<";
	
	uint32_t ParamCount = Template.GetTemplateParameterCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		const OilTemplateDefinitionParameter * Param = Template.GetTemplateParameter ( I );
		
		OutString += CodeConversion :: ConvertUTF32ToUTF8 ( Param -> GetName () );
		
		if ( Param -> IsRestricted () )
		{
			
			OutString += ": ";
			
			for ( uint32_t I = 0; I < Param -> GetRestrictionCount (); I ++ )
			{
				
				OutString += OilStringTypeRef ( * Param -> GetRestriction ( I ), PrintOptions );
				
				if ( I != Param -> GetRestrictionCount () - 1 )
					OutString += " + ";
				
			}
			
		}
		
		if ( I != ParamCount - 1 )
			OutString += ", ";
		
	}
	
	OutString += ">";
	
	return OutString;
	
}

std :: string OilStringFunctionCallParameterList ( const OilFunctionCallParameterList & List, const OilPrintOptions & PrintOptions )
{
	
	std :: string OutString = "(";
	
	for ( uint32_t I = 0; I < List.GetParameterCount (); I ++ )
	{
		
		OutString += " ";
		
		OutString += OilStringExpression ( * List.GetParameter ( I ), PrintOptions );
		
		OutString += ( I != List.GetParameterCount () - 1 ) ? ", " : " ";
		
	}
	
	OutString += ")";
	
	return OutString;
	
}

void OilPrintFunction ( const OilFunctionDefinition & Function, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[FUNCTION ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Function.GetName () );
	
	if ( Function.IsInline () || Function.IsPublic () )
	{
		
		PrintString += " {";
		
		if ( Function.IsPublic () )
			PrintString += " public";
		
		if ( Function.IsInline () )
			PrintString += " inline";
		
		PrintString += " }";
		
	}
	
	if ( Function.IsTemplated () )
	{
		
		PrintString += " Template: ";
		PrintString += OilStringTemplateDefinition ( * Function.GetTemplateDefinition (), PrintOptions );
		
	}
	
	const OilFunctionParameterList * ParamList = Function.GetParameterList ();
	
	if ( ParamList -> GetParameterCount () != 0 )
	{
		
		PrintString += " Parameters: (";
		
		for ( uint32_t I = 0; I < ParamList -> GetParameterCount (); I ++ )
		{
			
			const OilFunctionParameter * Parameter = ParamList -> GetFunctionParameter ( I );
			
			PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Parameter -> GetName () );
			
			PrintString += ": ";
			
			PrintString += OilStringTypeRef ( * Parameter -> GetType (), PrintOptions );
			
			if ( I != ParamList -> GetParameterCount () - 1 )
				PrintString += ", ";
			
		}
		
		PrintString += ")";
		
	}
	
	if ( Function.HasReturnType () )
	{
		
		PrintString += " Return Type: ";
		PrintString += OilStringTypeRef ( * Function.GetReturnType (), PrintOptions );
		
	}
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
	OilPrintStatementBody ( * Function.GetStatementBody (), Indent, PrintOptions );
	
}


void OilPrintMethod ( const OilMethodDefinition & Method, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[METHOD \"";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Method.GetName () );
	PrintString += "\"";
	
	if ( Method.IsInline () || Method.IsPublic () )
	{
		
		PrintString += " {";
		
		if ( Method.IsPublic () )
			PrintString += " public";
		
		if ( Method.IsInline () )
			PrintString += " inline";
		
		PrintString += " }";
		
	}
	
	if ( Method.IsTemplated () )
	{
		
		PrintString += " Template: ";
		PrintString += OilStringTemplateDefinition ( * Method.GetTemplateDefinition (), PrintOptions );
		
	}
	
	const OilMethodParameterList * ParamList = Method.GetParameterList ();
	
	if ( ParamList -> GetParameterCount () != 0 )
	{
		
		PrintString += ParamList -> IsSelfReference () ? " Parameters: ( &self, " : " Parameters: ( self, ";
		
		for ( uint32_t I = 0; I < ParamList -> GetParameterCount (); I ++ )
		{
			
			const OilFunctionParameter * Parameter = ParamList -> GetFunctionParameter ( I );
			
			PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Parameter -> GetName () );
			
			PrintString += ": ";
			
			PrintString += OilStringTypeRef ( * Parameter -> GetType (), PrintOptions );
			
			if ( I != ParamList -> GetParameterCount () - 1 )
				PrintString += ", ";
			
		}
		
		PrintString += " )";
		
	}
	else
		PrintString += ParamList -> IsSelfReference () ? " Parameters: ( &self )" : " Parameters: ( self )";
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
	OilPrintStatementBody ( * Method.GetStatementBody (), Indent, PrintOptions );
	
}

std :: string OilStringTypeRef ( const OilTypeRef & Ref, const OilPrintOptions & PrintOptions )
{
	
	if ( ! Ref.IsDirectType () )
	{
		
		if ( Ref.IsVoid () )
			return std :: string ( "(void)" );
		else
			return std :: string ( "&" ) + OilStringTypeRef ( * Ref.GetSubType (), PrintOptions ) + ")";
			
	}
	
	std :: string OutString = "(";
	
	if ( PrintOptions.ShowResolution )
		OutString += Ref.IsResolved () ? "resolved " : "unresolved ";
	
	if ( ! Ref.IsResolved () )
	{
		
		if ( Ref.IsNamespaced () )
		{
			
			for ( uint32_t I = 0; I < Ref.GetNamespaceNameCount (); I ++ )
			{
				
				OutString += CodeConversion :: ConvertUTF32ToUTF8 ( Ref.GetNamespaceName ( I ) );
				OutString += "::";
				
			}
			
		}
		
		OutString += CodeConversion :: ConvertUTF32ToUTF8 ( Ref.GetName () );
		
		if ( Ref.IsTemplated () )
			OutString += ":" + OilStringTemplateSpecification ( * Ref.GetTemplateSpecification (), PrintOptions );
		
	}
	else
	{
		
		if ( Ref.IsResolvedAsType () )
		{
			
			const OilTypeDefinition * Type = Ref.GetResolvedTypeDefinition ();
			
			std :: string PathString = CodeConversion :: ConvertUTF32ToUTF8 ( Type -> GetName () );
			
			if ( Ref.IsTemplated () )
				PathString += ":" + OilStringTemplateSpecification ( * Ref.GetTemplateSpecification (), PrintOptions );
			
			const OilNamespaceDefinition * ParentDef = Type -> GetParentNamespace ();
			const OilNamespaceDefinition * ParentParent = ParentDef -> GetParent ();
			
			while ( ParentParent != NULL )
			{
				
				PathString = CodeConversion :: ConvertUTF32ToUTF8 ( ParentDef -> GetID () ) + "::" + PathString;
				ParentDef = ParentParent;
				ParentParent = ParentDef -> GetParent ();
				
			}
			
			OutString += PathString;
			
		}
		else if ( Ref.IsResolvedAsTrait () )
		{
			
			const OilTraitDefinition * Trait = Ref.GetResolvedTraitDefinition ();
			
			std :: string PathString = CodeConversion :: ConvertUTF32ToUTF8 ( Trait -> GetName () );
			
			if ( Ref.IsTemplated () )
				PathString += ":" + OilStringTemplateSpecification ( * Ref.GetTemplateSpecification (), PrintOptions );
			
			const OilNamespaceDefinition * ParentDef = Trait -> GetParentNamespace ();
			const OilNamespaceDefinition * ParentParent = ParentDef -> GetParent ();
			
			while ( ParentParent != NULL )
			{
				
				PathString = CodeConversion :: ConvertUTF32ToUTF8 ( ParentDef -> GetID () ) + "::" + PathString;
				ParentDef = ParentParent;
				ParentParent = ParentDef -> GetParent ();
				
			}
			
			OutString += "::" + PathString;
			
		}
		else
			OutString += "template_param: " + CodeConversion :: ConvertUTF32ToUTF8 ( Ref.GetName () );
		
	}
	
	return OutString + ")";
	
}

std :: string OilStringTemplateSpecification ( const OilTemplateSpecification & Template, const OilPrintOptions & PrintOptions )
{
	
	std :: string OutString;
	
	OutString += "<";
	
	uint32_t ParamCount = Template.GetTypeRefCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OutString += OilStringTypeRef ( * Template.GetTypeRef ( I ), PrintOptions );
		
		if ( I != ParamCount - 1 )
			OutString += ", ";
		
	}
	
	OutString += ">";
	
	return OutString;
	
}

void OilPrintBindingStatement ( const OilBindingStatement & Binding, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[BINDING ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Binding.GetName () );
	
	PrintString += ": ";
	PrintString += OilStringTypeRef ( * Binding.GetType (), PrintOptions );
	
	if ( Binding.IsMutable () )
		PrintString += " ( mut )";
	
	if ( Binding.IsPublic () )
		PrintString += "( public )";
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintConstStatement ( const OilConstStatement & Constant, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[CONSTANT ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Constant.GetName () );
	
	PrintString += ": ";
	PrintString += OilStringTypeRef ( * Constant.GetType (), PrintOptions );
	
	if ( Constant.IsPublic () )
		PrintString += " ( public )";
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintTypeAlias ( const OilTypeAlias & Alias, uint32_t Indent, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[ALIAS ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Alias.GetName () );
	
	if ( Alias.IsTemplated () )
	{
		
		PrintString += " Template: ";
		PrintString += OilStringTemplateDefinition ( * Alias.GetTemplateDefinition (), PrintOptions );
		
	}
	
	PrintString += ": ";
	PrintString += OilStringTypeRef ( * Alias.GetAliasedType (), PrintOptions );
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintStatementBody ( const OilStatementBody & Body, uint32_t Indent, const OilPrintOptions & PrintOptions, const OilNamespaceDefinition * InitializedBindingContainer )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Body.GetIgnoredParamCount (); I ++ )
	{
		
		PrintString = "";
		
		for ( uint32_t I = 0; I < Indent; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += "* Ignored: ";
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Body.GetIgnoredParamName ( I ) );
		
		LOG_VERBOSE ( PrintString );
		
	}
	
	for ( uint32_t I = 0; I < Body.GetLocalBindingCount (); I ++ )
	{
		
		PrintString = "";
		
		for ( uint32_t I = 0; I < Indent; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		const OilBindingStatement * Binding = Body.GetLocalBinding ( I );
		
		PrintString += "* Local ";
		
		if ( Binding -> IsMutable () )
			PrintString += "mut ";
		
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Binding -> GetName () );
		PrintString += ": ";
		PrintString += OilStringTypeRef ( * Binding -> GetType (), PrintOptions );
		
		LOG_VERBOSE ( PrintString );
		
	}
	
	for ( uint32_t I = 0; I < Body.GetLocalConstCount (); I ++ )
	{
		
		PrintString = "";
		
		for ( uint32_t I = 0; I < Indent; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		const OilConstStatement * Constant = Body.GetLocalConst ( I );
		
		PrintString += "* Const ";
		
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Constant -> GetName () );
		PrintString += ": ";
		PrintString += OilStringTypeRef ( * Constant -> GetType (), PrintOptions );
		
		LOG_VERBOSE ( PrintString );
		
	}
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
				
	PrintString = "";
	
	for ( uint64_t I = 0; I < Body.GetStatementCount (); I ++ )
	{
		
		const IOilStatement * Statement = Body.GetStatement ( I );
		
		switch ( Statement -> GetStatementType () )
		{
			
			case IOilStatement :: kStatementType_Body:
				OilPrintStatementBody ( * dynamic_cast <const OilStatementBody *> ( Statement ), Indent + 1, PrintOptions );
				break;
			
			case IOilStatement :: kStatementType_Expression:
			{
				
				for ( uint32_t I = 0; I < Indent + 1; I ++ )
					PrintString += OIL_PRINT_INDENTSTRING;
				
				PrintString += OilStringExpression ( * dynamic_cast <const OilExpression *> ( Statement ), PrintOptions );
				
				LOG_VERBOSE ( PrintString );
				
				PrintString = "";
				
			}
			break;
			
			case IOilStatement :: kStatementType_Break:
				OilPrintBreak ( * dynamic_cast <const OilBreak *> ( Statement ), Indent + 1, PrintOptions );
				break;
			
			case IOilStatement :: kStatementType_IfElse:
				OilPrintIfElse ( * dynamic_cast <const OilIfElse *> ( Statement ), Indent + 1, PrintOptions );
				break;
				
			case IOilStatement :: kStatementType_WhileLoop:
				OilPrintWhileLoop ( * dynamic_cast <const OilWhileLoop *> ( Statement ), Indent + 1, PrintOptions );
				break;
				
			case IOilStatement :: kStatementType_DoWhileLoop:
				OilPrintDoWhileLoop ( * dynamic_cast <const OilDoWhileLoop *> ( Statement ), Indent + 1, PrintOptions );
				break;
				
			case IOilStatement :: kStatementType_Loop:
				OilPrintLoop ( * dynamic_cast <const OilLoop *> ( Statement ), Indent + 1, PrintOptions );
				break;
			
			case IOilStatement :: kStatementType_Return:
			{
				
				const OilReturn * Return = dynamic_cast <const OilReturn *> ( Statement );
				
				const OilExpression * ReturnedExpression = Return -> GetReturnedExpression ();
				
				for ( uint32_t I = 0; I < Indent + 1; I ++ )
					PrintString += OIL_PRINT_INDENTSTRING;
				
				if ( ReturnedExpression == NULL )
				{
					
					PrintString += "[RETURN]";
					LOG_VERBOSE ( PrintString );
					
					PrintString = "";
					
					break;
					
				}
				
				PrintString += "[RETURN ";
				PrintString += OilStringExpression ( * ReturnedExpression, PrintOptions );
				PrintString += "]";
				
				LOG_VERBOSE ( PrintString );
				
				PrintString = "";
				
			}
			break;
				
			case IOilStatement :: kStatementType_ImplicitLocalInitialization:
			{
				
				const OilImplicitLocalInitialization * Initialization = dynamic_cast <const OilImplicitLocalInitialization *> ( Statement );
				
				const OilBindingStatement * Local = Body.GetLocalBinding ( Initialization -> GetLocalIndex () );
				
				for ( uint32_t I = 0; I < Indent + 1; I ++ )
					PrintString += OIL_PRINT_INDENTSTRING;
				
				PrintString += "[LOCAL_INIT ";
				PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Local -> GetName () );
				PrintString += " = ";
				PrintString += OilStringExpression ( * Local -> GetInitializerValue (), PrintOptions );
				PrintString += "]";
				
				LOG_VERBOSE ( PrintString );
				
				PrintString = "";
				
			}
			break;
			
			case IOilStatement :: kStatementType_ImplicitBindingInitialization:
			{
				
				const OilImplicitBindingInitialization * Initialization = dynamic_cast <const OilImplicitBindingInitialization *> ( Statement );
				
				const OilBindingStatement * Binding = ( InitializedBindingContainer != NULL ) ? ( InitializedBindingContainer -> FindBindingStatement ( Initialization -> GetBindingID () ) ) : NULL;
				
				for ( uint32_t I = 0; I < Indent + 1; I ++ )
					PrintString += OIL_PRINT_INDENTSTRING;
				
				PrintString += "[BINDING_INIT ";
				
				if ( Binding != NULL )
				{
					
					PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Binding -> GetName () );
					PrintString += " = ";
					PrintString += OilStringExpression ( * Binding -> GetInitializerValue (), PrintOptions );
					PrintString += "]";
					
				}
				else
					PrintString += "(unresolvable)]";
				
				LOG_VERBOSE ( PrintString );
				
				PrintString = "";
				
			}
			break;
			
			default:
				break;
			
		}
		
	}
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

std :: string OilStringExpression ( const OilExpression & Expression, const OilPrintOptions & PrintOptions )
{
	
	std :: string OutString = "[EXPRESSION: ";
	
	if ( Expression.IsPrimary () )
		OutString += OilStringPrimary ( * Expression.GetTermAsPrimary (), PrintOptions );
	else
		OutString += OilStringOperator ( * Expression.GetTermAsOperator (), PrintOptions );
	
	OutString += "]";
	
	return OutString;
	
}

std :: string OilStringPrimary ( const IOilPrimary & Primary, const OilPrintOptions & PrintOptions )
{
	
	switch ( Primary.GetPrimaryType () )
	{
		
		case IOilPrimary :: kPrimaryType_Allusion:
		{
			
			const OilAllusion & Allusion = dynamic_cast <const OilAllusion &> ( Primary );
			
			switch ( Allusion.GetTarget () )
			{
				
				case OilAllusion :: kAllusionTarget_Indeterminate:
					return std :: string ( PrintOptions.ShowResolution ? "[ALLUSION (unresolved) " : "[ALLUSION " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "]";
					
				case OilAllusion :: kAllusionTarget_Indeterminate_Templated:
					return std :: string ( PrintOptions.ShowResolution ? "[ALLUSION (unresolved) " : "[ALLUSION " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + ":" + OilStringTemplateSpecification ( * Allusion.GetDirectTemplateSpecification (), PrintOptions ) + "]";
					
				case OilAllusion :: kAllusionTarget_Self_Unchecked:
					return PrintOptions.ShowResolution ? "[ALLUSION (unresolved) self]" : "[ALLUSION self]";
					
				case OilAllusion :: kAllusionTarget_Namespaced:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (unresolved) ?::" : "[ALLUSION ?::";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					PrintString += std :: string ( " " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "]";
					
					return PrintString;
					
				}
				
				case OilAllusion :: kAllusionTarget_Namespaced_Absolue:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (unresolved) " : "[ALLUSION ";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					PrintString += std :: string ( " " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "]";
					
					return PrintString;
					
				}
				
				case OilAllusion :: kAllusionTarget_Namespaced_Templated:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (unresolved) ?::" : "[ALLUSION ?::";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + ( ( I != Allusion.GetNamespaceNameCount () - 1 ) ? "::" : ( Allusion.GetIndirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetIndirectTemplateSpecification (), PrintOptions ) + "::" ) : "::" );
					
					PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + ( ( Allusion.GetDirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetDirectTemplateSpecification (), PrintOptions ) + "]" ) : "]" );
					
					return PrintString;
					
				}
				
				case OilAllusion :: kAllusionTarget_Namespaced_Absolue_Templated:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (unresolved) " : "[ALLUSION ";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + ( ( I != Allusion.GetNamespaceNameCount () - 1 ) ? "::" : ( Allusion.GetIndirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetIndirectTemplateSpecification (), PrintOptions ) + "::" ) : "::" );
					
					PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + ( ( Allusion.GetDirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetDirectTemplateSpecification (), PrintOptions ) + "]" ) : "]" );
					
					return PrintString;
					
				}
				
				case OilAllusion :: kAllusionTarget_Self:
					return PrintOptions.ShowResolution ? "[ALLUSION (resolved) self]" : "[ALLUSION self]";
					
				case OilAllusion :: kAllusionTarget_Parameter:
					return std :: string ( ( PrintOptions.ShowResolution ? "[ALLUSION (resolved) Parameter: \"" : "[ALLUSION Parameter: \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]" );
				
				case OilAllusion :: kAllusionTarget_Function:
					return std :: string ( ( PrintOptions.ShowResolution ? "[ALLUSION (resolved) Function: \"" : "[ALLUSION Function: \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]" );
				
				case OilAllusion :: kAllusionTarget_Function_Templated:
					return std :: string ( ( PrintOptions.ShowResolution ? "[ALLUSION (resolved) Function: \"" : "[ALLUSION Function: \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\" " + OilStringTemplateSpecification ( * Allusion.GetDirectTemplateSpecification (), PrintOptions ) + "]" );
					
				case OilAllusion :: kAllusionTarget_LocalBinding:
					return std :: string ( ( PrintOptions.ShowResolution ? "[ALLUSION (resolved) Local Binding: \"" : "[ALLUSION Local Binding: \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]" );
					
				case OilAllusion :: kAllusionTarget_Binding:
					return std :: string ( ( PrintOptions.ShowResolution ? "[ALLUSION (resolved) Binding: \"" : "[ALLUSION Binding: \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]" );
				
				case OilAllusion :: kAllusionTarget_Constant:
					return std :: string ( ( PrintOptions.ShowResolution ? "[ALLUSION (resolved) Constant: \"" : "[ALLUSION Constant: \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]" );
				
				case OilAllusion :: kAllusionTarget_Function_Namespaced:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (resolved) Function: \"" : "[ALLUSION Function: \"";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					return PrintString + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]";
					
				}
				
				case OilAllusion :: kAllusionTarget_Method_Namespaced:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (resolved) Method: \"" : "[ALLUSION Method: \"";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					return PrintString + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]";
					
				}
				
				case OilAllusion :: kAllusionTarget_Binding_Namespaced:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (resolved) Binding: \"" : "[ALLUSION Binding: \"";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					return PrintString + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]";
					
				}
				
				case OilAllusion :: kAllusionTarget_Constant_Namespaced:
				{
					
					std :: string PrintString = PrintOptions.ShowResolution ? "[ALLUSION (resolved) Constant: \"" : "[ALLUSION Constant: \"";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					return PrintString + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]";
					
				}
				
				default:
					break;
				
			}
			
			return "[ALLUSION UNKOWN_TYPE]";
			
		}
		
		case IOilPrimary :: kPrimaryType_BoolLiteral:
		{
			
			const OilBoolLiteral & Literal = dynamic_cast <const OilBoolLiteral &> ( Primary );
			
			return Literal.GetValue () ? "[BOOL: true]" : "[BOOL: false]";
			
		}
		
		case IOilPrimary :: kPrimaryType_FloatLiteral:
		{
			
			const OilFloatLiteral & Literal = dynamic_cast <const OilFloatLiteral &> ( Primary );
			
			switch ( Literal.GetType () )
			{
				
				case OilFloatLiteral :: kFloatType_32:
					return std :: string ( "[FLOAT: Significand: " ) + Literal.GetValue ().GetSignificand ().ToHexString () + ", Power10: " + std :: to_string ( Literal.GetValue ().GetPower10 () ) + ", Power2: " + std :: to_string ( Literal.GetValue ().GetPower2 () ) + " (f32)]";
				
				case OilFloatLiteral :: kFloatType_64:
					return std :: string ( "[FLOAT: Significand: " ) + Literal.GetValue ().GetSignificand ().ToHexString () + ", Power10: " + std :: to_string ( Literal.GetValue ().GetPower10 () ) + ", Power2: " + std :: to_string ( Literal.GetValue ().GetPower2 () ) + " (f64)]";
				
				default:
					break;
				
			}
			
			return std :: string ( "[FLOAT: Significand: " ) + Literal.GetValue ().GetSignificand ().ToHexString () + ", Power10: " + std :: to_string ( Literal.GetValue ().GetPower10 () ) + ", Power2: " + std :: to_string ( Literal.GetValue ().GetPower2 () ) + " (indet)]";
			
		}
		
		case IOilPrimary :: kPrimaryType_StringLiteral:
		{
			
			const OilStringLiteral & Literal = dynamic_cast <const OilStringLiteral &> ( Primary );
			
			std :: string PrintString = "[STRING \"";
			
			PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Literal.GetValue () ) + "\" ";
			
			switch ( Literal.GetType () )
			{
				
				case OilStringLiteral :: kEncodingType_UTF8:
					PrintString += "(UTF8)]";
					break;
					
				case OilStringLiteral :: kEncodingType_UTF16:
					PrintString += "(UTF16)]";
					break;
					
				case OilStringLiteral :: kEncodingType_UTF32:
					PrintString += "(UTF32)]";
					break;
					
				case OilStringLiteral :: kEncodingType_Indeterminate:
				default:
					PrintString += "(indet)]";
					break;
				
			}
			
			return PrintString;
			
		}
		
		case IOilPrimary :: kPrimaryType_CharLiteral:
		{
			
			const OilCharLiteral & Literal = dynamic_cast <const OilCharLiteral &> ( Primary );
			
			return std :: string ( "[CHAR \'" ) + CodeConversion :: ConvertUTF32ToUTF8 ( std :: u32string ( 1, Literal.GetValue () ) ) + "\']";
			
		}
		
		case IOilPrimary :: kPrimaryType_NullPointerLiteral:
			return "[NULL_POINTER]";
			
		case IOilPrimary :: kPrimaryType_ArrayLiteral:
		{
			
			const OilArrayLiteral & Literal = dynamic_cast <const OilArrayLiteral &> ( Primary );
			
			std :: string PrintString = "[ARRAY";
			
			if ( Literal.HasTypeSpecifier () )
			{
				
				PrintString += "<";
				PrintString += OilStringTypeRef ( * Literal.GetTypeSpecifier (), PrintOptions );
				PrintString += ">";
				
			}
			
			if ( Literal.HasSpecificCount () )
			{
				
				PrintString += " (count = ";
				PrintString += OilStringPrimary ( * Literal.GetCountExpression (), PrintOptions );
				PrintString += ")";
				
			}
			
			if ( Literal.HasMemberInitiailizers () )
			{
				
				uint32_t MemberInitializerCount = Literal.GetMemberInitializerCount ();
				
				PrintString += " Initializers: {";
				
				for ( uint32_t I = 0; I < MemberInitializerCount - 1; I ++ )
				{
					
					PrintString += OilStringPrimary ( * Literal.GetMemberInitializer ( I ), PrintOptions );
					PrintString += ", ";
					
				}
				
				PrintString += OilStringPrimary ( * Literal.GetMemberInitializer ( MemberInitializerCount - 1 ), PrintOptions );
				
				PrintString += "}";
				
			}
			
			PrintString += "]";
			
			return PrintString;
			
		}
		
		case IOilPrimary :: kPrimaryType_IntegerLiteral:
		{
			
			const OilIntegerLiteral & Literal = dynamic_cast <const OilIntegerLiteral &> ( Primary );
			
			std :: string PrintString = "[INTEGER: ";
			
			switch ( Literal.GetType () )
			{
				
				case OilIntegerLiteral :: kIntType_Explicit_I8:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetSValue () ) ) + " (i8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_I16:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetSValue () ) ) + " (i16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_I32:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetSValue () ) ) + " (i32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_I64:
					PrintString += std :: to_string ( Literal.GetSValue () ) + " (i64)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_IPtr:
					PrintString += std :: to_string ( Literal.GetSValue () ) + " (iptr)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_U8:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetUValue () ) ) + " (u8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_U16:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetUValue () ) ) + " (u16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_U32:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetUValue () ) ) + " (u32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_U64:
					PrintString += std :: to_string ( Literal.GetUValue () ) + " (u64)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_UPtr:
					PrintString += std :: to_string ( Literal.GetUValue () ) + " (uptr)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinI8:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetSValue () ) ) + " (implied min i8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinI16:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetSValue () ) ) + " (implied min i16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinI32:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetSValue () ) ) + " (implied min i32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinI64:
					PrintString += std :: to_string ( Literal.GetSValue () ) + " (implied min i64)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinU8:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetUValue () ) ) + " (implied min u8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinU16:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetUValue () ) ) + " (implied min u16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinU32:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetUValue () ) ) + " (implied min u32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_I8_IfNegative:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetSValue () ) ) + " (req if_negative i8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_I16_IfNegative:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetSValue () ) ) + " (req if_negative i16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_I32_IfNegative:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetSValue () ) ) + " (req if_negative i32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Explicit_I64_IfNegative:
					PrintString += std :: to_string ( Literal.GetSValue () ) + " (req if_negative i64)]";
					break;
				
				case OilIntegerLiteral :: kIntType_Implied_MinI8_IfNegative:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetSValue () ) ) + " (implied min if_negative i8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinI16_IfNegative:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetSValue () ) ) + " (implied min if_negative i16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinI32_IfNegative:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetSValue () ) ) + " (implied min if_negative i32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Implied_MinI64_IfNegative:
					PrintString += std :: to_string ( Literal.GetSValue () ) + " (implied min if_negative i64)]";
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI8:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetSValue () ) ) + " (indet min i8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI16:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetSValue () ) ) + " (indet min i16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI32:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetSValue () ) ) + " (indet min i32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI64:
					PrintString += std :: to_string ( Literal.GetSValue () ) + " (indet min i64)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI8_IfNegative:
					PrintString += std :: to_string ( static_cast <int8_t> ( Literal.GetSValue () ) ) + " (indet min if_negative i8)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI16_IfNegative:
					PrintString += std :: to_string ( static_cast <int16_t> ( Literal.GetSValue () ) ) + " (indet min if_negative i16)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI32_IfNegative:
					PrintString += std :: to_string ( static_cast <int32_t> ( Literal.GetSValue () ) ) + " (indet min if_negative i32)]";
					break;
					
				case OilIntegerLiteral :: kIntType_Indeterminate_MinI64_IfNegative:
					PrintString += std :: to_string ( Literal.GetSValue () ) + " (indet min if_negative i64)]";
					break;
					
				default:
					PrintString += std :: to_string ( Literal.GetUValue () ) + " (UNKNOWN)]";
					break;
				
			}
			
			return PrintString;
			
		}
		
		case IOilPrimary :: kPrimaryType_Expression:
			return OilStringExpression ( dynamic_cast <const OilExpression &> ( Primary ), PrintOptions );
		
		default:
		break;
		
	}
	
	return "UNKNOWN_PRIMARY";
	
}

std :: string OilStringOperator ( const IOilOperator & Operator, const OilPrintOptions & PrintOptions )
{
	
	std :: string PrintString = "( ";
	
	if ( Operator.GetOperatorType () == IOilOperator :: kOperatorType_Unary )
	{
		
		const OilUnaryOperator & UnOp = dynamic_cast <const OilUnaryOperator &> ( Operator );
		
		PrintString += UnOp.GetOpName ();
		PrintString += ": ";
		
		if ( UnOp.IsTermPrimary () )
			PrintString += OilStringPrimary ( * UnOp.GetTermAsPrimary (), PrintOptions );
		else
			PrintString += OilStringOperator ( * UnOp.GetTermAsOperator (), PrintOptions );
		
		if ( UnOp.GetOp () == OilUnaryOperator :: kOperator_FunctionCall )
			PrintString += " parameters: " + OilStringFunctionCallParameterList ( * UnOp.GetFunctionCallParameterList (), PrintOptions );
		if ( UnOp.GetOp () == OilUnaryOperator :: kOperator_MemberAccess )
			PrintString += " member: " + CodeConversion :: ConvertUTF32ToUTF8 ( UnOp.GetNameForMemberAccess () );
		
	}
	else if ( Operator.GetOperatorType () == IOilOperator :: kOperatorType_Binary )
	{
		
		const OilBinaryOperator & BinOp = dynamic_cast <const OilBinaryOperator &> ( Operator );
		
		PrintString += BinOp.GetOpName ();
		PrintString += ": ";
		
		if ( BinOp.IsLeftPrimary () )
			PrintString += OilStringPrimary ( * BinOp.GetLeftTermAsPrimary (), PrintOptions );
		else
			PrintString += OilStringOperator ( * BinOp.GetLeftTermAsOperator (), PrintOptions );
		
		PrintString += ", ";
		
		if ( BinOp.IsRightPrimary () )
			PrintString += OilStringPrimary ( * BinOp.GetRightTermAsPrimary (), PrintOptions );
		else
			PrintString += OilStringOperator ( * BinOp.GetRightTermAsOperator (), PrintOptions );
		
	}
	else
		PrintString += std :: string ( "unkown op type: " ) + std :: to_string ( (int) Operator.GetOperatorType () );
	
	PrintString += " )";
	
	return PrintString;
	
}
