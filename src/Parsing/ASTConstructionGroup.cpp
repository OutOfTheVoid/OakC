#include <Parsing/ASTConstructionGroup.h>

#ifndef NULL
	#define NULL nullptr
#endif

#include <Parsing/IASTConstructor.h>

#include <Encoding/CodeConversion.h>

#include <Tokenization/Language/OakTokenTags.h>

ASTConstructionGroup :: ASTConstructionGroup ():
	Constructors ()
{
}

ASTConstructionGroup :: ASTConstructionGroup ( StaticInitEntry * EntryList, uint32_t EntryCount ):
	Constructors ()
{
	
	for ( uint32_t I = 0; I < EntryCount; I ++ )
		AddConstructorCantidate ( EntryList [ I ].Cantidate, EntryList [ I ].Priority );
	
}

ASTConstructionGroup :: ~ASTConstructionGroup ()
{
}

void ASTConstructionGroup :: AddConstructorCantidate ( const IASTConstructor * Cantidate, uint32_t Priority )
{
	
	if ( Cantidate == NULL )
		return;
	
	ConstructorRecord Record;
	
	Record.Priority = Priority;
	Record.Cantidate = Cantidate;
	
	uint32_t Index = 0;
	
	while ( Index < Constructors.size () )
	{
		
		if ( Constructors [ Index ].Priority > Priority )
			break;
		
		Index ++;
		
	}
	
	if ( Index >= Constructors.size () )
	{
		
		Constructors.push_back ( Record );
		
		return;
		
	}
	
	Constructors.insert ( Constructors.begin () + Index, Record );
	
}

ASTElement * ASTConstructionGroup :: TryConstructSingleNoParent ( uint64_t DummyParentTag, bool & Error, std :: string & ErrorSuggestion, const Token * & ErrorProvokingToken, const Token ** TokenList, uint64_t & AvailableTokens ) const
{
	
	if ( Constructors.size () == 0 )
	{
		
		Error = false;
		
		return 0;
		
	}
	
	ASTElement Dummy;
	
	Dummy.SetTag ( DummyParentTag );
	
	for ( uint64_t I = 0; I < Constructors.size (); I ++ )
	{
		
		IASTConstructor :: ASTConstructionInput Input;
		IASTConstructor :: ASTConstructionOutput Output;
		
		Input.Tokens = TokenList;
		Input.AvailableTokenCount = AvailableTokens;
		Input.ParentElement = & Dummy;
		
		Output.Accepted = false;
		Output.Error = false;
		Output.ErrorSuggestion = "";
		Output.TokensConsumed = 0;
		Output.ConstructedElement = NULL;
		Output.ErrorProvokingToken = NULL;
		
		Constructors [ I ].Cantidate -> TryConstruct ( Input, Output );
		
		if ( Output.Accepted )
		{
			
			AvailableTokens -= Output.TokensConsumed;
			
			return Output.ConstructedElement;
			
		}
		else if ( Output.Error && ! Error )
		{
			
			Error = true;
			ErrorSuggestion = Output.ErrorSuggestion;
			ErrorProvokingToken = Output.ErrorProvokingToken;
			
		}
		
	}
	
	return NULL;
	
}

uint64_t ASTConstructionGroup :: TryConstruction ( ASTElement * RootElement, uint64_t SubElementLimit, bool & Error, std :: string & ErrorSuggestion, const Token * & ErrorProvokingToken, const Token ** TokenList, uint64_t & AvailableTokens ) const
{
	
	if ( RootElement == NULL )
	{
		
		Error = true;
		ErrorSuggestion = "Internal error: AST Root node not set";
		
		return 0;
		
	}
	
	Error = false;
	
	if ( Constructors.size () == 0 )
		return 0;
	
	uint64_t SubElementCount = 0;
	uint64_t TokenOffset = 0;
	
	while ( SubElementCount < SubElementLimit )
	{
		
		bool Found = false;
		
		for ( uint64_t I = 0; I < Constructors.size (); I ++ )
		{
			
			IASTConstructor :: ASTConstructionInput Input;
			IASTConstructor :: ASTConstructionOutput Output;
			
			Input.Tokens = & TokenList [ TokenOffset ];
			Input.AvailableTokenCount = AvailableTokens - TokenOffset;
			Input.ParentElement = RootElement;
			
			Output.Accepted = false;
			Output.Error = false;
			Output.ErrorSuggestion = "";
			Output.TokensConsumed = 0;
			Output.ConstructedElement = NULL;
			Output.ErrorProvokingToken = NULL;
			
			Constructors [ I ].Cantidate -> TryConstruct ( Input, Output );
			
			if ( Output.Accepted )
			{
				
				Error = false;
				Found = true;
				
				if ( Output.ConstructedElement != NULL )
					RootElement -> AddSubElement ( Output.ConstructedElement );
				
				SubElementCount ++;
				
				TokenOffset += Output.TokensConsumed;
				
				if ( TokenOffset >= AvailableTokens )
				{
					
					AvailableTokens = 0;
					
					return SubElementCount;
					
				}
				
				break;
				
			}
			else if ( Output.Error && ! Error )
			{
				
				Error = true;
				ErrorSuggestion = Output.ErrorSuggestion;
				ErrorProvokingToken = Output.ErrorProvokingToken;
				
			}
			
		}
		
		if ( ! Found )
			break;
		
	}
	
	AvailableTokens -= TokenOffset;
	
	return SubElementCount;
	
}
