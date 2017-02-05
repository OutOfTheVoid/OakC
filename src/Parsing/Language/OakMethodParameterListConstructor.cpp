#include <Parsing/Language/OakMethodParameterListConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakSelfParameterConstructor.h>
#include <Parsing/Language/OakSelfParameterPointerConstructor.h>
#include <Parsing/Language/OakFunctionParameterConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakSelfParameterConstructor _OakMethodParameterListConstructor_OakSelfParameterConstructorInstance;
OakSelfParameterPointerConstructor _OakMethodParameterListConstructor_OakSelfParameterPointerConstructorInstance;

OakFunctionParameterConstructor _OakMethodParameterListConstructor_OakFunctionParameterConstructorInstance;

OakMethodParameterListConstructor :: OakMethodParameterListConstructor ():
	SelfParameterConstructionGroup (),
	ParameterConstructionGroup ()
{
	
	SelfParameterConstructionGroup.AddConstructorCantidate ( & _OakMethodParameterListConstructor_OakSelfParameterConstructorInstance, 0 );
	SelfParameterConstructionGroup.AddConstructorCantidate ( & _OakMethodParameterListConstructor_OakSelfParameterPointerConstructorInstance, 1 );
	
	ParameterConstructionGroup.AddConstructorCantidate ( & _OakMethodParameterListConstructor_OakFunctionParameterConstructorInstance, 0 );
	
}

OakMethodParameterListConstructor :: ~OakMethodParameterListConstructor ()
{
}

void OakMethodParameterListConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	LOG_VERBOSE ( "**A" );
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	LOG_VERBOSE ( "**B" );
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Open )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	LOG_VERBOSE ( "**C" );
	
	ASTElement * MethodParamsElement = new ASTElement ();
	MethodParamsElement -> SetTag ( OakASTTags :: kASTTag_MethodParameterList );
	MethodParamsElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( SelfParameterConstructionGroup.TryConstruction ( MethodParamsElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	LOG_VERBOSE ( "**D" );
	
	if ( Error )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	LOG_VERBOSE ( "**E" );
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	LOG_VERBOSE ( std :: string ( "TOKEN: " ) + OakTokenTags :: TagNames [ CurrentToken -> GetTag () ] );
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Comma )
	{
		
		LOG_VERBOSE ( "**E_A" );
		
		TokenCount --;
		
		while ( ParameterConstructionGroup.TryConstruction ( MethodParamsElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
		{
			
			LOG_VERBOSE ( "**E_B" );
			
			if ( TokenCount == 0 )
			{
				
				delete MethodParamsElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = "Expected closing parethesis at end of method parameter list";
				Output.ErrorProvokingToken = CurrentToken;
				
				return;
				
			}
			
			LOG_VERBOSE ( "**E_D" );
			
			CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
				break;
			
			LOG_VERBOSE ( "**E_E" );
				
			TokenCount --;
			
		}
		
	}
	
	LOG_VERBOSE ( "**F" );
	
	if ( Error )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	LOG_VERBOSE ( "**G" );
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parenthesis at end of method parameter list";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	LOG_VERBOSE ( "**H" );
	
	MethodParamsElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = MethodParamsElement;
	
}
