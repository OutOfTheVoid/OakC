#ifndef LEXING_LANGUAGE_OAKKEYWORDS_H
#define LEXING_LANGUAGE_OAKKEYWORDS_H

namespace OakKeywords
{
	
	typedef struct
	{
		
		std :: string True;
		std :: string False;
		
		std :: string Null;
		
		std :: string Bool;
		std :: string I8;
		std :: string I16;
		std :: string I32;
		std :: string I64;
		std :: string IPtr;
		std :: string U8;
		std :: string U16;
		std :: string U32;
		std :: string U64;
		std :: string UPtr;
		std :: string Void;
		std :: string Char;
		std :: string F32;
		std :: string F64;
		std :: string Str8;
		std :: string Str16;
		std :: string Str32;
		
		std :: string Namespace;
		std :: string Import;
		std :: string Struct;
		std :: string Trait;
		std :: string Function;
		std :: string Return;
		std :: string Enum;
		std :: string Ignore;
		std :: string Implement;
		std :: string Self;
		std :: string Where;
		
		std :: string Mut;
		std :: string Public;
		std :: string Inline;
		
		std :: string Init;
		std :: string Drop;
		
		std :: string If;
		std :: string Else;
		std :: string While;
		std :: string Do;
		std :: string For;
		std :: string Match;
		std :: string Break;
		std :: string Loop;
		
		std :: string Bind;
		std :: string Const;
		
		std :: string Require;
		
		std :: string Alias;
		
	} KeywordLocalization;
	
	const KeywordLocalization kKeywordLocalization_EN
	{
		
		u8"true",
		u8"false",
	
		u8"null",
		
		u8"bool",
		u8"i8",
		u8"i16",
		u8"i32",
		u8"i64",
		u8"iptr",
		u8"u8",
		u8"u16",
		u8"u32",
		u8"u64",
		u8"uptr",
		u8"void",
		u8"char",
		u8"f32",
		u8"f64",
		u8"str",
		u8"str16",
		u8"str32",
		
		u8"namespace",
		u8"import",
		u8"struct",
		u8"trait",
		u8"function",
		u8"return",
		u8"enum",
		u8"ignore",
		u8"implement",
		u8"self",
		u8"where",
		
		u8"mut",
		u8"public",
		u8"inline",
		
		u8"init",
		u8"drop",
		
		u8"if",
		u8"else",
		u8"while",
		u8"do",
		u8"for",
		u8"match",
		u8"break",
		u8"loop",
		
		u8"bind",
		u8"const",
		u8"require",
		
		u8"alias",
		
	};
	
	const KeywordLocalization kKeywordLocalization_FR
	{
		
		u8"vrai", // true
		u8"faux", // false
	
		u8"nul",
	
		u8"bool",
		u8"i8",
		u8"i16",
		u8"i32",
		u8"i64",
		u8"iptr",
		u8"u8",
		u8"u16",
		u8"u32",
		u8"u64",
		u8"uptr",
		u8"vide", // void
		u8"char",
		u8"f32",
		u8"f64",
		u8"str",
		u8"str16",
		u8"str32",
	
		u8"espacenom", // namespace
		u8"importer",
		u8"struct",
		u8"trait",
		u8"fonction",
		u8"rendre", // return
		u8"énum",
		u8"ignorer",
		u8"réaliser", // implement
		u8"soi", // self
		u8"ou",
	
		u8"mut",
		u8"public",
		u8"enligne", // inline
	
		u8"init",
		u8"baisser", // drop
	
		u8"si", // if
		u8"autre", // else
		u8"alors", // while
		u8"faire", // do
		u8"pour", // for
		u8"identifier", // match
		u8"quitter", // break
		u8"boucle", // loop
	
		u8"lier", // bind
		u8"const",
		u8"faut", // require
		
		u8"alias",
		
	};
	
}

#endif
