#include <Parsing/Language/OakFunctionParameterListConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakFunctionParameterConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakFunctionParameterListConstructor OakFunctionParameterListConstructor :: Instance;

OakFunctionParameterConstructor _OakFunctionParameterListConstructor_OakFunctionParameterConstructorInstance;

OakFunctionParameterListConstructor :: OakFunctionParameterListConstructor ():
	ParameterConstructionGroup ()
{
	
	ParameterConstructionGroup.AddConstructorCantidate ( & OakFunctionParameterConstructor :: Instance, 0 );
	
}

OakFunctionParameterListConstructor :: ~OakFunctionParameterListConstructor ()
{
}

void OakFunctionParameterListConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Open )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * FunctionParamsElement = new ASTElement ();
	FunctionParamsElement -> SetTag ( OakASTTags :: kASTTag_FunctionParameterList );
	FunctionParamsElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	while ( ParameterConstructionGroup.TryConstruction ( FunctionParamsElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		if ( TokenCount == 0 )
		{
			
			delete FunctionParamsElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing parethesis at end of function parameter list";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
			break;
			
		TokenCount --;
		
	}
	
	if ( Error )
	{
		
		delete FunctionParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
	{
		
		delete FunctionParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis at end of function parameter list";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	FunctionParamsElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = FunctionParamsElement;
	
}

void OakFunctionParameterListConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
