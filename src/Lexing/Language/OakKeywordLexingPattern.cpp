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
	
	AddLocalization ( OakKeywords :: kKeywordLocalization_EN, OakKeywordTokenTags :: kKeywordAuxTags_Localization_EN, true );
	AddLocalization ( OakKeywords :: kKeywordLocalization_FR, OakKeywordTokenTags :: kKeywordAuxTags_Localization_FR, false );
	
}

OakKeywordLexingPattern :: ~OakKeywordLexingPattern ()
{
}

void OakKeywordLexingPattern :: AddLocalization ( const OakKeywords :: KeywordLocalization & Localization, uint64_t LocalizationIndex, bool Overwrite )
{
	
	KeywordAuxTags.Set ( Localization.True.c_str (), Localization.True.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_True, Overwrite );
	KeywordAuxTags.Set ( Localization.False.c_str (), Localization.False.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_False, Overwrite );
	
	KeywordAuxTags.Set ( Localization.Null.c_str (), Localization.Null.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Null, Overwrite );
	
	KeywordAuxTags.Set ( Localization.Bool.c_str (), Localization.Bool.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Bool, Overwrite );
	KeywordAuxTags.Set ( Localization.I8.c_str (), Localization.I8.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Int8, Overwrite );
	KeywordAuxTags.Set ( Localization.I16.c_str (), Localization.I16.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Int16, Overwrite );
	KeywordAuxTags.Set ( Localization.I32.c_str (), Localization.I32.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Int32, Overwrite );
	KeywordAuxTags.Set ( Localization.I64.c_str (), Localization.I64.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Int64, Overwrite );
	KeywordAuxTags.Set ( Localization.IPtr.c_str (), Localization.IPtr.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_IntPtr, Overwrite );
	KeywordAuxTags.Set ( Localization.U8.c_str (), Localization.U8.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_UInt8, Overwrite );
	KeywordAuxTags.Set ( Localization.U16.c_str (), Localization.U16.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_UInt16, Overwrite );
	KeywordAuxTags.Set ( Localization.U32.c_str (), Localization.U32.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_UInt32, Overwrite );
	KeywordAuxTags.Set ( Localization.U64.c_str (), Localization.U64.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_UInt64, Overwrite );
	KeywordAuxTags.Set ( Localization.UPtr.c_str (), Localization.UPtr.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_UIntPtr, Overwrite );
	KeywordAuxTags.Set ( Localization.Void.c_str (), Localization.Void.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Void, Overwrite );
	KeywordAuxTags.Set ( Localization.Char.c_str (), Localization.Char.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Char, Overwrite );
	KeywordAuxTags.Set ( Localization.F32.c_str (), Localization.F32.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Float32, Overwrite );
	KeywordAuxTags.Set ( Localization.F64.c_str (), Localization.F64.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Float64, Overwrite );
	KeywordAuxTags.Set ( Localization.Str8.c_str (), Localization.Str8.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_String8, Overwrite );
	KeywordAuxTags.Set ( Localization.Str16.c_str (), Localization.Str16.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_String16, Overwrite );
	KeywordAuxTags.Set ( Localization.Str32.c_str (), Localization.Str32.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_String32, Overwrite );
	
	KeywordAuxTags.Set ( Localization.Namespace.c_str (), Localization.Namespace.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Namespace, Overwrite );
	KeywordAuxTags.Set ( Localization.Import.c_str (), Localization.Import.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Import, Overwrite );
	KeywordAuxTags.Set ( Localization.Struct.c_str (), Localization.Struct.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Struct, Overwrite );
	KeywordAuxTags.Set ( Localization.Trait.c_str (), Localization.Trait.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Trait, Overwrite );
	KeywordAuxTags.Set ( Localization.Function.c_str (), Localization.Function.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Function, Overwrite );
	KeywordAuxTags.Set ( Localization.Return.c_str (), Localization.Return.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Return, Overwrite );
	KeywordAuxTags.Set ( Localization.Enum.c_str (), Localization.Enum.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Enum, Overwrite );
	KeywordAuxTags.Set ( Localization.Ignore.c_str (), Localization.Ignore.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Ignore, Overwrite );
	KeywordAuxTags.Set ( Localization.Implement.c_str (), Localization.Implement.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Implement, Overwrite );
	KeywordAuxTags.Set ( Localization.Self.c_str (), Localization.Self.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Self, Overwrite );
	
	KeywordAuxTags.Set ( Localization.Mut.c_str (), Localization.Mut.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Mut, Overwrite );
	KeywordAuxTags.Set ( Localization.Public.c_str (), Localization.Public.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Public, Overwrite );
	KeywordAuxTags.Set ( Localization.Inline.c_str (), Localization.Inline.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Inline, Overwrite );
	
	KeywordAuxTags.Set ( Localization.Init.c_str (), Localization.Init.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Init, Overwrite );
	KeywordAuxTags.Set ( Localization.Drop.c_str (), Localization.Drop.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Drop, Overwrite );
	KeywordAuxTags.Set ( Localization.If.c_str (), Localization.If.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_If, Overwrite );
	KeywordAuxTags.Set ( Localization.Else.c_str (), Localization.Else.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Else, Overwrite );
	KeywordAuxTags.Set ( Localization.While.c_str (), Localization.While.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_While, Overwrite );
	KeywordAuxTags.Set ( Localization.Do.c_str (), Localization.Do.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Do, Overwrite );
	KeywordAuxTags.Set ( Localization.For.c_str (), Localization.For.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_For, Overwrite );
	KeywordAuxTags.Set ( Localization.Match.c_str (), Localization.Match.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Match, Overwrite );
	KeywordAuxTags.Set ( Localization.Break.c_str (), Localization.Break.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Break, Overwrite );
	KeywordAuxTags.Set ( Localization.Loop.c_str (), Localization.Loop.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Loop, Overwrite );
	
	KeywordAuxTags.Set ( Localization.Bind.c_str (), Localization.Bind.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Bind, Overwrite );
	KeywordAuxTags.Set ( Localization.Const.c_str (), Localization.Const.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Const, Overwrite );
	
	KeywordAuxTags.Set ( Localization.Require.c_str (), Localization.Require.size (), ( LocalizationIndex << OakKeywordTokenTags :: kKeywordAuxTags_Shift_Localization ) | OakKeywordTokenTags :: kKeywordAuxTags_Require, Overwrite );
	
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
	Result.TokenOutput.push_back ( new Token ( Current -> GetSource (), Current -> GetChar (), Current -> GetLine (), OakTokenTags :: kTokenTag_Identifier, AuxTag, Current -> GetSourceUnit () ) );
	Result.TokensConsumed = 1;
	
}

