#include <Parsing/Language/OakImplementDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakFunctionDefinitionConstructor.h>
#include <Parsing/Language/OakMethodDefinitionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakImplementDefinitionConstructor OakImplementDefinitionConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakImplementDefinitionConstructor_ImplementChildrenConstructionGroupEntries [] =
{
	
	{ & OakMethodDefinitionConstructor :: Instance, 0 },
	{ & OakFunctionDefinitionConstructor :: Instance, 1 }
	
};

OakImplementDefinitionConstructor :: OakImplementDefinitionConstructor ():
	ImplementChildrenConstructionGroup ( _OakImplementDefinitionConstructor_ImplementChildrenConstructionGroupEntries, 2 )
{
}

OakImplementDefinitionConstructor :: ~OakImplementDefinitionConstructor ()
{
}

void OakImplementDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Implement ) )
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
		Output.ErrorSuggestion = "Expected body after implement declaration";
		Output.ErrorProvokingToken = CurrentToken;
		
	}
	
	Offset ++;
	
	ElementData * ImplementData = new ElementData ();
	
	ImplementData -> DirectGlobalReference = DirectGlobalReference;
	
	ImplementData -> Name = LastIdent;
	
	ImplementData -> IdentList = new std :: u32string [ NamespaceChain.size () ];
	ImplementData -> IdentListLength = NamespaceChain.size ();
	
	for ( uint32_t I = 0; I < NamespaceChain.size (); I ++ )
		ImplementData -> IdentList [ I ] = NamespaceChain [ I ];
	
	ASTElement * ImplementElement = new ASTElement ();
	ImplementElement -> SetTag ( OakASTTags :: kASTTag_ImplementDefinition );
	ImplementElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	ImplementElement -> SetData ( ImplementData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	
	ImplementChildrenConstructionGroup.TryConstruction ( ImplementElement, 0xFFFFFFFFFFFFFFFF, Error, ErrorString, ErrorToken, & Input.Tokens [ Offset ], TokenCount );
	
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
		Output.ErrorSuggestion = "Expected closing curly brace at end of implement definition";
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
		Output.ErrorSuggestion = "Expected closing curly brace at end of implement definition";
		Output.ErrorProvokingToken = CurrentToken;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Offset;
	Output.ConstructedElement = ImplementElement;
	
}

void OakImplementDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * ImplementDefinitionInstance = reinterpret_cast <ElementData *> ( Data );
	
	if ( ImplementDefinitionInstance -> IdentList != NULL )
		delete [] ImplementDefinitionInstance -> IdentList;
	
	delete ImplementDefinitionInstance;
	
}