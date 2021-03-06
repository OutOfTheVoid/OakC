#include <Parsing/Language/OakNamespaceDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakStructBindingConstructor.h>
#include <Parsing/Language/OakTraitDefinitionConstructor.h>
#include <Parsing/Language/OakImplementDefinitionConstructor.h>
#include <Parsing/Language/OakBindingStatementConstructor.h>
#include <Parsing/Language/OakConstStatementConstructor.h>
#include <Parsing/Language/OakLoneSemicolonConstructor.h>
#include <Parsing/Language/OakFunctionDefinitionConstructor.h>
#include <Parsing/Language/OakDecoratorTagConstructor.h>
#include <Parsing/Language/OakAliasDeclarationConstructor.h>
#include <Parsing/Language/OakEnumConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Parsing/Language/OakStructDefinitionConstructor.h>

#include <Utils/GlobalSingleton.h>

OakNamespaceDefinitionConstructor & OakNamespaceDefinitionConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakNamespaceDefinitionConstructor> ();
	
}

OakNamespaceDefinitionConstructor :: OakNamespaceDefinitionConstructor ():
	NamespaceChildrenGroup ( 
	{
		
		{ & ( OakNamespaceDefinitionConstructor :: Instance () ), 0 },
		{ & ( OakAliasDeclarationConstructor :: Instance () ), 0 },
		{ & ( OakStructDefinitionConstructor :: Instance () ), 0 },
		{ & ( OakTraitDefinitionConstructor :: Instance () ), 0 },
		{ & ( OakBindingStatementConstructor :: Instance () ), 0 },
		{ & ( OakConstStatementConstructor :: Instance () ), 0 },
		{ & ( OakFunctionDefinitionConstructor :: Instance () ), 0 },
		{ & ( OakImplementDefinitionConstructor :: Instance () ), 0 },
		{ & ( OakDecoratorTagConstructor :: Instance () ), 0 },
		{ & ( OakEnumConstructor :: Instance () ), 0 },
		
		{ & ( OakLoneSemicolonConstructor :: Instance () ), 1 },
		
	} )
{
}

OakNamespaceDefinitionConstructor :: ~OakNamespaceDefinitionConstructor ()
{
}

void OakNamespaceDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	uint64_t Offset = 0;
	
	std :: vector <std :: u32string> NamespaceChain;
	std :: u32string LastIdent;
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Namespace ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Offset ++;
	CurrentToken = Input.Tokens [ Offset ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	LastIdent = CurrentToken -> GetSource ();
	Offset ++;
	
	while ( ( Offset + 1 ) < Input.AvailableTokenCount )
	{
		
		CurrentToken = Input.Tokens [ Offset ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_DoubleColon )
			break;
		
		NamespaceChain.push_back ( LastIdent );
		Offset ++;
		
		CurrentToken = Input.Tokens [ Offset ];
		
		if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected identifier after namespace access operator";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		LastIdent = CurrentToken -> GetSource ();
		
		Offset ++;
		
	}
	
	CurrentToken = Input.Tokens [ Offset ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body after namespace declaration";
		Output.ErrorProvokingToken = CurrentToken;
		
	}
	
	Offset ++;
	
	ElementData * NamespaceData = new ElementData ();
	
	NamespaceData -> DirectGlobalReference = NamespaceChain.size () == 0;
	
	NamespaceData -> Name = LastIdent;
	
	NamespaceData -> IdentList = new std :: u32string [ NamespaceChain.size () ];
	NamespaceData -> IdentListLength = NamespaceChain.size ();
	
	for ( uint32_t I = 0; I < NamespaceChain.size (); I ++ )
		NamespaceData -> IdentList [ I ] = NamespaceChain [ I ];
	
	ASTElement * NamespaceElement = new ASTElement ();
	NamespaceElement -> SetTag ( OakASTTags :: kASTTag_NamespaceDefinition );
	NamespaceElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	NamespaceElement -> SetData ( NamespaceData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	
	NamespaceChildrenGroup.TryConstruction ( NamespaceElement, 0xFFFFFFFFFFFFFFFF, Error, ErrorString, ErrorToken, & Input.Tokens [ Offset ], TokenCount );
	
	if ( Error )
	{
		
		delete NamespaceElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete NamespaceElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly brace at end of namespace definition";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - 1 ];
		
		return;
		
	}
	
	Offset = Input.AvailableTokenCount - TokenCount;
	
	CurrentToken = Input.Tokens [ Offset ];
	Offset ++;
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete NamespaceElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly brace at end of namespace definition";
		Output.ErrorProvokingToken = CurrentToken;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Offset;
	Output.ConstructedElement = NamespaceElement;
	
}

void OakNamespaceDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * EData = reinterpret_cast <ElementData *> ( Data );
	
	delete [] EData -> IdentList;
	EData -> IdentList = NULL;
	
	delete EData;
	
}