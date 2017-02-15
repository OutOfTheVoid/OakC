#ifndef LEXING_LANGUAGE_OAKKEYWORDS_H
#define LEXING_LANGUAGE_OAKKEYWORDS_H

namespace OakKeywords
{
	
	/// A list of all UTF8-encoded keywords in the Oak language
	
	const std :: string kKeyword_True ( u8"true" );
	const std :: string kKeyword_False ( u8"false" );
	
	const std :: string kKeyword_Null ( u8"null" );
	
	const std :: string kKeyword_Bool ( u8"bool" );
	const std :: string kKeyword_Int8 ( u8"i8" );
	const std :: string kKeyword_Int16 ( u8"i16" );
	const std :: string kKeyword_Int32 ( u8"i32" );
	const std :: string kKeyword_Int64 ( u8"i64" );
	const std :: string kKeyword_IntPtr ( u8"iptr" );
	const std :: string kKeyword_UInt8 ( u8"u8" );
	const std :: string kKeyword_UInt16 ( u8"u16" );
	const std :: string kKeyword_UInt32 ( u8"u32" );
	const std :: string kKeyword_UInt64 ( u8"u64" );
	const std :: string kKeyword_UIntPtr ( u8"uptr" );
	const std :: string kKeyword_Void ( u8"void" );
	const std :: string kKeyword_Char ( u8"char" );
	const std :: string kKeyword_Float32 ( u8"f32" );
	const std :: string kKeyword_Float64 ( u8"f64" );
	const std :: string kKeyword_String8 ( u8"string" );
	const std :: string kKeyword_String16 ( u8"string16" );
	const std :: string kKeyword_String32 ( u8"string32" );
	
	const std :: string kKeyword_Namespace ( u8"namespace" );
	const std :: string kKeyword_Import ( u8"import" );
	const std :: string kKeyword_Struct ( u8"struct" );
	const std :: string kKeyword_Trait ( u8"trait" );
	const std :: string kKeyword_Function ( u8"function" );
	const std :: string kKeyword_Return ( u8"return" );
	const std :: string kKeyword_Enum ( u8"enum" );
	const std :: string kKeyword_Ignore ( u8"ignore" );
	const std :: string kKeyword_Implement ( u8"implement" );
	const std :: string kKeyword_Self ( u8"self" );
	
	const std :: string kKeyword_Mut ( u8"mut" );
	const std :: string kKeyword_Public ( u8"public" );
	const std :: string kKeyword_Inline ( u8"inline" );
	
	const std :: string kKeyword_Init ( u8"init" );
	const std :: string kKeyword_Drop ( u8"drop" );
	
	const std :: string kKeyword_If ( u8"if" );
	const std :: string kKeyword_Else ( u8"else" );
	const std :: string kKeyword_While ( u8"while" );
	const std :: string kKeyword_Do ( u8"do" );
	const std :: string kKeyword_For ( u8"for" );
	const std :: string kKeyword_Match ( u8"match" );
	const std :: string kKeyword_Break ( u8"break" );
	
	const std :: string kKeyword_Bind ( u8"bind" );
	
}

#endif
