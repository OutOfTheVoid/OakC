#include <OIL/OilDebugPrint.h>
#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilStructDefinition.h>
#include <OIL/OilStructBinding.h>
#include <OIL/OilTemplateDefinition.h>
#include <OIL/OilTemplateDefinitionParameter.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

#define OIL_PRINT_INDENTSTRING "    "

void OilPrintNamespace ( const OilNamespaceDefinition & Namespace, uint32_t Indent );
void OilPrintNamespaceMembers ( const OilNamespaceDefinition & Namespace, uint32_t Indent );
void OilPrintStruct ( const OilStructDefinition & Struct, uint32_t Indent );
std :: string OilStringTemplateDefinition ( const OilTemplateDefinition & Template );

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
		
		OilTemplateDefinitionParameter * Param = Template.GetTemplateParameter ( I );
		
		OutString += CodeConversion :: ConvertUTF32ToUTF8 ( Param -> GetName () );
		
		if ( I != ParamCount - 1 )
			OutString += ", ";
		
	}
	
	OutString += ">";
	
	return OutString;
	
}

