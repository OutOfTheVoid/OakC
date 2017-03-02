#include <Parsing/Language/OakSelfParameterReferenceConstructor.h>
#include <Parsing/Language/OakSelfParameterConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

OakSelfParameterReferenceConstructor OakSelfParameterReferenceConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakSelfParameterReferenceConstructor_SelfParamGroupEntries [] = { { & OakSelfParameterConstructor :: Instance, 0 } };

OakSelfParameterReferenceConstructor :: OakSelfParameterReferenceConstructor ():
	SelfParamGroup ( _OakSelfParameterReferenceConstructor_SelfParamGroupEntries, 1 )
{
}

OakSelfParameterReferenceConstructor :: ~OakSelfParameterReferenceConstructor ()
{
}

void OakSelfParameterReferenceConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( Input.Tokens [ 0 ] -> GetTag () != OakTokenTags :: kTokenTag_Ampersand )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * SelfParamReferenceElement = new ASTElement ();
	SelfParamReferenceElement -> SetTag ( OakASTTags :: kASTTag_SelfParameterReference );
	SelfParamReferenceElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool ConstructionError = false;
	std :: string ErrorString;
	const Token * ErrorToken;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( SelfParamGroup.TryConstruction ( SelfParamReferenceElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete SelfParamReferenceElement;
		
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
	Output.ConstructedElement = SelfParamReferenceElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
