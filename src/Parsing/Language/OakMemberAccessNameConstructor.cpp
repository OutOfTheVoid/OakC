#include <Parsing/Language/OakMemberAccessNameConstructor.h>

#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Parsing/Language/OakTemplateSpecificationConstructor.h>

#include <Utils/GlobalSingleton.h>

OakMemberAccessNameConstructor & OakMemberAccessNameConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakMemberAccessNameConstructor> ();
	
}

OakMemberAccessNameConstructor :: OakMemberAccessNameConstructor ():
	TemplateGroup ( { { & ( OakTemplateSpecificationConstructor :: Instance () ), 0 } } )
{
}

OakMemberAccessNameConstructor :: ~OakMemberAccessNameConstructor ()
{
}

void OakMemberAccessNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 1 )
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
	
	ElementData * NameData = new ElementData ();
	
	NameData -> Templated = false;
	NameData -> Name = Input.Tokens [ 0 ] -> GetSource ();
	
	ASTElement * NameElement = new ASTElement ();
	
	NameElement -> SetTag ( OakASTTags :: kASTTag_MemberAccessName );
	NameElement -> SetData ( NameData, & ElementDataDestructor );
	
	if ( Input.AvailableTokenCount == 1 )
	{
		
		Output.Accepted = true;
		Output.TokensConsumed = 1;
		Output.ConstructedElement = NameElement;
		
	}
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TemplateGroup.TryConstruction ( NameElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		Output.Accepted = true;
		Output.TokensConsumed = 1;
		Output.ConstructedElement = NameElement;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete NameElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	NameData -> Templated = true;
	
	OakTemplateSpecificationConstructor :: ElementData * TemplateSpecData = reinterpret_cast <OakTemplateSpecificationConstructor :: ElementData *> ( NameElement -> GetSubElement ( 0 ) -> GetData () );
	
	if ( TemplateSpecData -> DoubleTemplateClose || TemplateSpecData -> TripleTemplateClose )
	{
		
		delete NameElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Unexpected closing triangle bracket after end of template";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ];
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = NameElement;
	
}

void OakMemberAccessNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
