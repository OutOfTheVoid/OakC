#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>
#include <Tokenization/Token.h>

uint64_t AllowedKeywordTagList [] =
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

TestSet <uint64_t> OakBareTypeNameConstructor :: AllowedKeywordTags ( AllowedKeywordTagList, 19, false );

OakBareTypeNameConstructor :: OakBareTypeNameConstructor ()
{	
}

OakBareTypeNameConstructor :: ~OakBareTypeNameConstructor ()
{
}

void OakBareTypeNameConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 1 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
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
	
	ElementData * BareTypeNameData = new ElementData ();
	
	BareTypeNameData -> TypeName = CurrentToken -> GetSource ();
	BareTypeNameData -> TypeTag = CurrentToken -> GetTag ();
	
	ASTElement * BareTypeNameElement = new ASTElement ();
	
	BareTypeNameElement -> SetTag ( OakASTTags :: kASTTag_BareTypeName );
	BareTypeNameElement -> SetData ( BareTypeNameData, & ElementDataDestructor );
	BareTypeNameElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	Output.Accepted = true;
	Output.TokensConsumed = 1;
	Output.ConstructedElement = BareTypeNameElement;
	
}

void OakBareTypeNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
