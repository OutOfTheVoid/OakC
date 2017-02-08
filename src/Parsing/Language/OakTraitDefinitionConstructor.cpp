#include <Parsing/Language/OakTraitDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakTraitFunctionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakTemplateDefinitionConstructor _OakTraitDefinitionConstructor_OakTemplateDefinitionConstructorInstance;
OakTraitFunctionConstructor _OakTraitDefinitionConstructor_OakTraitFunctionConstructorInstance;

OakTraitDefinitionConstructor :: OakTraitDefinitionConstructor ():
	TemplateConstructionGroup (),
	TraitBodyConstructionGroup ()
{
	
	TemplateConstructionGroup.AddConstructorCantidate ( & _OakTraitDefinitionConstructor_OakTemplateDefinitionConstructorInstance, 0 );
	TraitBodyConstructionGroup.AddConstructorCantidate ( & _OakTraitDefinitionConstructor_OakTraitFunctionConstructorInstance, 0 );
	
}

OakTraitDefinitionConstructor :: ~OakTraitDefinitionConstructor ()
{	
}

void OakTraitDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Trait ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier for struct name";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ElementData * TraitData = new ElementData ();
	
	TraitData -> Name = CurrentToken -> GetSource ();
	TraitData -> Templated = false;
	TraitData -> Empty = false;
	
	ASTElement * TraitElement = new ASTElement ();
	
	TraitElement -> SetTag ( OakASTTags :: kASTTag_TraitDefinition );
	TraitElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	TraitElement -> SetData ( TraitData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( TemplateConstructionGroup.TryConstruction ( TraitElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 2 ], TokenCount ) != 0 )
	{
		
		TraitData -> Templated = true;
		
		ASTElement * TemplateElement = TraitElement -> GetSubElement ( TraitElement -> GetSubElementCount () - 1 );
		
		if ( reinterpret_cast <OakTemplateDefinitionConstructor :: ElementData *> ( TemplateElement -> GetData () ) -> DoubleTemplateClose )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Unexpected closing triangle bracket after end of template definition";
			Output.ErrorProvokingToken = TemplateElement -> GetToken ( TemplateElement -> GetTokenSectionCount () - 1, TemplateElement -> GetTokenCount ( TemplateElement -> GetTokenSectionCount () - 1 ) - 1 );
			
			delete TraitElement;
			
			return;
			
		}
		
	}
	else if ( Error )
	{
		
		delete TraitElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount < 2 )
	{
		
		delete TraitElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for trait definition";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Semicolon )
		{
			
			TraitElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			TraitData -> Empty = true;
			
			TokenCount --;
			
			Output.Accepted = true;
			Output.ConstructedElement = TraitElement;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			
			return;
			
		}
		
		delete TraitElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for trait definition or parenthesis to close empty trait";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	TraitElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Error = false;
	ErrorString = "";
	ErrorToken = NULL;
	
	while ( TraitBodyConstructionGroup.TryConstruction ( TraitElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		if ( TokenCount == 0 )
		{
			
			delete TraitElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing curly bracket at end of trait body";
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
		
		delete TraitElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete TraitElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of trait body";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	TraitElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = TraitElement;
	
}

void OakTraitDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}

