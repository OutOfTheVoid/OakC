#include <OIL/OilDebugPrint.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilTypeRef.h>
#include <OIL/OilTemplateSpecification.h>
#include <OIL/OilStatementBody.h>
#include <OIL/IOilStatement.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTraitFunction.h>
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

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

#define OIL_PRINT_INDENTSTRING "    "

void OilPrintNamespace ( const OilNamespaceDefinition & Namespace, uint32_t Indent );
void OilPrintNamespaceMembers ( const OilNamespaceDefinition & Namespace, uint32_t Indent );
void OilPrintStruct ( const OilStructDefinition & Struct, uint32_t Indent );
std :: string OilStringTemplateDefinition ( const OilTemplateDefinition & Template );
std :: string OilStringTemplateSpecification ( const OilTemplateSpecification & Template );
void OilPrintFunction ( const OilFunctionDefinition & Function, uint32_t Indent );
std :: string OilStringTypeRef ( const OilTypeRef & Ref );
void OilPrintStatementBody ( const OilStatementBody & Body, uint32_t Indent, const OilNamespaceDefinition * InitializedBindingContainer = NULL );
void OilPrintBindingStatement ( const OilBindingStatement & Binding, uint32_t Indent );
void OilPrintTrait ( const OilTraitDefinition & Trait, uint32_t Indent );
std :: string OilStringTraitFunction ( const OilTraitFunction & Function );
std :: string OilStringExpression ( const OilExpression & Expression );
std :: string OilStringPrimary ( const IOilPrimary & Primary );
std :: string OilStringOperator ( const IOilOperator & Operator );

void OilPrint ( const OilNamespaceDefinition & RootNS )
{
	
	LOG_VERBOSE ( "OIL TREE:" );
	
	OilPrintNamespace ( RootNS, 0 );
	
}

void OilPrintNamespaceMembers ( const OilNamespaceDefinition & Namespace, uint32_t Indent )
{
	
	uint64_t TempCount = Namespace.GetBindingStatementCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilBindingStatement * Binding = Namespace.GetBindingStatement ( I );
		
		OilPrintBindingStatement ( * Binding, Indent );
		
	}
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "STATIC INITIALIZER BODY:";
	
	LOG_VERBOSE ( PrintString );
	
	OilPrintStatementBody ( Namespace.GetImplicitInitializationBody (), Indent, & Namespace );
	
	TempCount = Namespace.GetTraitDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilTraitDefinition * Definition = Namespace.GetTraitDefinition ( I );
		
		OilPrintTrait ( * Definition, Indent );
		
	}
	
	TempCount = Namespace.GetStructDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilStructDefinition * Definition = Namespace.GetStructDefinition ( I );
		
		OilPrintStruct ( * Definition, Indent );
		
	}
	
	TempCount = Namespace.GetFunctionDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilFunctionDefinition * Definition = Namespace.GetFunctionDefinition ( I );
		
		OilPrintFunction ( * Definition, Indent );
		
	}
	
	TempCount = Namespace.GetSubNamespaceDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilNamespaceDefinition * Definition = Namespace.GetNamespaceDefinition ( I );
		
		OilPrintNamespace ( * Definition, Indent );
		
	}
	
}

void OilPrintNamespace ( const OilNamespaceDefinition & Namespace, uint32_t Indent )
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
	
	OilPrintNamespaceMembers ( Namespace, Indent + 1 );
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintTrait ( const OilTraitDefinition & Trait, uint32_t Indent )
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
		PrintString += OilStringTemplateDefinition ( * Trait.GetTemplateDefinition () );
		
	}
	
	PrintString += "]\n";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
	
	PrintString = "";
	
	for ( uint32_t J = 0; J < Trait.GetFunctionCount (); J ++ )
	{
		
		for ( uint32_t I = 0; I < Indent + 1; I ++ )
			PrintString += OIL_PRINT_INDENTSTRING;
		
		PrintString += OilStringTraitFunction ( * Trait.GetTraitFunction ( J ) );
		LOG_VERBOSE ( PrintString );
		
		PrintString = "";
		
	}
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

std :: string OilStringTraitFunction ( const OilTraitFunction & Function )
{
	
	std :: string PrintString = "[FUNCTION ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Function.GetName () );
	
	if ( Function.IsTemplated () )
		PrintString += std :: string ( " Template: " ) + OilStringTemplateDefinition ( * Function.GetTemplateDefinition () );
	
	const OilFunctionParameterList * ParamList = Function.GetParameterList ();
	
	if ( ParamList -> GetParameterCount () != 0 )
	{
		
		PrintString += " Parameters: (";
		
		for ( uint32_t I = 0; I < ParamList -> GetParameterCount (); I ++ )
		{
			
			const OilFunctionParameter * Parameter = ParamList -> GetFunctionParameter ( I );
			
			PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Parameter -> GetName () );
			
			PrintString += ": ";
			
			PrintString += OilStringTypeRef ( * Parameter -> GetType () );
			
			if ( I != ParamList -> GetParameterCount () - 1 )
				PrintString += ", ";
			
		}
		
		PrintString += ")";
		
	}
	
	if ( Function.HasReturnType () )
	{
		
		PrintString += " Return: ";
		PrintString += OilStringTypeRef ( * Function.GetReturnType () );
		
	}
	
	PrintString += "]";
	
	return PrintString;
	
}

void OilPrintStruct ( const OilStructDefinition & Struct, uint32_t Indent )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[STRUCT \"";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Struct.GetID () );
	
	if ( Struct.IsTemplated () )
	{
		
		PrintString += "\" Template: ";
		PrintString += OilStringTemplateDefinition ( * Struct.GetTemplateDefinition () );
		PrintString += "]\n";
		
	}
	else
		PrintString += "\"]\n";
	
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
		PrintString += OilStringTypeRef ( * Binding -> GetTypeRef () );
		PrintString += "]";
		
		LOG_VERBOSE ( PrintString );
		
	}
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
}

std :: string OilStringTemplateDefinition ( const OilTemplateDefinition & Template )
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
				
				OutString += OilStringTypeRef ( * Param -> GetRestriction ( I ) );
				
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

void OilPrintFunction ( const OilFunctionDefinition & Function, uint32_t Indent )
{
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[FUNCTION \"";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Function.GetName () );
	PrintString += "\"";
	
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
		PrintString += OilStringTemplateDefinition ( * Function.GetTemplateDefinition () );
		
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
			
			PrintString += OilStringTypeRef ( * Parameter -> GetType () );
			
			if ( I != ParamList -> GetParameterCount () - 1 )
				PrintString += ", ";
			
		}
		
		PrintString += ")";
		
	}
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
	OilPrintStatementBody ( * Function.GetStatementBody (), Indent );
	
}

std :: string OilStringTypeRef ( const OilTypeRef & Ref )
{
	
	if ( ! Ref.IsDirectType () )
	{
		
		if ( Ref.IsReference () )
			return std :: string ( "&" ) + OilStringTypeRef ( * Ref.GetSubType () );
		else
			return std :: string ( "*" ) + OilStringTypeRef ( * Ref.GetSubType () );
			
	}
	
	std :: string OutString;
	
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
		OutString += OilStringTemplateSpecification ( * Ref.GetTemplateSpecification () );
	
	return OutString;
	
}

std :: string OilStringTemplateSpecification ( const OilTemplateSpecification & Template )
{
	
	std :: string OutString;
	
	OutString += "<";
	
	uint32_t ParamCount = Template.GetTypeRefCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OutString += OilStringTypeRef ( * Template.GetTypeRef ( I ) );
		
		if ( I != ParamCount - 1 )
			OutString += ", ";
		
	}
	
	OutString += ">";
	
	return OutString;
	
}

void OilPrintBindingStatement ( const OilBindingStatement & Binding, uint32_t Indent )
{
	
	std :: string PrintString;
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "[BINDING ";
	PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Binding.GetName () );
	
	PrintString += ": ";
	PrintString += OilStringTypeRef ( * Binding.GetType () );
	
	if ( Binding.IsMutable () )
		PrintString += " ( mut )";
	
	if ( Binding.IsPublic () )
		PrintString += Binding.IsMutable () ? "( public )" : " ( public )";
	
	PrintString += "]";
	
	LOG_VERBOSE ( PrintString );
	
}

void OilPrintStatementBody ( const OilStatementBody & Body, uint32_t Indent, const OilNamespaceDefinition * InitializedBindingContainer )
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
		PrintString += OilStringTypeRef ( * Binding -> GetType () );
		
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
				OilPrintStatementBody ( * dynamic_cast <const OilStatementBody *> ( Statement ), Indent + 1 );
				break;
			
			case IOilStatement :: kStatementType_Expression:
			{
				
				for ( uint32_t I = 0; I < Indent + 1; I ++ )
					PrintString += OIL_PRINT_INDENTSTRING;
				
				PrintString += OilStringExpression ( * dynamic_cast <const OilExpression *> ( Statement ) );
				
				LOG_VERBOSE ( PrintString );
				
				PrintString = "";
				
			}
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
				PrintString += OilStringExpression ( * ReturnedExpression );
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
				PrintString += OilStringExpression ( * Local -> GetInitializerValue () );
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
					PrintString += OilStringExpression ( * Binding -> GetInitializerValue () );
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

std :: string OilStringExpression ( const OilExpression & Expression )
{
	
	std :: string OutString = "[EXPRESSION: ";
	
	if ( Expression.IsPrimary () )
		OutString += OilStringPrimary ( * Expression.GetTermAsPrimary () );
	else
		OutString += OilStringOperator ( * Expression.GetTermAsOperator () );
	
	OutString += "]";
	
	return OutString;
	
}

std :: string OilStringPrimary ( const IOilPrimary & Primary )
{
	
	switch ( Primary.GetPrimaryType () )
	{
		
		case IOilPrimary :: kPrimaryType_Allusion:
		{
			
			const OilAllusion & Allusion = dynamic_cast <const OilAllusion &> ( Primary );
			
			switch ( Allusion.GetTarget () )
			{
				
				case OilAllusion :: kAllusionTarget_Indeterminate:
					return std :: string ( "[ALLUSION " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "]";
					
				case OilAllusion :: kAllusionTarget_Indeterminate_Templated:
					return std :: string ( "[ALLUSION " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + ":" + OilStringTemplateSpecification ( * Allusion.GetDirectTemplateSpecification () ) + "]";
					
				case OilAllusion :: kAllusionTarget_Parameter:
					return std :: string ( "[ALLUSION Parameter: \"" ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "\"]";
					
				case OilAllusion :: kAllusionTarget_Self:
					return "[ALLUSION self]";
					
				case OilAllusion :: kAllusionTarget_Namespaced:
				{
					
					std :: string PrintString = "[ALLUSION ?::";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					PrintString += std :: string ( " " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "]";
					
					return PrintString;
					
				}
				
				case OilAllusion :: kAllusionTarget_Namespaced_Absolue:
				{
					
					std :: string PrintString = "[ALLUSION ";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + "::";
					
					PrintString += std :: string ( " " ) + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + "]";
					
					return PrintString;
					
				}
				
				case OilAllusion :: kAllusionTarget_Namespaced_Templated:
				{
					
					std :: string PrintString = "[ALLUSION ?::";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + ( ( I != Allusion.GetNamespaceNameCount () - 1 ) ? "::" : ( Allusion.GetIndirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetIndirectTemplateSpecification () ) + "::" ) : "::" );
					
					PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + ( ( Allusion.GetDirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetDirectTemplateSpecification () ) + "]" ) : "]" );
					
					return PrintString;
					
				}
				
				case OilAllusion :: kAllusionTarget_Namespaced_Absolue_Templated:
				{
					
					std :: string PrintString = "[ALLUSION ";
					
					for ( uint32_t I = 0; I < Allusion.GetNamespaceNameCount (); I ++ )
						PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( I ) ) + ( ( I != Allusion.GetNamespaceNameCount () - 1 ) ? "::" : ( Allusion.GetIndirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetIndirectTemplateSpecification () ) + "::" ) : "::" );
					
					PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetName () ) + ( ( Allusion.GetDirectTemplateSpecification () != NULL ) ? ( std :: string ( ":" ) + OilStringTemplateSpecification ( * Allusion.GetDirectTemplateSpecification () ) + "]" ) : "]" );
					
					return PrintString;
					
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
				PrintString += OilStringTypeRef ( * Literal.GetTypeSpecifier () );
				PrintString += ">";
				
			}
			
			if ( Literal.HasSpecificCount () )
			{
				
				PrintString += " (count = ";
				PrintString += OilStringPrimary ( * Literal.GetCountExpression () );
				PrintString += ")";
				
			}
			
			if ( Literal.HasMemberInitiailizers () )
			{
				
				uint32_t MemberInitializerCount = Literal.GetMemberInitializerCount ();
				
				PrintString += " Initializers: {";
				
				for ( uint32_t I = 0; I < MemberInitializerCount - 1; I ++ )
				{
					
					PrintString += OilStringPrimary ( * Literal.GetMemberInitializer ( I ) );
					PrintString += ", ";
					
				}
				
				PrintString += OilStringPrimary ( * Literal.GetMemberInitializer ( MemberInitializerCount - 1 ) );
				
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
			return OilStringExpression ( dynamic_cast <const OilExpression &> ( Primary ) );
			
		
		
		default:
		break;
		
	}
	
	return "UNKNOWN_PRIMARY";
	
}

std :: string OilStringOperator ( const IOilOperator & Operator )
{
	
	std :: string PrintString = "( ";
	
	if ( Operator.GetOperatorType () == IOilOperator :: kOperatorType_Unary )
	{
		
		const OilUnaryOperator & UnOp = dynamic_cast <const OilUnaryOperator &> ( Operator );
		
		PrintString += UnOp.GetOpName ();
		PrintString += ": ";
		
		if ( UnOp.IsTermPrimary () )
			PrintString += OilStringPrimary ( * UnOp.GetTermAsPrimary () );
		else
			PrintString += OilStringOperator ( * UnOp.GetTermAsOperator () );
		
		
	}
	else if ( Operator.GetOperatorType () == IOilOperator :: kOperatorType_Binary )
	{
		
		const OilBinaryOperator & BinOp = dynamic_cast <const OilBinaryOperator &> ( Operator );
		
		PrintString += BinOp.GetOpName ();
		PrintString += ": ";
		
		if ( BinOp.IsLeftPrimary () )
			PrintString += OilStringPrimary ( * BinOp.GetLeftTermAsPrimary () );
		else
			PrintString += OilStringOperator ( * BinOp.GetLeftTermAsOperator () );
		
		PrintString += ", ";
		
		if ( BinOp.IsRightPrimary () )
			PrintString += OilStringPrimary ( * BinOp.GetRightTermAsPrimary () );
		else
			PrintString += OilStringOperator ( * BinOp.GetRightTermAsOperator () );
		
	}
	else
		PrintString += std :: string ( "unkown op type: " ) + std :: to_string ( (int) Operator.GetOperatorType () );
	
	PrintString += " )";
	
	return PrintString;
	
}
