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
void OilPrintStatementBody ( const OilStatementBody & Body, uint32_t Indent );
void OilPrintBindingStatement ( const OilBindingStatement & Binding, uint32_t Indent );
void OilPrintTrait ( const OilTraitDefinition & Trait, uint32_t Indent );

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
	
	//OilPrintNamespaceMembers ( Namespace, Indent + 1 );
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
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
	
	OutString += ":<";
	
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

void OilPrintStatementBody ( const OilStatementBody & Body, uint32_t Indent )
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
	
	for ( uint64_t I = 0; I < Body.GetStatementCount (); I ++ )
	{
		
		const IOilStatement * Statement = Body.GetStatement ( I );
		
		switch ( Statement -> GetStatementType () )
		{
			
			case IOilStatement :: kStatementType_Body:
				OilPrintStatementBody ( * dynamic_cast <const OilStatementBody *> ( Statement ), Indent + 1 );
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
