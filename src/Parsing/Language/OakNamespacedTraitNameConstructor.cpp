#include <Parsing/Language/OakNamespacedTraitNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <vector>

OakNamespacedTraitNameConstructor OakNamespacedTraitNameConstructor :: Instance;

OakNamespacedTraitNameConstructor :: OakNamespacedTraitNameConstructor ()
{
}

OakNamespacedTraitNameConstructor :: ~OakNamespacedTraitNameConstructor ()
{
}

void OakNamespacedTraitNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	uint64_t Offset = 0;
	
	std :: vector <std :: u32string> NamespaceChain;
	std :: u32string LastIdent;
	
	bool DirectGlobalReference = false;
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
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
	
	if ( NamespaceChain.size () == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * TraitNameData = new ElementData ();
	
	TraitNameData -> DirectGlobalReference = DirectGlobalReference;
	TraitNameData -> Name = LastIdent;
	
	TraitNameData -> IdentList = new std :: u32string [ NamespaceChain.size () ];
	TraitNameData -> IdentListLength = NamespaceChain.size ();
	
	for ( uint32_t I = 0; I < NamespaceChain.size (); I ++ )
		TraitNameData -> IdentList [ I ] = NamespaceChain [ I ];
	
	ASTElement * TraitNameElement = new ASTElement ();
	TraitNameElement -> SetTag ( OakASTTags :: kASTTag_TraitName_Namespaced );
	TraitNameElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	TraitNameElement -> SetData ( TraitNameData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.TokensConsumed = Offset;
	Output.ConstructedElement = TraitNameElement;
	
}

void OakNamespacedTraitNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * EData = reinterpret_cast <ElementData *> ( Data );
	
	delete [] EData -> IdentList;
	EData -> IdentList = NULL;
	
	delete EData;
	
}
