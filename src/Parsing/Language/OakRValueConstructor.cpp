#include <Parsing/Language/OakRValueConstructor.h>
#include <Parsing/Language/OakLiteralRValueConstructor.h>

#include <Parsing/Language/OakASTTags.h>

OakLiteralRValueConstructor _OakRValueConstructor_OakLiteralRValueConstructorInstance;

OakRValueConstructor :: OakRValueConstructor ():
	ValueGroup ()
{
	
	
	
	// This must be the highest priority ( last tested ).
	ValueGroup.AddConstructorCantidate ( & _OakRValueConstructor_OakLiteralRValueConstructorInstance, 1 );
	
}

OakRValueConstructor :: ~OakRValueConstructor ()
{
}

void OakRValueConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * RValueElement = new ASTElement ();
	
	RValueElement -> SetTag ( OakASTTags :: kASTTag_RValue );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( ValueGroup.TryConstruction ( RValueElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete RValueElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete RValueElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = RValueElement;
	
}

