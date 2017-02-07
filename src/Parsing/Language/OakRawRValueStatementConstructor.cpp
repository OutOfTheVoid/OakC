#include <Parsing/Language/OakRawRValueStatementConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakRValueConstructor.h>

#include <Tokenization/Language/OakTokenTags.h>

OakRValueConstructor _OakRawRValueStatementConstructor_OakRValueConstructorInstance;

OakRawRValueStatementConstructor :: OakRawRValueStatementConstructor ():
	RValueGroup ()
{
	
	RValueGroup.AddConstructorCantidate ( & _OakRawRValueStatementConstructor_OakRValueConstructorInstance, 0 );
	
}
	
OakRawRValueStatementConstructor :: ~OakRawRValueStatementConstructor ()
{
}

void OakRawRValueStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * StatementElement = new ASTElement ();
	
	StatementElement -> SetTag ( OakASTTags :: kASTTag_RawRValueStatement );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( RValueGroup.TryConstruction ( StatementElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete StatementElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete StatementElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		delete StatementElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = StatementElement;
	
}
