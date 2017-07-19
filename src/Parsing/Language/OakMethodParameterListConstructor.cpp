#include <Parsing/Language/OakMethodParameterListConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakSelfParameterConstructor.h>
#include <Parsing/Language/OakSelfParameterReferenceConstructor.h>
#include <Parsing/Language/OakFunctionParameterConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakMethodParameterListConstructor & OakMethodParameterListConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakMethodParameterListConstructor> ();
	
}

OakMethodParameterListConstructor :: OakMethodParameterListConstructor ():
	SelfParameterConstructionGroup ( 
	{
		
		{ & ( OakSelfParameterConstructor :: Instance () ), 0 },
		{ & ( OakSelfParameterReferenceConstructor :: Instance () ), 1 }
			
	} ),
	ParameterConstructionGroup ( { { & ( OakFunctionParameterConstructor :: Instance () ), 0 } } )
{
}

OakMethodParameterListConstructor :: ~OakMethodParameterListConstructor ()
{
}

void OakMethodParameterListConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
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
	
	ASTElement * MethodParamsElement = new ASTElement ();
	MethodParamsElement -> SetTag ( OakASTTags :: kASTTag_MethodParameterList );
	MethodParamsElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( SelfParameterConstructionGroup.TryConstruction ( MethodParamsElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( Error )
		{
			
			delete MethodParamsElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected self parameter in method";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parethesis at end of method parameter list";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Comma )
	{
		
		TokenCount --;
		
		while ( ParameterConstructionGroup.TryConstruction ( MethodParamsElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
		{
			
			if ( TokenCount == 0 )
			{
				
				delete MethodParamsElement;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = "Expected closing parethesis at end of method parameter list";
				Output.ErrorProvokingToken = CurrentToken;
				
				return;
				
			}
			
			CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
			
			if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
				break;
				
			TokenCount --;
			
		}
		
	}
	
	if ( Error )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete MethodParamsElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing parethesis at end of method parameter list";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
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
	
	MethodParamsElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = MethodParamsElement;
	
}
