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
#include <OIL/OilExpression.h>
#include <OIL/OilImplicitLocalInitialization.h>
#include <OIL/OilImplicitBindingInitialization.h>
#include <OIL/OilReturn.h>
#include <OIL/OilIfElse.h>
#include <OIL/OilMatch.h>
#include <OIL/OilLoop.h>
#include <OIL/OilDoWhileLoop.h>
#include <OIL/OilWhileLoop.h>
#include <OIL/OilBreak.h>
#include <OIL/IOilLoop.h>
#include <OIL/OilMatchBranch.h>
#include <OIL/OilFunctionParameterList.h>
#include <OIL/OilFunctionParameter.h>
#include <OIL/OilStructDestructure.h>
#include <OIL/OilMemberDestructure.h>
#include <OIL/OilAllusion.h>

#include <Logging/Logging.h>
#include <Logging/ErrorUtils.h>

#include <Encoding/CodeConversion.h>
 
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

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( IOilLoop * LabledLoop ):
	Type ( kMappingType_LabledLoop ),
	LabledLoop ( LabledLoop )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilFunctionParameter * FunctionParameter ):
	Type ( kMappingType_FunctionParameter ),
	FunctionParameter ( FunctionParameter )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilMatchBranch * MatchBranchValue ):
	Type ( kMappingType_MatchBranchValue ),
	MatchBranchValue ( MatchBranchValue )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: NameMapping_Struct ( OilMemberDestructure * MemberDestructure ):
	Type ( kMappingType_MemberDestructure ),
	MemberDestructure ( MemberDestructure )
{
}

OilAllusionResolution_NameMapStack :: NameMapping_Struct :: ~NameMapping_Struct ()
{
}


OilAllusionResolution_NameMapStack :: OilAllusionResolution_NameMapStack ( OilNamespaceDefinition & GlobalNamespace ):
	Contexts (),
	NameMap (),
	GlobalNamespace ( GlobalNamespace )
{
}

OilAllusionResolution_NameMapStack :: ~OilAllusionResolution_NameMapStack ()
{
	
	for ( uint32_t I = 0; I < Contexts.size (); I ++ )
		delete Contexts [ I ];
	
	Contexts.clear ();
	NameMap.clear ();
	
}

OilNamespaceDefinition & OilAllusionResolution_NameMapStack :: GetGlobalNamespace ()
{
	
	return GlobalNamespace;
	
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

void OilAllusionResolution_NameMapStack :: AddLabledLoopMapping ( const std :: u32string & Label, IOilLoop * LabledLoop )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Label );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Label );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Label ] = std :: vector <NameMapping> ( { NameMapping ( LabledLoop ) } );
	else
		FindIter -> second.push_back ( NameMapping ( LabledLoop ) );
	
}

void OilAllusionResolution_NameMapStack :: AddFunctionParameterMapping ( const std :: u32string & Name, OilFunctionParameter * FunctionParameter )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( FunctionParameter ) } );
	else
		FindIter -> second.push_back ( NameMapping ( FunctionParameter ) );
	
}

void OilAllusionResolution_NameMapStack :: AddMatchBranchValueMapping ( const std :: u32string & Name, OilMatchBranch * MatchBranchValue )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( MatchBranchValue ) } );
	else
		FindIter -> second.push_back ( NameMapping ( MatchBranchValue ) );
	
}


void OilAllusionResolution_NameMapStack :: AddMemberDestructureMapping ( const std :: u32string & Name, OilMemberDestructure * MemberDestructure )
{
	
	NameContext * CurrentContext = Contexts [ Contexts.size () - 1 ];
	
	CurrentContext -> Names.push_back ( Name );
	
	std :: unordered_map <std :: u32string, std :: vector <NameMapping>> :: iterator FindIter = NameMap.find ( Name );
	
	if ( FindIter == NameMap.end () )
		NameMap [ Name ] = std :: vector <NameMapping> ( { NameMapping ( MemberDestructure ) } );
	else
		FindIter -> second.push_back ( NameMapping ( MemberDestructure ) );
	
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

AllusionResolutionResult OilAllusionResolution_Allusion ( OilAllusionResolution_NameMapStack & NameStack, OilAllusion & Allusion );
void AddDestructureNames ( OilAllusionResolution_NameMapStack & NameStack, OilStructDestructure & Destructure );
AllusionResolutionResult OilAllusionResolution_Function ( OilAllusionResolution_NameMapStack & NameStack, OilFunctionDefinition & Branch );
AllusionResolutionResult OilAllusionResolution_MatchBranch ( OilAllusionResolution_NameMapStack & NameStack, OilMatchBranch & Branch, IOilLoop * TopLoop );
AllusionResolutionResult OilAllusionResolution_Expression ( OilAllusionResolution_NameMapStack & NameStack, OilExpression & Expression );
AllusionResolutionResult OilAllusionResolution_StatementBody ( OilAllusionResolution_NameMapStack & NameStack, OilStatementBody & Body, IOilLoop * TopLoop );
AllusionResolutionResult OilAllusionResolution_Namespace ( OilAllusionResolution_NameMapStack & NameStack, OilNamespaceDefinition & Namespace );

AllusionResolutionResult OilAllusionResolution_Root ( OilNamespaceDefinition & RootNS )
{
	
	(void) RootNS;
	
	OilAllusionResolution_NameMapStack NameMapStack ( RootNS );
	
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
	
	AllusionResolutionResult ISBResult = OilAllusionResolution_StatementBody ( NameStack, ImplicitInitBody, NULL );
	
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
	
	TypeDefCount = Namespace.GetTypeDefinitionCount ();
	
	for ( uint32_t I = 0; I < TypeDefCount; I ++ )
	{
		
		OilTypeDefinition * Definition = Namespace.GetTypeDefinition ( I );
		
		// TODO: Resolve type definitions
		(void) Definition;
		
	}
	
	FunctionDefCount = Namespace.GetFunctionDefinitionCount ();
	
	for ( uint32_t I = 0; I < FunctionDefCount; I ++ )
	{
		
		OilFunctionDefinition * Definition = Namespace.GetFunctionDefinition ( I );
		
		AllusionResolutionResult FResult = OilAllusionResolution_Function ( NameStack, * Definition );
		
		if ( FResult == kAllusionResolutionResult_Success_Complete )
			Progress = true;
		else if ( FResult == kAllusionResolutionResult_Success_Progress )
		{
			
			Progress = true;
			Unresolved = true;
			
		}
		else if ( FResult == kAllusionResolutionResult_Success_NoProgress )
			Unresolved = true;
		else
			return FResult;
		
	}
	
	//========================================[Child propogation]=======================================//
	
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

AllusionResolutionResult OilAllusionResolution_StatementBody ( OilAllusionResolution_NameMapStack & NameStack, OilStatementBody & Body, IOilLoop * TopLoop )
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
				
				AllusionResolutionResult SBResult = OilAllusionResolution_StatementBody ( NameStack, * SubBody, TopLoop );
				
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
				
				// NOTE: Initializer allusion resolution is handled by resolving corresponding OilImplicitLocalInitialization objects.
				
				OilBindingStatement * Binding = dynamic_cast <OilBindingStatement *> ( Statement );
				NameStack.AddBindingStatementMapping ( Binding -> GetName (), Binding );
				
			}
			break;
			
			case IOilStatement :: kStatementType_ImplicitLocalInitialization:
			{
				
				OilImplicitLocalInitialization * Initializer = dynamic_cast <OilImplicitLocalInitialization *> ( Statement );
				OilBindingStatement * Binding = Body.GetLocalBinding ( Initializer -> GetLocalIndex () );
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Binding -> GetInitializerValue () );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_ImplicitBindingInitialization:
			{
				
				OilImplicitBindingInitialization * Initializer = dynamic_cast <OilImplicitBindingInitialization *> ( Statement );
				OilAllusionResolution_NameMapStack :: NameMapping BindingMapping = NameStack.LookupName ( Initializer -> GetBindingID () );
				
				if ( BindingMapping.Type != OilAllusionResolution_NameMapStack :: kMappingType_BindingStatement )
				{
					
					LOG_FATALERROR ( "internal error: namespace binding initializer refers to binding not in namespace scope" );
					
					return kAllusionResolutionResult_Error;
					
				}
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * BindingMapping.BindingStatement -> GetInitializerValue () );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Const:
			{
				
				OilConstStatement * Constant = dynamic_cast <OilConstStatement *> ( Statement );
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Constant -> GetInitializerValue () );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
				
				NameStack.AddConstStatementMapping ( Constant -> GetName (), Constant );
				
			}
			break;
			
			case IOilStatement :: kStatementType_Expression:
			{
				
				OilExpression * Expression = dynamic_cast <OilExpression *> ( Statement );
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Expression );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Return:
			{
				
				OilReturn * Return = dynamic_cast <OilReturn *> ( Statement );
				
				if ( Return -> HasExpression () )
				{
					
					OilExpression * Expression = Return -> GetReturnedExpression ();
					
					AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Expression );
					
					if ( EResult == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( EResult == kAllusionResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return EResult;
					
				}
				
			}
			break;
			
			case IOilStatement :: kStatementType_IfElse:
			{
				
				OilIfElse * IfElse = dynamic_cast <OilIfElse *> ( Statement );
				
				OilExpression * Expression = IfElse -> GetIfClauseConditionExpression ();
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Expression );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
				OilStatementBody * Body = IfElse -> GetIfClauseStatementBody ();
				
				AllusionResolutionResult BResult = OilAllusionResolution_StatementBody ( NameStack, * Body, TopLoop );
				
				if ( BResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( BResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BResult;
				
				uint32_t ElseIfCount = IfElse -> HasElseIfClauses () ? IfElse -> GetElseIfClauseCount () : 0;
				
				for ( uint32_t I = 0; I < ElseIfCount; I ++ )
				{
					
					Expression = IfElse -> GetElseIfClauseConditionExpression ( I );
					
					EResult = OilAllusionResolution_Expression ( NameStack, * Expression );
					
					if ( EResult == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( EResult == kAllusionResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return EResult;
					
					Body = IfElse -> GetElseIfClauseStatementBody ( I );
					
					AllusionResolutionResult BResult = OilAllusionResolution_StatementBody ( NameStack, * Body, TopLoop );
					
					if ( BResult == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( BResult == kAllusionResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( BResult == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return BResult;
					
				}
				
				if ( IfElse -> HasElseClause () )
				{
					
					Body = IfElse -> GetElseClauseStatementBody ();
					
					AllusionResolutionResult BResult = OilAllusionResolution_StatementBody ( NameStack, * Body, TopLoop );
					
					if ( BResult == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( BResult == kAllusionResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( BResult == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return BResult;
					
				}
				
			}
			break;
			
			case IOilStatement :: kStatementType_Match:
			{
				
				OilMatch * Match = dynamic_cast <OilMatch *> ( Statement );
				
				OilExpression * Expression = Match -> GetMatcheeExpression ();
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Expression );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
				uint32_t BranchCount = Match -> GetBranchCount ();
				
				for ( uint32_t I = 0; I < BranchCount; I ++ )
				{
					
					OilMatchBranch * Branch = Match -> GetBranch ( I );
					
					AllusionResolutionResult BRResult = OilAllusionResolution_MatchBranch ( NameStack, * Branch, TopLoop );
					
					if ( BRResult == kAllusionResolutionResult_Success_Complete )
						Progress = true;
					else if ( BRResult == kAllusionResolutionResult_Success_Progress )
					{
						
						Progress = true;
						Unresolved = true;
						
					}
					else if ( BRResult == kAllusionResolutionResult_Success_NoProgress )
						Unresolved = true;
					else
						return BRResult;
					
				}
				
			}
			break;
			
			case IOilStatement :: kStatementType_WhileLoop:
			{
				
				OilWhileLoop * WhileLoop = dynamic_cast <OilWhileLoop *> ( Statement );
				
				OilExpression * Expression = WhileLoop -> GetConditionExpression ();
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Expression );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
				if ( WhileLoop -> HasLoopLabel () )
					NameStack.AddLabledLoopMapping ( std :: u32string ( U"`" ) + WhileLoop -> GetLoopLabel (), WhileLoop );
				
				OilStatementBody * Body = WhileLoop -> GetStatementBody ();
				
				AllusionResolutionResult BResult = OilAllusionResolution_StatementBody ( NameStack, * Body, WhileLoop );
				
				if ( BResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( BResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_DoWhileLoop:
			{
				
				OilDoWhileLoop * DoWhileLoop = dynamic_cast <OilDoWhileLoop *> ( Statement );
				
				if ( DoWhileLoop -> HasLoopLabel () )
					NameStack.AddLabledLoopMapping ( std :: u32string ( U"`" ) + DoWhileLoop -> GetLoopLabel (), DoWhileLoop );
				
				OilStatementBody * Body = DoWhileLoop -> GetStatementBody ();
				
				AllusionResolutionResult BResult = OilAllusionResolution_StatementBody ( NameStack, * Body, DoWhileLoop );
				
				if ( BResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( BResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BResult;
				
				OilExpression * Expression = DoWhileLoop -> GetConditionExpression ();
				
				AllusionResolutionResult EResult = OilAllusionResolution_Expression ( NameStack, * Expression );
				
				if ( EResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( EResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( EResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return EResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Loop:
			{
				
				OilLoop * Loop = dynamic_cast <OilLoop *> ( Statement );
				
				if ( Loop -> HasLoopLabel () )
					NameStack.AddLabledLoopMapping ( std :: u32string ( U"`" ) + Loop -> GetLoopLabel (), Loop );
				
				OilStatementBody * Body = Loop -> GetStatementBody ();
				
				AllusionResolutionResult BResult = OilAllusionResolution_StatementBody ( NameStack, * Body, Loop );
				
				if ( BResult == kAllusionResolutionResult_Success_Complete )
					Progress = true;
				else if ( BResult == kAllusionResolutionResult_Success_Progress )
				{
					
					Progress = true;
					Unresolved = true;
					
				}
				else if ( BResult == kAllusionResolutionResult_Success_NoProgress )
					Unresolved = true;
				else
					return BResult;
				
			}
			break;
			
			case IOilStatement :: kStatementType_Break:
			{
				
				OilBreak * Break = dynamic_cast <OilBreak *> ( Statement );
				
				if ( ! Break -> BrokenLoopResolved () )
				{
					
					if ( Break -> HasLoopLabel () )
					{
						
						OilAllusionResolution_NameMapStack :: NameMapping Lookup = NameStack.LookupName ( std :: u32string ( U"`" ) + Break -> GetLoopLabel () );
						
						if ( Lookup.Type != OilAllusionResolution_NameMapStack :: kMappingType_LabledLoop )
						{
							
							if ( Lookup.Type == OilAllusionResolution_NameMapStack :: kMappingType_None )
							{
								
								LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Break -> GetSourceRef () ) + "break label refers to non-existant of loop" );
								
								return kAllusionResolutionResult_Error;
								
							}
														
							LOG_FATALERROR ( "internal error: break label refers to a non loop-label type name" );
							
							return kAllusionResolutionResult_Error;
							
						}
						
						Break -> SetBrokenLoop ( Lookup.LabledLoop );
						
					}
					else
					{
						
						if ( TopLoop == NULL )
						{
							
							LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Break -> GetSourceRef () ) + "break statement outside of loop" );
							
							return kAllusionResolutionResult_Error;
							
						}
						
						Break -> SetBrokenLoop ( TopLoop );
						
					}
					
				}
				
			}
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

AllusionResolutionResult OilAllusionResolution_MatchBranch ( OilAllusionResolution_NameMapStack & NameStack, OilMatchBranch & Branch, IOilLoop * TopLoop )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	NameStack.PushContext ( OilAllusionResolution_NameMapStack :: kNameContext_MatchBranch );
	OilAllusionResolution_ScopedNameStackContextReleaser NS_Releaser ( NameStack );
	
	switch ( Branch.GetMatchType () )
	{
		
		case OilMatchBranch :: kMatchType_Allusion:
		{
			
			AllusionResolutionResult ARResult = OilAllusionResolution_Allusion ( NameStack, * Branch.GetMatchAllusion () );
			
			if ( ARResult == kAllusionResolutionResult_Success_Complete )
				Progress = true;
			else if ( ARResult == kAllusionResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( ARResult == kAllusionResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ARResult;
			
		}
		break;
		
		case OilMatchBranch :: kMatchType_AllusionValue:
		{
			
			AllusionResolutionResult ARResult = OilAllusionResolution_Allusion ( NameStack, * Branch.GetMatchAllusion () );
			
			if ( ARResult == kAllusionResolutionResult_Success_Complete )
				Progress = true;
			else if ( ARResult == kAllusionResolutionResult_Success_Progress )
			{
				
				Progress = true;
				Unresolved = true;
				
			}
			else if ( ARResult == kAllusionResolutionResult_Success_NoProgress )
				Unresolved = true;
			else
				return ARResult;
			
			NameStack.AddMatchBranchValueMapping ( Branch.GetAllusionValueName (), & Branch );
			
		}
		break;
		
		case OilMatchBranch :: kMatchType_Destructure:
		{
			
			OilStructDestructure * Destructure = Branch.GetMatchDestructure ();
			AddDestructureNames ( NameStack, * Destructure );
			
		}
		break;
		
		case OilMatchBranch :: kMatchType_Constant:
		case OilMatchBranch :: kMatchType_Other:
		break;
		
	}
	
	OilStatementBody * Body = Branch.GetStatementBody ();
	
	AllusionResolutionResult SBResult = OilAllusionResolution_StatementBody ( NameStack, * Body, TopLoop );
	
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
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		
		return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

void AddDestructureNames ( OilAllusionResolution_NameMapStack & NameStack, OilStructDestructure & Destructure )
{
	
	uint32_t MemberCount = Destructure.GetMemberDestructureCount ();
	
	for ( uint32_t I = 0; I < MemberCount; I ++ )
	{
		
		OilMemberDestructure * Member = Destructure.GetMemberDestructure ( I );
		
		if ( ! Member -> IsIgnored () )
		{
			
			if ( Member -> IsSubDestructure () )
				AddDestructureNames ( NameStack, * Member -> GetSubDestructure () );
			else
				NameStack.AddMemberDestructureMapping ( Member -> GetValueName (), Member );
			
		}
		
	}
	
}

AllusionResolutionResult OilAllusionResolution_Function ( OilAllusionResolution_NameMapStack & NameStack, OilFunctionDefinition & FunctionDefinition )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	NameStack.PushContext ( OilAllusionResolution_NameMapStack :: kNameContext_Function );
	OilAllusionResolution_ScopedNameStackContextReleaser NS_Releaser ( NameStack );
	
	OilFunctionParameterList * Parameters = FunctionDefinition.GetParameterList ();
	uint32_t ParamCount = Parameters -> GetParameterCount ();
	
	for ( uint32_t I = 0; I < ParamCount; I ++ )
	{
		
		OilFunctionParameter * Param = Parameters -> GetFunctionParameter ( I );
		
		NameStack.AddFunctionParameterMapping ( Param -> GetName (), Param );
		
	}
	
	OilStatementBody * Body = FunctionDefinition.GetStatementBody ();
	
	AllusionResolutionResult SBResult = OilAllusionResolution_StatementBody ( NameStack, * Body, NULL );
	
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
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		
		return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilAllusionResolution_Expression ( OilAllusionResolution_NameMapStack & NameStack, OilExpression & Expression )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	// TODO: Implement 
	(void) NameStack;
	(void) Expression;
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		
		return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilAllusionResolution_Allusion_FinalNamespaceSearchResult ( OilNamespaceDefinition :: NameSearchResult & NamespaceSearchResult, OilAllusion & Allusion )
{
	
	(void) NamespaceSearchResult;
	(void) Allusion;
	
	// TODO: Implement
	
	return kAllusionResolutionResult_Success_Complete;
	
}

AllusionResolutionResult OilAllusionResolution_Allusion ( OilAllusionResolution_NameMapStack & NameStack, OilAllusion & Allusion )
{
	
	bool Unresolved = false;
	bool Progress = false;
	
	if ( Allusion.IsResolved () )
		return kAllusionResolutionResult_Success_Complete;
	
	OilNamespaceDefinition :: NameSearchResult NamespaceSearchResult;
	OilAllusionResolution_NameMapStack :: NameMapping NameStackSearchResult;
	
	switch ( Allusion.GetTarget () )
	{
		
		case OilAllusion :: kAllusionTarget_Namespaced:
		{
			
			NameStackSearchResult = NameStack.LookupName ( Allusion.GetNamespaceName ( 0 ) );
			
			OilNamespaceDefinition * CurrentNamespace = NULL;
			OilTypeDefinition * CurrentTypeDefinition = NULL;
			OilTypeAlias * CurrentTypeAlias = NULL;
			
			if ( NameStackSearchResult.Type == OilAllusionResolution_NameMapStack :: kMappingType_None )
			{
				
				NameStack.GetGlobalNamespace ().SearchName ( Allusion.GetNamespaceName ( 0 ), NamespaceSearchResult );
				
				if ( NamespaceSearchResult.Type == OilNamespaceDefinition :: kNameSearchResultType_SubNamespace )
					CurrentNamespace = NamespaceSearchResult.NamespaceDefinition;
				else if ( NamespaceSearchResult.Type == OilNamespaceDefinition :: kNameSearchResultType_TypeDefinition )
				{
					
					if ( Allusion.GetNamespaceNameCount () != 1 )
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"" + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( 0 ) ) + "\" does not refer to a namespace!" );
						
						return kAllusionResolutionResult_Error;
						
					}
					
					CurrentTypeDefinition = NamespaceSearchResult.TypeDefinition;
					
				}
				else if ( NamespaceSearchResult.Type == OilNamespaceDefinition :: kNameSearchResultType_TypeAlias )
				{
					
					if ( Allusion.GetNamespaceNameCount () != 1 )
					{
						
						LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"" + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( 0 ) ) + "\" does not refer to a namespace!" );
						
						return kAllusionResolutionResult_Error;
						
					}
					
					CurrentTypeAlias = NamespaceSearchResult.Alias;
					
				}
				
			}
			else if ( NameStackSearchResult.Type == OilAllusionResolution_NameMapStack :: kMappingType_Namespace )
				CurrentNamespace = NameStackSearchResult.Namespace;
			else if ( NameStackSearchResult.Type == OilAllusionResolution_NameMapStack :: kMappingType_TypeDefinition )
			{
				
				if ( Allusion.GetNamespaceNameCount () != 1 )
				{
					
					LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"" + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( 0 ) ) + "\" does not refer to a namespace!" );
					
					return kAllusionResolutionResult_Error;
					
				}
				
				CurrentTypeDefinition = NamespaceSearchResult.TypeDefinition;
				
			}
			else if ( NameStackSearchResult.Type == OilAllusionResolution_NameMapStack :: kMappingType_TypeAlias )
			{
				
				if ( Allusion.GetNamespaceNameCount () != 1 )
				{
					
					LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"" + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( 0 ) ) + "\" does not refer to a namespace!" );
					
					return kAllusionResolutionResult_Error;
					
				}
				
				CurrentTypeAlias = NameStackSearchResult.TypeAlias;
				
			}
			else
			{
				
				LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"" + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( 0 ) ) + "\" does not refer to a namespace!" );
				
				return kAllusionResolutionResult_Error;
				
			}
			
			if ( CurrentNamespace != NULL )
			{
				
				uint32_t CurrentNameIndex = 1;
				uint32_t NameLength = Allusion.GetNamespaceNameCount ();
				
				while ( CurrentNameIndex < NameLength )
				{
					
					CurrentNamespace -> SearchName ( Allusion.GetNamespaceName ( CurrentNameIndex ), NamespaceSearchResult );
					CurrentNamespace = NULL;
					CurrentNameIndex ++;
					
					if ( NamespaceSearchResult.Type != OilNamespaceDefinition :: kNameSearchResultType_SubNamespace )
					{
						
						if ( ( NamespaceSearchResult.Type == OilNamespaceDefinition :: kNameSearchResultType_None ) || ( CurrentNameIndex != NameLength ) )
						{
							
							LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"" + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( CurrentNameIndex - 1 ) ) + "\" does not refer to a namespace!" );
							
							return kAllusionResolutionResult_Error;
							
						}
						
						if ( NamespaceSearchResult.Type == OilNamespaceDefinition :: kNameSearchResultType_TypeDefinition )
							CurrentTypeDefinition = NamespaceSearchResult.TypeDefinition;
						else if ( NamespaceSearchResult.Type == OilNamespaceDefinition :: kNameSearchResultType_TypeAlias )
							CurrentTypeAlias = NamespaceSearchResult.Alias;
						else
						{
							
							LOG_FATALERROR_NOFILE ( SourceRefToPositionString ( Allusion.GetSourceRef () ) + "\"" + CodeConversion :: ConvertUTF32ToUTF8 ( Allusion.GetNamespaceName ( CurrentNameIndex - 1 ) ) + "\" does not refer to a namespace!" );
							
							return kAllusionResolutionResult_Error;
							
						}
						
					}
					else
						CurrentNamespace = NamespaceSearchResult.NamespaceDefinition;
					
				}
				
			}
			
			if ( CurrentNamespace != NULL )
			{
				
				CurrentNamespace -> SearchName ( Allusion.GetName (), NamespaceSearchResult );
				
				return OilAllusionResolution_Allusion_FinalNamespaceSearchResult ( NamespaceSearchResult, Allusion );
				
			}
			
		}
		break;
		
		case OilAllusion :: kAllusionTarget_Namespaced_Absolue:
		case OilAllusion :: kAllusionTarget_Namespaced_Templated:
		case OilAllusion :: kAllusionTarget_Namespaced_Absolue_Templated:
		case OilAllusion :: kAllusionTarget_Self_Unchecked:
		
		case OilAllusion :: kAllusionTarget_Indeterminate:
		case OilAllusion :: kAllusionTarget_Indeterminate_Templated:
		break;
		
		default:
		break;
		
	}
	
	
	(void) NameStack;
	(void) Allusion;
	
	if ( Unresolved )
	{
		
		if ( Progress )
			return kAllusionResolutionResult_Success_Progress;
		
		return kAllusionResolutionResult_Success_NoProgress;
		
	}
	
	return kAllusionResolutionResult_Success_Complete;
	
}
