#include <Parsing/Language/OakFunctionCallParameterListConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>

#include <Parsing/Language/OakASTTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakFunctionCallParameterListConstructor OakFunctionCallParameterListConstructor :: Instance;

OakFunctionCallParameterListConstructor :: OakFunctionCallParameterListConstructor ():
	ParameterGroup ()
{
	
	ParameterGroup.AddConstructorCantidate ( & OakExpressionConstructor :: Instance, 0 );
	
}

OakFunctionCallParameterListConstructor :: ~OakFunctionCallParameterListConstructor ()
{
}

void OakFunctionCallParameterListConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount;
	
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
	
	Output.Accepted = true;
	Output.ConstructedElement = ParameterListElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
