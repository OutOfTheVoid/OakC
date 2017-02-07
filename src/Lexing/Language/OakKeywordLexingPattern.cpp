#include <Lexing/Language/OakKeywordLexingPattern.h>
#include <Lexing/Language/OakKeywordTokenTags.h>
#include <Lexing/Language/OakKeywords.h>

#include <Tokenization/Language/OakTokenTags.h>
#include <Tokenization/Token.h>

#include <Encoding/CodeConversion.h>

#include <Logging/Logging.h>

OakKeywordLexingPattern :: OakKeywordLexingPattern ():
	KeywordAuxTags ( OakKeywordTokenTags :: kKeywordAuxTags_Ident )
{
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_True.c_str (), OakKeywords :: kKeyword_True.size (), OakKeywordTokenTags :: kKeywordAuxTags_True );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_False.c_str (), OakKeywords :: kKeyword_False.size (), OakKeywordTokenTags :: kKeywordAuxTags_False );
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Null.c_str (), OakKeywords :: kKeyword_Null.size (), OakKeywordTokenTags :: kKeywordAuxTags_Null );
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Bool.c_str (), OakKeywords :: kKeyword_Bool.size (), OakKeywordTokenTags :: kKeywordAuxTags_Bool );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Int8.c_str (), OakKeywords :: kKeyword_Int8.size (), OakKeywordTokenTags :: kKeywordAuxTags_Int8 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Int16.c_str (), OakKeywords :: kKeyword_Int16.size (), OakKeywordTokenTags :: kKeywordAuxTags_Int16 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Int32.c_str (), OakKeywords :: kKeyword_Int32.size (), OakKeywordTokenTags :: kKeywordAuxTags_Int32 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Int64.c_str (), OakKeywords :: kKeyword_Int64.size (), OakKeywordTokenTags :: kKeywordAuxTags_Int64 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_IntPtr.c_str (), OakKeywords :: kKeyword_IntPtr.size (), OakKeywordTokenTags :: kKeywordAuxTags_IntPtr );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_UInt8.c_str (), OakKeywords :: kKeyword_UInt8.size (), OakKeywordTokenTags :: kKeywordAuxTags_UInt8 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_UInt16.c_str (), OakKeywords :: kKeyword_UInt16.size (), OakKeywordTokenTags :: kKeywordAuxTags_UInt16 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_UInt32.c_str (), OakKeywords :: kKeyword_UInt32.size (), OakKeywordTokenTags :: kKeywordAuxTags_UInt32 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_UInt64.c_str (), OakKeywords :: kKeyword_UInt64.size (), OakKeywordTokenTags :: kKeywordAuxTags_UInt64 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_UIntPtr.c_str (), OakKeywords :: kKeyword_UIntPtr.size (), OakKeywordTokenTags :: kKeywordAuxTags_UIntPtr );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Void.c_str (), OakKeywords :: kKeyword_Void.size (), OakKeywordTokenTags :: kKeywordAuxTags_Void );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Char.c_str (), OakKeywords :: kKeyword_Char.size (), OakKeywordTokenTags :: kKeywordAuxTags_Char );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Float32.c_str (), OakKeywords :: kKeyword_Float32.size (), OakKeywordTokenTags :: kKeywordAuxTags_Float32 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Float64.c_str (), OakKeywords :: kKeyword_Float64.size (), OakKeywordTokenTags :: kKeywordAuxTags_Float64 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_String8.c_str (), OakKeywords :: kKeyword_String8.size (), OakKeywordTokenTags :: kKeywordAuxTags_String8 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_String16.c_str (), OakKeywords :: kKeyword_String16.size (), OakKeywordTokenTags :: kKeywordAuxTags_String16 );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_String32.c_str (), OakKeywords :: kKeyword_String32.size (), OakKeywordTokenTags :: kKeywordAuxTags_String32 );
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Namespace.c_str (), OakKeywords :: kKeyword_Namespace.size (), OakKeywordTokenTags :: kKeywordAuxTags_Namespace );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Import.c_str (), OakKeywords :: kKeyword_Import.size (), OakKeywordTokenTags :: kKeywordAuxTags_Import );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Struct.c_str (), OakKeywords :: kKeyword_Struct.size (), OakKeywordTokenTags :: kKeywordAuxTags_Struct );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Trait.c_str (), OakKeywords :: kKeyword_Trait.size (), OakKeywordTokenTags :: kKeywordAuxTags_Trait );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Function.c_str (), OakKeywords :: kKeyword_Function.size (), OakKeywordTokenTags :: kKeywordAuxTags_Function );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Return.c_str (), OakKeywords :: kKeyword_Return.size (), OakKeywordTokenTags :: kKeywordAuxTags_Return );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Enum.c_str (), OakKeywords :: kKeyword_Enum.size (), OakKeywordTokenTags :: kKeywordAuxTags_Enum );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Ignore.c_str (), OakKeywords :: kKeyword_Ignore.size (), OakKeywordTokenTags :: kKeywordAuxTags_Ignore );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Implement.c_str (), OakKeywords :: kKeyword_Implement.size (), OakKeywordTokenTags :: kKeywordAuxTags_Implement );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Self.c_str (), OakKeywords :: kKeyword_Self.size (), OakKeywordTokenTags :: kKeywordAuxTags_Self );
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Mut.c_str (), OakKeywords :: kKeyword_Mut.size (), OakKeywordTokenTags :: kKeywordAuxTags_Mut );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Public.c_str (), OakKeywords :: kKeyword_Public.size (), OakKeywordTokenTags :: kKeywordAuxTags_Public );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Inline.c_str (), OakKeywords :: kKeyword_Inline.size (), OakKeywordTokenTags :: kKeywordAuxTags_Inline );
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_New.c_str (), OakKeywords :: kKeyword_New.size (), OakKeywordTokenTags :: kKeywordAuxTags_New );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Delete.c_str (), OakKeywords :: kKeyword_Delete.size (), OakKeywordTokenTags :: kKeywordAuxTags_Delete );
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Init.c_str (), OakKeywords :: kKeyword_Init.size (), OakKeywordTokenTags :: kKeywordAuxTags_Init );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Drop.c_str (), OakKeywords :: kKeyword_Drop.size (), OakKeywordTokenTags :: kKeywordAuxTags_Drop );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_If.c_str (), OakKeywords :: kKeyword_If.size (), OakKeywordTokenTags :: kKeywordAuxTags_If );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_While.c_str (), OakKeywords :: kKeyword_While.size (), OakKeywordTokenTags :: kKeywordAuxTags_While );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Do.c_str (), OakKeywords :: kKeyword_Do.size (), OakKeywordTokenTags :: kKeywordAuxTags_Do );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_For.c_str (), OakKeywords :: kKeyword_For.size (), OakKeywordTokenTags :: kKeywordAuxTags_For );
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Match.c_str (), OakKeywords :: kKeyword_Match.size (), OakKeywordTokenTags :: kKeywordAuxTags_Match );
	
	KeywordAuxTags.Set ( OakKeywords :: kKeyword_Bind.c_str (), OakKeywords :: kKeyword_Bind.size (), OakKeywordTokenTags :: kKeywordAuxTags_Bind );
	
}

OakKeywordLexingPattern :: ~OakKeywordLexingPattern ()
{
}

void OakKeywordLexingPattern :: TryPattern ( ILexingInput & Input, ILexingResult & Result )
{
	
	if ( Input.AvailableTokens == 0 )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	const Token * Current = Input.Tokens [ 0 ];
	
	if ( Current -> GetTag () != OakTokenTags :: kTokenTag_Identifier )
	{
		
		Result.Accepted = false;
		
		return;
		
	}
	
	std :: string SourceUTF8 = CodeConversion :: ConvertUTF32ToUTF8 ( Current -> GetSource () );
	uint64_t AuxTag = KeywordAuxTags.Get ( SourceUTF8.c_str (), SourceUTF8.size () );
	
	Result.Accepted = true;
	Result.TokenOutput.push_back ( new Token ( Current -> GetSource (), Current -> GetChar (), Current -> GetLine (), OakTokenTags :: kTokenTag_Identifier, AuxTag ) );
	Result.TokensConsumed = 1;
	
}

