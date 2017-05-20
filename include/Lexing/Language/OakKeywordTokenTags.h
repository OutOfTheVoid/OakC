#ifndef LEXING_LANGUAGE_OAKKEYWORDTOKENTAGS_H
#define LEXING_LANGUAGE_OAKKEYWORDTOKENTAGS_H

namespace OakKeywordTokenTags
{
	
	/// A list of auxialiary tags for keywords, as well as the Ident tag, which is equivalent to ITokenSplitRule :: kAuxTag_Default
	
	const uint64_t kKeywordAuxTags_Ident = 0;
	
	const uint64_t kKeywordAuxTags_True = 1;
	const uint64_t kKeywordAuxTags_False = 2;
	const uint64_t kKeywordAuxTags_Null = 3;
	
	const uint64_t kKeywordAuxTags_Bool = 4;
	const uint64_t kKeywordAuxTags_Int8 = 5;
	const uint64_t kKeywordAuxTags_Int16 = 6;
	const uint64_t kKeywordAuxTags_Int32 = 7;
	const uint64_t kKeywordAuxTags_Int64 = 8;
	const uint64_t kKeywordAuxTags_IntPtr = 9;
	const uint64_t kKeywordAuxTags_UInt8 = 10;
	const uint64_t kKeywordAuxTags_UInt16 = 11;
	const uint64_t kKeywordAuxTags_UInt32 = 12;
	const uint64_t kKeywordAuxTags_UInt64 = 13;
	const uint64_t kKeywordAuxTags_UIntPtr = 14;
	const uint64_t kKeywordAuxTags_Void = 15;
	const uint64_t kKeywordAuxTags_Char = 16;
	const uint64_t kKeywordAuxTags_Float32 = 17;
	const uint64_t kKeywordAuxTags_Float64 = 18;
	const uint64_t kKeywordAuxTags_String8 = 19;
	const uint64_t kKeywordAuxTags_String16 = 20;
	const uint64_t kKeywordAuxTags_String32 = 21;
	
	const uint64_t kKeywordAuxTags_Namespace = 22;
	const uint64_t kKeywordAuxTags_Import = 23;
	const uint64_t kKeywordAuxTags_Struct = 24;
	const uint64_t kKeywordAuxTags_Trait = 25;
	const uint64_t kKeywordAuxTags_Function = 26;
	const uint64_t kKeywordAuxTags_Return = 27;
	const uint64_t kKeywordAuxTags_Enum = 28;
	const uint64_t kKeywordAuxTags_Ignore = 29;
	const uint64_t kKeywordAuxTags_Mut = 30;
	const uint64_t kKeywordAuxTags_Public = 31;
	const uint64_t kKeywordAuxTags_New = 32;
	const uint64_t kKeywordAuxTags_Delete = 33;
	const uint64_t kKeywordAuxTags_Init = 34;
	const uint64_t kKeywordAuxTags_Drop = 35;
	const uint64_t kKeywordAuxTags_If = 36;
	const uint64_t kKeywordAuxTags_Else = 37;
	const uint64_t kKeywordAuxTags_While = 38;
	const uint64_t kKeywordAuxTags_Do = 39;
	const uint64_t kKeywordAuxTags_For = 40;
	const uint64_t kKeywordAuxTags_Match = 41;
	const uint64_t kKeywordAuxTags_Bind = 42;
	const uint64_t kKeywordAuxTags_Implement = 43;
	const uint64_t kKeywordAuxTags_Self = 44;
	const uint64_t kKeywordAuxTags_Inline = 45;
	const uint64_t kKeywordAuxTags_Break = 46;
	const uint64_t kKeywordAuxTags_Loop = 47;
	const uint64_t kKeywordAuxTags_Const = 48;
	const uint64_t kKeywordAuxTags_Require = 49;
	const uint64_t kKeywordAuxTags_Where = 50;
	
	const uint64_t kKeywordAuxTags_Mask_Meaning = 0xFFF;
	
	const uint64_t kKeywordAuxTags_Mask_Localization = 0xFFFFF000;
	const uint64_t kKeywordAuxTags_Shift_Localization = 12;
	
	const uint64_t kKeywordAuxTags_Localization_EN = 0x00000;
	const uint64_t kKeywordAuxTags_Localization_FR = 0x00001;
	
	/// A list of the human-readable forms of kewords.
	const char * const KeywordAuxTagNames [] =
	{
		
		"IDENT",
		"TRUE",
		"FALSE",
		"NULL",
		"BOOL",
		"INT_8",
		"INT_16",
		"INT_32",
		"INT_64",
		"INT_PTR",
		"UINT_8",
		"UINT_16",
		"UINT_32",
		"UINT_64",
		"UINT_PTR",
		"VOID",
		"CHAR",
		"FLOAT_32",
		"FLOAT_64",
		"STRING_8",
		"STRING_16",
		"STRING_32",
		"NAMESPACE",
		"IMPORT",
		"STRUCT",
		"TRAIT",
		"FUNCTION",
		"RETURN",
		"ENUM",
		"IGNORE",
		"MUT",
		"PUBLIC",
		"NEW",
		"DELETE",
		"INIT",
		"DROP",
		"IF",
		"ELSE",
		"WHILE",
		"DO",
		"FOR",
		"MATCH",
		"BIND",
		"IMPLEMENT",
		"SELF",
		"INLINE",
		"BREAK",
		"LOOP",
		"CONST",
		"REQUIRE"
		
	};
	
}

#endif
