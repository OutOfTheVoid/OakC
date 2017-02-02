#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <vector>

OakNamespacedTypeNameConstructor :: OakNamespacedTypeNameConstructor ()
{
}

OakNamespacedTypeNameConstructor :: ~OakNamespacedTypeNameConstructor ()
{
}

void OakNamespacedTypeNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	ElementData * TypeNameData = new ElementData ();
	
	TypeNameData -> DirectGlobalReference = DirectGlobalReference;
	
	TypeNameData -> Name = LastIdent;
	
	TypeNameData -> IdentList = new std :: u32string [ NamespaceChain.size () ];
	TypeNameData -> IdentListLength = NamespaceChain.size ();
	
	for ( uint32_t I = 0; I < NamespaceChain.size (); I ++ )
		TypeNameData -> IdentList [ I ] = NamespaceChain [ I ];
	
	ASTElement * TypeNameElement = new ASTElement ();
	TypeNameElement -> SetTag ( OakASTTags :: kASTTag_TypeName_Namespaced );
	TypeNameElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	TypeNameElement -> SetData ( TypeNameData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.TokensConsumed = Offset;
	Output.ConstructedElement = TypeNameElement;
	
}

void OakNamespacedTypeNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * EData = reinterpret_cast <ElementData *> ( Data );
	
	delete [] EData -> IdentList;
	EData -> IdentList = NULL;
	
	delete EData;
	
}
