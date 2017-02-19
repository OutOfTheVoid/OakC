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

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Parsing/Language/OakStructDefinitionConstructor.h>

OakNamespaceDefinitionConstructor OakNamespaceDefinitionConstructor :: Instance;

OakNamespaceDefinitionConstructor :: OakNamespaceDefinitionConstructor ():
	NamespaceChildrenGroup ()
{
	
	NamespaceChildrenGroup.AddConstructorCantidate ( & Instance, 0 );
	NamespaceChildrenGroup.AddConstructorCantidate ( & OakStructDefinitionConstructor :: Instance, 0 );
	NamespaceChildrenGroup.AddConstructorCantidate ( & OakTraitDefinitionConstructor :: Instance, 0 );
	NamespaceChildrenGroup.AddConstructorCantidate ( & OakBindingStatementConstructor :: Instance, 0 );
	NamespaceChildrenGroup.AddConstructorCantidate ( & OakConstStatementConstructor :: Instance, 0 );
	NamespaceChildrenGroup.AddConstructorCantidate ( & OakFunctionDefinitionConstructor :: Instance, 0 );
	NamespaceChildrenGroup.AddConstructorCantidate ( & OakImplementDefinitionConstructor :: Instance, 0 );
	
	// Just in case
	NamespaceChildrenGroup.AddConstructorCantidate ( & OakLoneSemicolonConstructor :: Instance, 1 );
	
}

OakNamespaceDefinitionConstructor :: ~OakNamespaceDefinitionConstructor ()
{
}

void OakNamespaceDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	uint64_t Offset = 0;
	
	std :: vector <std :: u32string> NamespaceChain;
	std :: u32string LastIdent;
	
	bool DirectGlobalReference = false;
	
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
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_DoubleColon )
	{
		
		DirectGlobalReference = true;
		
		Offset ++;
		
		CurrentToken = Input.Tokens [ Offset ];
		
	}
	
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
	
	NamespaceData -> DirectGlobalReference = DirectGlobalReference;
	
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
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
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