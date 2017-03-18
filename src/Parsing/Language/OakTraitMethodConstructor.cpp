#include <Parsing/Language/OakTraitMethodConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakMethodParameterListConstructor.h>
#include <Parsing/Language/OakReturnTypeConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakTraitMethodConstructor OakTraitMethodConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakTraitMethodConstructor_TemplateConstructionGroupEntries [] = { { & OakTemplateDefinitionConstructor :: Instance, 0 } };
ASTConstructionGroup :: StaticInitEntry _OakTraitMethodConstructor_ParameterListConstructionGroupEntries [] = { { & OakMethodParameterListConstructor :: Instance, 0 } };
ASTConstructionGroup :: StaticInitEntry _OakTraitMethodConstructor_ReturnTypeConstructionGroupEntries [] = { { & OakReturnTypeConstructor :: Instance, 0 } };

OakTraitMethodConstructor :: OakTraitMethodConstructor ():
	TemplateConstructionGroup ( _OakTraitMethodConstructor_TemplateConstructionGroupEntries, 1 ),
	ParameterListConstructionGroup ( _OakTraitMethodConstructor_ParameterListConstructionGroupEntries, 1 ),
	ReturnTypeConstructionGroup ( _OakTraitMethodConstructor_ReturnTypeConstructionGroupEntries, 1 )
{
}

OakTraitMethodConstructor :: ~OakTraitMethodConstructor ()
{
}

void OakTraitMethodConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Function ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier for function name";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ElementData * TraitFunctionData = new ElementData ();
	
	TraitFunctionData -> Name = CurrentToken -> GetSource ();
	TraitFunctionData -> Templated = false;
	TraitFunctionData -> ReturnTyped = false;
	
	ASTElement * TraitFunctionElement = new ASTElement ();
	
	TraitFunctionElement -> SetTag ( OakASTTags :: kASTTag_TraitMethod );
	TraitFunctionElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	TraitFunctionElement -> SetData ( TraitFunctionData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( TemplateConstructionGroup.TryConstruction ( TraitFunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 2 ], TokenCount ) != 0 )
	{
		
		TraitFunctionData -> Templated = true;
		
		ASTElement * TemplateElement = TraitFunctionElement -> GetSubElement ( TraitFunctionElement -> GetSubElementCount () - 1 );
		
		if ( reinterpret_cast <OakTemplateDefinitionConstructor :: ElementData *> ( TemplateElement -> GetData () ) -> DoubleTemplateClose || reinterpret_cast <OakTemplateDefinitionConstructor :: ElementData *> ( TemplateElement -> GetData () ) -> TripleTemplateClose )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Unexpected closing triangle bracket after end of template definition";
			Output.ErrorProvokingToken = TemplateElement -> GetToken ( TemplateElement -> GetTokenSectionCount () - 1, TemplateElement -> GetTokenCount ( TemplateElement -> GetTokenSectionCount () - 1 ) - 1 );
			
			delete TraitFunctionElement;
			
			return;
			
		}
		
		if ( TokenCount < 2 )
		{
			
			delete TraitFunctionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected body for function definition";
			Output.ErrorProvokingToken = NULL;
			
			return;
			
		}
		
	}
	else if ( Error )
	{
		
		delete TraitFunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( ParameterListConstructionGroup.TryConstruction ( TraitFunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete TraitFunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	else if ( Error )
	{
		
		delete TraitFunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( ReturnTypeConstructionGroup.TryConstruction ( TraitFunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
		TraitFunctionData -> ReturnTyped = true;
	
	if ( Error )
	{
		
		delete TraitFunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = TraitFunctionElement;
	
}

void OakTraitMethodConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
