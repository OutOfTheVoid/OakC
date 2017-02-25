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

void OilPrint ( const OilNamespaceDefinition & RootNS )
{
	
	LOG_VERBOSE ( "OIL TREE:" );
	
	OilPrintNamespace ( RootNS, 0 );
	
}

void OilPrintNamespaceMembers ( const OilNamespaceDefinition & Namespace, uint32_t Indent )
{
	
	uint64_t TempCount = Namespace.GetSubNamespaceDefinitionCount ();
	
	for ( uint64_t I = 0; I < TempCount; I ++ )
	{
		
		const OilNamespaceDefinition * Definition = Namespace.GetNamespaceDefinition ( I );
		
		OilPrintNamespace ( * Definition, Indent );
		
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
		
		PrintString += "[BINDING \"";
		PrintString += CodeConversion :: ConvertUTF32ToUTF8 ( Binding -> GetName () );
		PrintString += "\"]";
		
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
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "{";
	
	LOG_VERBOSE ( PrintString );
	
	// TODO: Print function body
	
	PrintString = "";
	
	for ( uint32_t I = 0; I < Indent; I ++ )
		PrintString += OIL_PRINT_INDENTSTRING;
	
	PrintString += "}";
	
	LOG_VERBOSE ( PrintString );
	
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
