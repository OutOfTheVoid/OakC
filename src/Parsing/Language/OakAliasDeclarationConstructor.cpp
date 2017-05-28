#include <Parsing/Language/OakAliasDeclarationConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakReferenceTypeConstructor.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakVoidTypeConstructor.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>
#include <Encoding/CodeConversion.h>

OakAliasDeclarationConstructor OakAliasDeclarationConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakAliasDeclarationConstructor_TypeGroupEntries [] =
{
	
	{ & OakReferenceTypeConstructor :: Instance, 0 },
	{ & OakVoidTypeConstructor :: Instance, 0 },
	
	{ & OakNamespacedTemplatedTypeNameConstructor :: Instance, 0 },
	{ & OakNamespacedTypeNameConstructor :: Instance, 1 },
	{ & OakTemplatedTypeNameConstructor :: Instance, 1 },
	{ & OakBareTypeNameConstructor :: Instance, 2 },
	
};

ASTConstructionGroup :: StaticInitEntry _OakAliasDeclarationConstructor_TemplateGroupEntries [] =
{
	
	{ & OakTemplateDefinitionConstructor :: Instance, 0 },
	
};

OakAliasDeclarationConstructor :: OakAliasDeclarationConstructor ():
	TemplateGroup ( _OakAliasDeclarationConstructor_TemplateGroupEntries, 1 ),
	TypeGroup ( _OakAliasDeclarationConstructor_TypeGroupEntries, 6 )
{
}

OakAliasDeclarationConstructor :: ~OakAliasDeclarationConstructor ()
{
}

void OakAliasDeclarationConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Alias ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	ElementData * AliasData = new ElementData ();
	AliasData -> Templated = false;
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		delete AliasData;
		
		Output.Accepted = false;
		return;
		
	}
	
	AliasData -> NewName = CurrentToken -> GetSource ();
	
	ASTElement * AliasElement = new ASTElement ();
	
	AliasElement -> SetTag ( OakASTTags :: kASTTag_TypeAlias );
	AliasElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	AliasElement -> SetData ( AliasData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TemplateGroup.TryConstruction ( AliasElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		if ( ConstructionError )
		{
			
			delete AliasElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		AliasData -> Templated = true;
		
	}
	else if ( ConstructionError )
	{
		
		delete AliasElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TypeGroup.TryConstruction ( AliasElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( ConstructionError )
		{
			
			delete AliasElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
	}
	
	if ( ConstructionError )
	{
		
		delete AliasElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete AliasElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of alias statement";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		LOG ( std :: string ( "NON-SEMICOLON: " ) + CodeConversion :: ConvertUTF32ToUTF8 ( CurrentToken -> GetSource () ) );
		
		delete AliasElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon at end of alias statement";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	AliasElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.ConstructedElement = AliasElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}

void OakAliasDeclarationConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}

