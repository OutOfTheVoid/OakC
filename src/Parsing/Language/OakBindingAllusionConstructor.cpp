#include <Parsing/Language/OakBindingAllusionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <vector>

#ifndef NULL
	#define NULL nullptr
#endif

OakBindingAllusionConstructor OakBindingAllusionConstructor :: Instance;

OakBindingAllusionConstructor :: OakBindingAllusionConstructor ()
{
}

OakBindingAllusionConstructor :: ~OakBindingAllusionConstructor ()
{
}

void OakBindingAllusionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	uint64_t Offset = 0;
	
	std :: vector <std :: u32string> NamespaceChain;
	std :: u32string LastIdent;
	
	bool DirectGlobalReference = false;
	
	if ( Input.AvailableTokenCount < 1 )
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
	
	ElementData * AllusionData = new ElementData ();
	
	AllusionData -> DirectGlobalReference = DirectGlobalReference;
	
	AllusionData -> Name = LastIdent;
	AllusionData -> IdentListLength = NamespaceChain.size ();
	
	if ( NamespaceChain.size () != 0 )
	{
		
		AllusionData -> IdentList = new std :: u32string [ NamespaceChain.size () ];
		
		for ( uint32_t I = 0; I < NamespaceChain.size (); I ++ )
			AllusionData -> IdentList [ I ] = NamespaceChain [ I ];
		
	}
	else
		AllusionData -> IdentList = NULL;
	
	ASTElement * AllusionElement = new ASTElement ();
	AllusionElement -> SetTag ( OakASTTags :: kASTTag_BindingAllusion );
	AllusionElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	AllusionElement -> SetData ( AllusionData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.TokensConsumed = Offset;
	Output.ConstructedElement = AllusionElement;
	
}

void OakBindingAllusionConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * EData = reinterpret_cast <ElementData *> ( Data );
	
	if ( EData -> IdentList != NULL )
		delete EData -> IdentList;
	
	delete EData;
	
}

