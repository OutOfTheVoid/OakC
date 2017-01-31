#include <Parsing/Language/OakRestrictedTemplateParameterConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Parsing/Language/OakBareTraitNameConstructor.h>

OakBareTraitNameConstructor _OakRestrictedTemplateParameterConstructor_BareTraitNameConstructorInstance;

OakRestrictedTemplateParameterConstructor :: OakRestrictedTemplateParameterConstructor ():
	RestrictionTraitGroup ()
{
	
	// TODO: Add templated, namespaced, and namespace templated trait name constructors.
	RestrictionTraitGroup.AddConstructorCantidate ( & _OakRestrictedTemplateParameterConstructor_BareTraitNameConstructorInstance, 1 );
	
}

OakRestrictedTemplateParameterConstructor :: ~OakRestrictedTemplateParameterConstructor ()
{	
}

void OakRestrictedTemplateParameterConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * ParameterData = new ElementData ();
	
	ParameterData -> Name = Input.Tokens [ 0 ] -> GetSource ();
	ParameterData -> DoubleTemplateClose = false;
	
	ASTElement * ParameterElement = new ASTElement ();
	ParameterElement -> SetTag ( OakASTTags :: kASTTag_RestrictedTemplateParameter );
	ParameterElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	ParameterElement -> SetData ( ParameterData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	while ( RestrictionTraitGroup.TryConstruction ( ParameterElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		ASTElement * RestrictionElement = ParameterElement -> GetSubElement ( ParameterElement -> GetSubElementCount () - 1 );
		
		// In the case that it's a templated, OR namespaced templated parameter, we need to figure out whether it was a double-closed one due to the >> problem.
		
		if ( TokenCount == 0 )
		{
			
			delete ParameterElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected trait for template restriction";
			Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ];
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Plus )
			break;
		
		TokenCount --;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ParameterElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected trait for template restriction";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.ConstructedElement = ParameterElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}

void OakRestrictedTemplateParameterConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
