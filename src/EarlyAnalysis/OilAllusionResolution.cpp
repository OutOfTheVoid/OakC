#include <EarlyAnalysis/OilAllusionResolution.h>
 
OilAllusionResolution_NameMapStack :: NameContext_Struct :: NameContext_Struct ( NameContextType Context ):
	Type ( Context ),
	Names ()
{
}

OilAllusionResolution_NameMapStack :: NameContext_Struct :: ~NameContext_Struct ()
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ():
	Type ( kMappingType_None )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilNamespaceDefinition * Namespace ):
	Type ( kMappingType_Namespace ),
	Namespace ( Namespace )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilBindingStatement * BindingStatement ):
	Type ( kMappingType_BindingStatement ),
	BindingStatement ( BindingStatement )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilConstStatement * ConstantStatement ):
	Type ( kMappingType_ConstantStatement ),
	ConstantStatement ( ConstantStatement )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilTypeDefinition * TypeDefinition ):
	Type ( kMappingType_TypeDefinition ),
	TypeDefinition ( TypeDefinition )
{
}


OilAllusionResolution_NameMapStack :: OilAllusionResolution_NameMapStack ():
	Contexts ()
{
}

OilAllusionResolution_NameMapStack :: ~OilAllusionResolution_NameMapStack ()
{
	
	for ( uint32_t I = 0; I < Contexts.size (); I ++ )
		delete Contexts [ I ];
	
}

void OilAllusionResolution_NameMapStack :: PushContext ( NameContextType Context )
{
	
	Contexts.push_back ( new NameContext ( Context ) );
	
}

void OilAllusionResolution_NameMapStack :: PopContext ()
{
	
	NameContext * Context = Contexts [ Contexts.size () - 1 ];
	
	uint32_t NameCount = Context -> Names.size ();
	
	for ( uint32_t I = 0; I < NameCount; I ++ )
	{
		
		std :: map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Context -> Names [ I ] );
		
		if ( FindIter != NameMap.end () )
			FindIter -> second.pop_back ();
		
	}
	
}

void OilAllusionResolution_NameMapStack :: AddNamespaceMapping ( const std :: u32string Name, OilNamespaceDefinition * Namespace )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap.insert ( std :: make_pair ( Name, std :: vector <NameMapping> ( { NameMapping ( Namespace ) } ) ) );
	else
		FindIter -> second.push_back ( NameMapping ( Namespace ) );
	
}

void OilAllusionResolution_NameMapStack :: AddBindingStatementMapping ( const std :: u32string Name, OilBindingStatement * BindingStatement )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap.insert ( std :: make_pair ( Name, std :: vector <NameMapping> ( { NameMapping ( BindingStatement ) } ) ) );
	else
		FindIter -> second.push_back ( NameMapping ( BindingStatement ) );
	
}

void OilAllusionResolution_NameMapStack :: AddConstStatementMapping ( const std :: u32string Name, OilBindingStatement * ConstantStatement )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap.insert ( std :: make_pair ( Name, std :: vector <NameMapping> ( { NameMapping ( ConstantStatement ) } ) ) );
	else
		FindIter -> second.push_back ( NameMapping ( ConstantStatement ) );
	
}

void OilAllusionResolution_NameMapStack :: AddTypeMapping ( const std :: u32string Name, OilTypeDefinition * TypeMapping )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap.insert ( std :: make_pair ( Name, std :: vector <NameMapping> ( { NameMapping ( TypeMapping ) } ) ) );
	else
		FindIter -> second.push_back ( NameMapping ( TypeMapping ) );
	
}

OilAllusionResolution_NameMapStack :: NameMapping OilAllusionResolution_NameMapStack :: LookupName ( const std :: u32string Name )
{
	
	std :: map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		return NameMapping ();
	
	uint32_t ResultCount = FindIter -> second.size ();
	
	if ( ResultCount == 0 )
		return NameMapping ();
	
	return FindIter -> second [ ResultCount - 1 ];
	
}

class OilAllusionResolution_ScopedNameStackContextReleaser
{
public:
	
	inline OilAllusionResolution_ScopedNameStackContextReleaser ( OilAllusionResolution_NameMapStack & NameStack ):
		NameStack ( NameStack )
	{
	}
	
	inline ~OilAllusionResolution_ScopedNameStackContextReleaser ()
	{
		
		NameStack.PopContext ();
		
	}
	
private:
	
	OilAllusionResolution_NameMapStack & NameStack;
	
};

//============================================================================================================================================================================================//

AllusionResolutionResult OilAllusionResolution_Namespace ( OilAllusionResolution_NameMapStack & NameStack, OilNamespaceDefinition & Namespace );

AllusionResolutionResult OilAllusionResolution_Root ( OilNamespaceDefinition & RootNS )
{
	
	(void) RootNS;
	
	OilAllusionResolution_NameMapStack NameMapStack;
	
	return OilAllusionResolution_Namespace ( NameMapStack, RootNS );
	
}

AllusionResolutionResult OilAllusionResolution_Namespace ( OilAllusionResolution_NameMapStack & NameStack, OilNamespaceDefinition & Namespace )
{
	
	NameStack.PushContext ( OilAllusionResolution_NameMapStack :: kNameContext_Namespace );
	OilAllusionResolution_ScopedNameStackContextReleaser NS_Releaser ( NameStack );
	
	(void) Namespace;
	
	return kAllusionResolutionResult_Success_Complete;
	
}


