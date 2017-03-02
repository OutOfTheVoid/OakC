#include <Parsing/Language/OakFunctionCallParameterListConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>

#include <Parsing/Language/OakASTTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakFunctionCallParameterListConstructor OakFunctionCallParameterListConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakFunctionCallParameterListConstructor_ParameterGroup [] = { { & OakExpressionConstructor :: Instance, 0 } };

OakFunctionCallParameterListConstructor :: OakFunctionCallParameterListConstructor ():
	ParameterGroup ( _OakFunctionCallParameterListConstructor_ParameterGroup, 1 )
{
}

OakFunctionCallParameterListConstructor :: ~OakFunctionCallParameterListConstructor ()
{
}

void OakFunctionCallParameterListConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	ASTElement * ParameterListElement = new ASTElement ();
	ParameterListElement -> SetTag ( OakASTTags :: kASTTag_FunctionCall_ParameterList );
	
	bool SkipLoop = false;
	
	if ( ParameterGroup.TryConstruction ( ParameterListElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( Error )
		{
			
			delete ParameterListElement;
			
			Output.Error = true;
			Output.Accepted = false;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		SkipLoop = true;
		
	}
	
	if ( Error )
	{
		
		delete ParameterListElement;
		
		Output.Error = true;
		Output.Accepted = false;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	while ( ( ! SkipLoop ) && ( Input.AvailableTokenCount > 0 ) )
	{
		
		const Token * CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
			break;
		
		ParameterListElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
		if ( ParameterGroup.TryConstruction ( ParameterListElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
		{
			
			if ( Error )
			{
				
				delete ParameterListElement;
				
				Output.Error = true;
				Output.Accepted = false;
				Output.ErrorSuggestion = ErrorString;
				Output.ErrorProvokingToken = ErrorToken;
				
				return;
				
			}
			
			break;
			
		}
		
		if ( Error )
		{
			
			delete ParameterListElement;
			
			Output.Error = true;
			Output.Accepted = false;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete ParameterListElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Exected closing parenthesis at end of function call parameters";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Parenthesis_Close )
	{
		
		delete ParameterListElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Exected closing parenthesis at end of function call parameters";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.ConstructedElement = ParameterListElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
