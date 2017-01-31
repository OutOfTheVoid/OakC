#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Parsing/Language/OakTemplateSpecificationConstructor.h>

OakTemplateSpecificationConstructor _OakTemplatedTypeNameConstructor_OakTemplateSpecificationConstructorInstance;

OakTemplatedTypeNameConstructor :: OakTemplatedTypeNameConstructor ():
	TemplateGroup ()
{
	
	TemplateGroup.AddConstructorCantidate ( & _OakTemplatedTypeNameConstructor_OakTemplateSpecificationConstructorInstance, 0 );
	
}

OakTemplatedTypeNameConstructor :: ~OakTemplatedTypeNameConstructor ()
{
}

void OakTemplatedTypeNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	ElementData * TypeNameData = new ElementData ();
	
	TypeNameData -> Name = CurrentToken -> GetSource ();
	TypeNameData -> DoubleTemplateClose = false;
	
	ASTElement * TypeNameElement = new ASTElement ();
	TypeNameElement -> SetTag ( OakASTTags :: kASTTag_TypeName_Templated );
	TypeNameElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	TypeNameElement -> SetData ( TypeNameData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TemplateGroup.TryConstruction ( TypeNameElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete TypeNameData;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete TypeNameData;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	OakTemplateSpecificationConstructor :: ElementData * TemplateSpecData = reinterpret_cast <OakTemplateSpecificationConstructor :: ElementData *> ( TypeNameElement -> GetSubElement ( 0 ) -> GetData () );
	
	if ( TemplateSpecData -> DoubleTemplateClose )
		TypeNameData -> DoubleTemplateClose = true;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = TypeNameElement;
	
}

void OakTemplatedTypeNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}