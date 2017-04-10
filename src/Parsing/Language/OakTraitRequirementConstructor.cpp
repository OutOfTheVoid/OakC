#include <Parsing/Language/OakTraitRequirementConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakNamespacedTemplatedTraitNameConstructor.h>
#include <Parsing/Language/OakNamespacedTraitNameConstructor.h>
#include <Parsing/Language/OakTemplatedTraitNameConstructor.h>
#include <Parsing/Language/OakBareTraitNameConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakTraitRequirementConstructor OakTraitRequirementConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakTraitRequirementConstructor_TraitRefGroupEntries []
{
	
	{ & OakNamespacedTemplatedTraitNameConstructor :: Instance, 0 },
	{ & OakNamespacedTraitNameConstructor :: Instance, 1 },
	{ & OakTemplatedTraitNameConstructor :: Instance, 1 },
	{ & OakBareTraitNameConstructor :: Instance, 2 },
	
};

OakTraitRequirementConstructor :: OakTraitRequirementConstructor ():
	TraitRefGroup ( _OakTraitRequirementConstructor_TraitRefGroupEntries, 4 )
{
}

OakTraitRequirementConstructor :: ~OakTraitRequirementConstructor ()
{
}

void OakTraitRequirementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Require ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * RequireElement = new ASTElement ();
	RequireElement -> SetTag ( OakASTTags :: kASTTag_TraitRequirement );
	RequireElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( TraitRefGroup.TryConstruction ( RequireElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected trait name after require keyword in trait definition";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ];
		
		return;
		
	}
	
	if ( Error )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = RequireElement;
	
}
