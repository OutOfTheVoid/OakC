#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Parsing/Language/OakTemplateSpecificationConstructor.h>

uint64_t _OakNamespacedTemplatedTypeNameConstructor_AllowedKeywordTagList [] =
{
	
	OakKeywordTokenTags :: kKeywordAuxTags_Ident,
	OakKeywordTokenTags :: kKeywordAuxTags_Bool,
	OakKeywordTokenTags :: kKeywordAuxTags_Int8,
	OakKeywordTokenTags :: kKeywordAuxTags_Int16,
	OakKeywordTokenTags :: kKeywordAuxTags_Int32,
	OakKeywordTokenTags :: kKeywordAuxTags_Int64,
	OakKeywordTokenTags :: kKeywordAuxTags_IntPtr,
	OakKeywordTokenTags :: kKeywordAuxTags_UInt8,
	OakKeywordTokenTags :: kKeywordAuxTags_UInt16,
	OakKeywordTokenTags :: kKeywordAuxTags_UInt32,
	OakKeywordTokenTags :: kKeywordAuxTags_UInt64,
	OakKeywordTokenTags :: kKeywordAuxTags_UIntPtr,
	OakKeywordTokenTags :: kKeywordAuxTags_Void,
	OakKeywordTokenTags :: kKeywordAuxTags_Char,
	OakKeywordTokenTags :: kKeywordAuxTags_Float32,
	OakKeywordTokenTags :: kKeywordAuxTags_Float64,
	OakKeywordTokenTags :: kKeywordAuxTags_String8,
	OakKeywordTokenTags :: kKeywordAuxTags_String16,
	OakKeywordTokenTags :: kKeywordAuxTags_String32
	
};

TestSet <uint64_t> OakNamespacedTemplatedTypeNameConstructor :: AllowedKeywordTags ( _OakNamespacedTemplatedTypeNameConstructor_AllowedKeywordTagList, 19, false );

OakTemplateSpecificationConstructor _OakNamespacedTemplatedTypeNameConstructor_OakTemplateSpecificationConstructorInstance;

OakNamespacedTemplatedTypeNameConstructor :: OakNamespacedTemplatedTypeNameConstructor ():
	TemplateGroup ()
{
	
	TemplateGroup.AddConstructorCantidate ( & _OakNamespacedTemplatedTypeNameConstructor_OakTemplateSpecificationConstructorInstance, 0 );
	
}

OakNamespacedTemplatedTypeNameConstructor :: ~OakNamespacedTemplatedTypeNameConstructor ()
{
}

void OakNamespacedTemplatedTypeNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Identifier )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ! AllowedKeywordTags.Contains ( CurrentToken -> GetAuxTag () ) )
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
	
	TypeNameData -> DirectGlobalReference = true;
	
	TypeNameData -> Name = LastIdent;
	
	TypeNameData -> IdentList = new std :: u32string [ NamespaceChain.size () ];
	TypeNameData -> IdentListLength = NamespaceChain.size ();
	
	for ( uint32_t I = 0; I < NamespaceChain.size (); I ++ )
		TypeNameData -> IdentList [ I ] = NamespaceChain [ I ];
	
	ASTElement * TypeNameElement = new ASTElement ();
	TypeNameElement -> SetTag ( OakASTTags :: kASTTag_TypeName_NamespacedTemplated );
	TypeNameElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	TypeNameElement -> SetData ( TypeNameData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TemplateGroup.TryConstruction ( TypeNameElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		ElementDataDestructor ( TypeNameData );
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		ElementDataDestructor ( TypeNameData );
		
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

void OakNamespacedTemplatedTypeNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	ElementData * EData = reinterpret_cast <ElementData *> ( Data );
	
	delete [] EData -> IdentList;
	EData -> IdentList = NULL;
	
	delete EData;
	
}
