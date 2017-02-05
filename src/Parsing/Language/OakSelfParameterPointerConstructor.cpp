#include <Parsing/Language/OakSelfParameterPointerConstructor.h>
#include <Parsing/Language/OakSelfParameterConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

OakSelfParameterConstructor _OakSelfParameterPointerConstructor_OakSelfParameterConstructorInstance;

OakSelfParameterPointerConstructor :: OakSelfParameterPointerConstructor ():
	SelfParamGroup ()
{
	
	SelfParamGroup.AddConstructorCantidate ( & _OakSelfParameterPointerConstructor_OakSelfParameterConstructorInstance, 0 );
	
}

OakSelfParameterPointerConstructor :: ~OakSelfParameterPointerConstructor ()
{
}

void OakSelfParameterPointerConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( Input.Tokens [ 0 ] -> GetTag () != OakTokenTags :: kTokenTag_Star )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * SelfParamPointerElement = new ASTElement ();
	SelfParamPointerElement -> SetTag ( OakASTTags :: kASTTag_SelfParameterPointer );
	SelfParamPointerElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool ConstructionError = false;
	std :: string ErrorString;
	const Token * ErrorToken;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( SelfParamGroup.TryConstruction ( SelfParamPointerElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete SelfParamPointerElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.ConstructedElement = SelfParamPointerElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
