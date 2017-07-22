#include <EarlyAnalysis/OilAllusionResolution.h>

#include <OIL/OilNamespaceDefinition.h>
#include <OIL/OilBindingStatement.h>
#include <OIL/OilConstStatement.h>
#include <OIL/OilTypeDefinition.h>
#include <OIL/OilFunctionDefinition.h>
#include <OIL/OilTraitDefinition.h>
#include <OIL/OilTypeAlias.h>
#include <OIL/OilStatementBody.h>
#include <OIL/IOilStatement.h>
 
OilAllusionResolution_NameMapStack :: NameContext_Struct :: NameContext_Struct ( NameContextType Context ):
	Type ( Context ),
	Names ()
{
}

OilAllusionResolution_NameMapStack :: NameContext_Struct :: NameContext_Struct ( const NameContext_Struct & CopyFrom ):
	Type ( CopyFrom.Type ),
	Names ( CopyFrom.Names )
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

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilFunctionDefinition * FunctionDefintiion ):
	Type ( kMappingType_FunctionDefinition ),
	FunctionDefintiion ( FunctionDefintiion )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilTraitDefinition * TraitDefinition ):
	Type ( kMappingType_TraitDefinition ),
	TraitDefinition ( TraitDefinition )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilTypeAlias * TypeAlias ):
	Type ( kMappingType_TypeAlias ),
	TypeAlias ( TypeAlias )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: ~NameMapping_Struct ()
{
}


OilAllusionResolution_NameMapStack :: OilAllusionResolution_NameMapStack ():
	Contexts (),
	NameMap ()
{
}

OilAllusionResolution_NameMapStack :: ~OilAllusionResolution_NameMapStack ()
{
	
	for ( uint32_t I = 0; I < Contexts.size (); I ++ )
		delete Contexts [ I ];
	
	Contexts.clear ();
	NameMap.clear ();
	
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
		
		std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Context -> Names [ I ] );
		
		if ( FindIter != NameMap.end () )
			FindIter -> second.pop_back ();
		
	}
	
	Contexts.pop_back ();
	
	delete Context;
	
}

void OilAllusionResolution_NameMapStack :: AddNamespaceMapping ( const std :: u32string & Name, OilNamespaceDefinition * Namespace )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( Namespace ) } );
	else
		FindIter -> second.push_back ( NameMapping ( Namespace ) );
	
}

void OilAllusionResolution_NameMapStack :: AddBindingStatementMapping ( const std :: u32string & Name, OilBindingStatement * BindingStatement )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( BindingStatement ) } );
	else
		FindIter -> second.push_back ( NameMapping ( BindingStatement ) );
	
}

void OilAllusionResolution_NameMapStack :: AddConstStatementMapping ( const std :: u32string & Name, OilConstStatement * ConstantStatement )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( ConstantStatement ) } );
	else
		FindIter -> second.push_back ( NameMapping ( ConstantStatement ) );
	
}

void OilAllusionResolution_NameMapStack :: AddTypeMapping ( const std :: u32string & Name, OilTypeDefinition * TypeMapping )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( TypeMapping ) } );
	else
		FindIter -> second.push_back ( NameMapping ( TypeMapping ) );
	
}

void OilAllusionResolution_NameMapStack :: AddFunctionMapping ( const std :: u32string & Name, OilFunctionDefinition * FunctionDefintiion )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( FunctionDefintiion ) } );
	else
		FindIter -> second.push_back ( NameMapping ( FunctionDefintiion ) );
	
}

void OilAllusionResolution_NameMapStack :: AddTraitMapping ( const std :: u32string & Name, OilTraitDefinition * TraitDefinition )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( TraitDefinition ) } );
	else
		FindIter -> second.push_back ( NameMapping ( TraitDefinition ) );
	
}

void OilAllusionResolution_NameMapStack :: AddTypeAliasMapping ( const std :: u32string & Name, OilTypeAlias * TypeAlias )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( TypeAlias ) } );
	else
		FindIter -> second.push_back ( NameMapping ( TypeAlias ) );
	
}

OilAllusionResolution_NameMapStack :: NameMapping OilAllusionResolution_NameMapStack :: LookupName ( const std :: u32string Name )
{
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		return NameMapping ();
	
	uint32_t ResultCount = FindIter -> second.size ();
	
	if ( ResultCount == 0 )
		return NameMapping ();
	
	return FindIter -> second [ ResultCount - 1 ];
	
}

void OilAllusionResolution_NameMapStack :: ReadInScopeNames ( std :: vector <std :: u32string> & Out )
{
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator ListIter = NameMap.begin ();
	
	while ( ListIter != NameMap.end () )
	{
		
		if ( ListIter -> second.size () != 0 )
			Out.push_back ( ListIter -> first );
		
		ListIter ++;
		
	}
	
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

AllusionResolutionResult OilAllusionResolution_StatementBody ( OilAllusionResolution_NameMapStack & NameStack, OilStatementBody & Body );
AllusionResolutionResult OilAllusionResolution_Namespace ( OilAllusionResolution_NameMapStack & NameStack, OilNamespaceDefinition & Namespace );

AllusionResolutionResult OilAllusionResolution_Root ( OilNamespaceDefinition & RootNS )
{
	
	(void) RootNS;
	
	OilAllusionResolution_NameMapStack NameMapStack;
	
	return OilAllusionResolution_Namespace ( NameMapStack, RootNS );
	
}

AllusionResolutionResult OilAllusionResolution_Namespace ( OilAllusionResolution_NameMapStack & NameStack, OilNamespaceDefinition & Namespace )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	NameStack.PushContext ( OilAllusionResolution_NameMapStack :: kNameContext_Namespace );
	OilAllusionResolution_ScopedNameStackContextReleaser NS_Releaser ( NameStack );
	
	//=========================================[name population]========================================//
	
	uint32_t SubNSCount = Namespace.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		OilNamespaceDefinition * Definition = Namespace.GetNamespaceDefinition ( I );
		NameStack.AddNamespaceMapping ( Definition -> GetID (), Definition );
		
	}
	
	uint32_t TypeDefCount = Namespace.GetTypeDefinitionCount ();
	
	for ( uint32_t I = 0; I < TypeDefCount; I ++ )
	{
		
		OilTypeDefinition * Definition = Namespace.GetTypeDefinition ( I );
		NameStack.AddTypeMapping ( Definition -> GetName (), Definition );
		
	}
	
	uint32_t FunctionDefCount = Namespace.GetFunctionDefinitionCount ();
	
	for ( uint32_t I = 0; I < FunctionDefCount; I ++ )
	{
		
		OilFunctionDefinition * Definition = Namespace.GetFunctionDefinition ( I );
		NameStack.AddFunctionMapping ( Definition -> GetName (), Definition );
		
	}
	
	uint32_t BindingCount = Namespace.GetBindingStatementCount ();
	
	for ( uint32_t I = 0; I < BindingCount; I ++ )
	{
		
		OilBindingStatement * Binding = Namespace.GetBindingStatement ( I );
		NameStack.AddBindingStatementMapping ( Binding -> GetName (), Binding );
		
	}
	
	uint32_t ConstantCount = Namespace.GetConstStatementCount ();
	
	for ( uint32_t I = 0; I < ConstantCount; I ++ )
	{
		
		OilConstStatement * Constant = Namespace.GetConstStatement ( I );
		NameStack.AddConstStatementMapping ( Constant -> GetName (), Constant );
		
	}
	
	uint32_t TraitCount = Namespace.GetTraitDefinitionCount ();
	
	for ( uint32_t I = 0; I < TraitCount; I ++ )
	{
		
		OilTraitDefinition * Definition = Namespace.GetTraitDefinition ( I );
		NameStack.AddTraitMapping ( Definition -> GetName (), Definition );
		
	}
	
	uint32_t TypeAliasCount = Namespace.GetTypeAliasCount ();
	
	for ( uint32_t I = 0; I < TypeAliasCount; I ++ )
	{
		
		OilTypeAlias * Alias = Namespace.GetTypeAlias ( I );
		NameStack.AddTypeAliasMapping ( Alias -> GetName (), Alias );
		
	}
	
	//=======================================[Allusion resolution]======================================//
	
	OilStatementBody & ImplicitInitBody = Namespace.GetImplicitInitializationBody ();
	
	AllusionResolutionResult ISBResult = OilAllusionResolution_StatementBody ( NameStack, ImplicitInitBody );
	
	if ( ISBResult == kAllusionResolutionResult_Success_Complete )
		Progress = true;
	else if ( ISBResult == kAllusionResolutionResult_Success_Progress )
	{
		
		Progress = true;
		Unresolved = true;
		
	}
	else if ( ISBResult == kAllusionResolutionResult_Success_NoProgress )
		Unresolved = true;
	else
		return ISBResult;
	
	
	//=======================================[Child propogation]
	
	SubNSCount = Namespace.GetSubNamespaceDefinitionCount ();
	
	for ( uint32_t I = 0; I < SubNSCount; I ++ )
	{
		
		OilNamespaceDefinition * Definition = Namespace.GetNamespaceDefinition ( I );
		
		AllusionResolutionResult NSResult = OilAllusionResolution_Namespace ( NameStack, * Definition );
		
		if ( NSResult == kAllusionResolutionResult_Success_Complete )
			Progress = true;
		else if ( NSResult == kAllusionResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( NSResult == kAllusionResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return NSResult;
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		
		return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilAllusionResolution_StatementBody ( OilAllusionResolution_NameMapStack & NameStack, OilStatementBody & Body )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	NameStack.PushContext ( OilAllusionResolution_NameMapStack :: kNameContext_StatementBlock );
	OilAllusionResolution_ScopedNameStackContextReleaser NS_Releaser ( NameStack );
	
	uint32_t StatementCount = Body.GetStatementCount ();
	
	for ( uint32_t I = 0; I < StatementCount; I ++ )
	{
		
		IOilStatement * Statement = Body.GetStatement ( I );
		
		switch ( Statement -> GetStatementType () )
		{
			
			case IOilStatement :: kStatementType_Body:
			{
				
				OilStatementBody * SubBody = dynamic_cast <OilStatementBody *> ( Statement );
				
				AllusionResolutionResult SBResult = OilAllusionResolution_StatementBody ( NameStack, * SubBody );
				
				if ( SBResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( SBResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( SBResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return SBResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Binding:
			{
				
				OilBindingStatement * Binding = dynamic_cast <OilBindingStatement *> ( Statement );
				
				if ( Binding -> HasInitializer () )
				{
					
					// TODO: resolve allusions in initializer
					
				}
				
				NameStack.AddBindingStatementMapping ( Binding -> GetName (), Binding );
				
			}
			break;
			
			case IOilStatement :: kStatementType_Const:
			{
				
				OilConstStatement * Constant = dynamic_cast <OilConstStatement *> ( Statement );
				
				// TODO: resolve allusions in initializer
				
				NameStack.AddConstStatementMapping ( Constant -> GetName (), Constant );
				
			}
			break;
			
			case IOilStatement :: kStatementType_Expression:
			case IOilStatement :: kStatementType_Return:
			case IOilStatement :: kStatementType_IfElse:
			case IOilStatement :: kStatementType_Match:
			case IOilStatement :: kStatementType_WhileLoop:
			case IOilStatement :: kStatementType_DoWhileLoop:
			case IOilStatement :: kStatementType_Loop:
			case IOilStatement :: kStatementType_Break:
			case IOilStatement :: kStatementType_ImplicitLocalInitialization:
			case IOilStatement :: kStatementType_ImplicitBindingInitialization:
			break;
			
		}
		
	}
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		
		return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}


