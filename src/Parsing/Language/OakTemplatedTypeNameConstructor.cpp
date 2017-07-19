#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Parsing/Language/OakTemplateSpecificationConstructor.h>

#include <Utils/GlobalSingleton.h>

OakTemplatedTypeNameConstructor & OakTemplatedTypeNameConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakTemplatedTypeNameConstructor> ();
	
}

uint64_t _OakTemplatedTypeNameConstructor_AllowedKeywordTagList [] =
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

TestSet <uint64_t> OakTemplatedTypeNameConstructor :: AllowedKeywordTags ( _OakTemplatedTypeNameConstructor_AllowedKeywordTagList, 19, false );

OakTemplatedTypeNameConstructor :: OakTemplatedTypeNameConstructor ():
	TemplateGroup ( { { & ( OakTemplateSpecificationConstructor :: Instance () ), 0 } } )
{
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
	
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Identifier )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ! AllowedKeywordTags.Contains ( CurrentToken -> GetAuxTag () & OakKeywordTokenTags :: kKeywordAuxTags_Mask_Meaning ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ElementData * TypeNameData = new ElementData ();
	
	TypeNameData -> TypeName = CurrentToken -> GetSource ();
	TypeNameData -> DoubleTemplateClose = false;
	TypeNameData -> TripleTemplateClose = false;
	
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
		
		delete TypeNameElement;
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete TypeNameElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	OakTemplateSpecificationConstructor :: ElementData * TemplateSpecData = reinterpret_cast <OakTemplateSpecificationConstructor :: ElementData *> ( TypeNameElement -> GetSubElement ( 0 ) -> GetData () );
	
	if ( TemplateSpecData -> DoubleTemplateClose )
		TypeNameData -> DoubleTemplateClose = true;
	
	if ( TemplateSpecData -> TripleTemplateClose )
		TypeNameData -> TripleTemplateClose = true;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = TypeNameElement;
	
}

void OakTemplatedTypeNameConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}