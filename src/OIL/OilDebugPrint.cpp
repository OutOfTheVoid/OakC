#include <OIL/OilDebugPrint.h>
#include <OIL/OilNamespaceDefinition.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

#define OIL_PRINT_INDENTSTRING "    "

void OilPrintNamespace ( const OilNamespaceDefinition & Namespace, uint32_t Indent );
void OilPrintNamespaceMembers ( const OilNamespaceDefinition & Namespace, uint32_t Indent );

void OilPrint ( const OilNamespaceDefinition & RootNS )
{
	
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

