#ifndef TOKENIZATION_LANGUAGE_OAKTOKENTAGS_H
#define TOKENIZATION_LANGUAGE_OAKTOKENTAGS_H

#include <stdint.h>

namespace OakTokenTags
{
	
	/**
	 * OakTokenTags: A set of tags for the tokenizer to mark tokens of specific kinds early, to prevent extra work being needed in the lexer.
	 */
	
	const uint64_t kTokenTag_Whitespace = 1;
	
	const uint64_t kTokenTag_Comment = 2;
	
	const uint64_t kTokenTag_StringLiteralDefault = 3;
	const uint64_t kTokenTag_StringLiteralu8 = 4;
	const uint64_t kTokenTag_StringLiteralu16 = 5;
	const uint64_t kTokenTag_StringLiteralu32 = 6;
	
	const uint64_t kTokenTag_RESERVED_0 = 7;
	
	const uint64_t kTokenTag_CharLiteral = 8;
	
	const uint64_t kTokenTag_FloatLiteralDefaultSize = 9;
	const uint64_t kTokenTag_FloatLiteral32 = 10;
	const uint64_t kTokenTag_FloatLiteral64 = 11;
	
	const uint64_t kTokenAuxTax_FloatLiteral_HexFloat = 1;
	
	const uint64_t kTokenTag_IndeterminateIntegerLiteral = 12;
	
	const uint64_t kTokenTag_SignedIntegerLiteralDefault = 13;
	const uint64_t kTokenTag_SignedIntegerLiteral8 = 14;
	const uint64_t kTokenTag_SignedIntegerLiteral16 = 15;
	const uint64_t kTokenTag_SignedIntegerLiteral32 = 16;
	const uint64_t kTokenTag_SignedIntegerLiteral64 = 17;
	const uint64_t kTokenTag_SignedIntegerLiteralPointer = 18;
	
	const uint64_t kTokenAuxTax_IntegerLiteral_Hex = 1;
	const uint64_t kTokenAuxTax_IntegerLiteral_Octal = 2;
	const uint64_t kTokenAuxTax_IntegerLiteral_Binary = 3;
	
	const uint64_t kTokenTag_UnsignedIntegerLiteralDefault = 19;
	const uint64_t kTokenTag_UnsignedIntegerLiteral8 = 20;
	const uint64_t kTokenTag_UnsignedIntegerLiteral16 = 21;
	const uint64_t kTokenTag_UnsignedIntegerLiteral32 = 22;
	const uint64_t kTokenTag_UnsignedIntegerLiteral64 = 23;
	const uint64_t kTokenTag_UnsignedIntegerLiteralPointer = 24;
	
	const uint64_t kTokenTag_Semicolon = 25;
	const uint64_t kTokenTag_Colon = 26;
	const uint64_t kTokenTag_Comma = 27;
	const uint64_t kTokenTag_SquareBracket_Open = 28;
	const uint64_t kTokenTag_SquareBracket_Close = 29;
	const uint64_t kTokenTag_TriangleBracket_Open = 30;
	const uint64_t kTokenTag_TriangleBracket_Close = 31;
	const uint64_t kTokenTag_CurlyBracket_Open = 32;
	const uint64_t kTokenTag_CurlyBracket_Close = 33;
	const uint64_t kTokenTag_Parenthesis_Open = 34;
	const uint64_t kTokenTag_Parenthesis_Close = 35;
	const uint64_t kTokenTag_Pound = 36;
	const uint64_t kTokenTag_DoubleColon = 37;
	const uint64_t kTokenTag_Dot = 38;
	const uint64_t kTokenTag_Star = 39;
	const uint64_t kTokenTag_Plus = 40;
	const uint64_t kTokenTag_Minus = 41;
	const uint64_t kTokenTag_Slash = 42;
	const uint64_t kTokenTag_Equals = 43;
	const uint64_t kTokenTag_DoubleEquals = 44;
	const uint64_t kTokenTag_Ampersand = 45;
	const uint64_t kTokenTag_Plus_Equals = 46;
	const uint64_t kTokenTag_Minus_Equals = 47;
	const uint64_t kTokenTag_Star_Equals = 48;
	const uint64_t kTokenTag_Slash_Equals = 49;
	const uint64_t kTokenTag_TriangleBracket_Open_Equals = 50;
	const uint64_t kTokenTag_TriangleBracket_Close_Equals = 51;
	const uint64_t kTokenTag_DoubleTriangleBracket_Open_Equals = 52;
	const uint64_t kTokenTag_DoubleTriangleBracket_Close_Equals = 53;
	const uint64_t kTokenTag_DoubleTriangleBracket_Open = 54;
	const uint64_t kTokenTag_DoubleTriangleBracket_Close = 55;
	const uint64_t kTokenTag_DoubleAmpersand = 56;
	const uint64_t kTokenTag_VerticalBar = 57;
	const uint64_t kTokenTag_DoubleVerticalBar = 58;
	const uint64_t kTokenTag_Ampersand_Equals = 59;
	const uint64_t kTokenTag_VerticalBar_Equals = 60;
	const uint64_t kTokenTag_DoubleAmpersand_Equals = 61;
	const uint64_t kTokenTag_DoubleVerticalBar_Equals = 62;
	const uint64_t kTokenTag_Tilde = 63;
	const uint64_t kTokenTag_QuestionMark = 64;
	const uint64_t kTokenTag_ExclamationMark = 65;
	const uint64_t kTokenTag_ExclamationMark_Equals = 66;
	const uint64_t kTokenTag_DoublePlus = 67;
	const uint64_t kTokenTag_DoubleMinus = 68;
	const uint64_t kTokenTag_Percent = 69;
	const uint64_t kTokenTag_Carrot = 70;
	const uint64_t kTokenTag_Percent_Equals = 71;
	const uint64_t kTokenTag_Carrot_Equals = 72;
	const uint64_t kTokenTag_Minus_TriangleBracket_Close = 73;
	const uint64_t kTokenTag_TripleTriangleBracket_Close = 74;
	const uint64_t kTokenTag_TripleTriangleBracket_Close_Equals = 75;
	const uint64_t kTokenTag_BackTick = 76;
	
	const uint64_t kTokenTag_Identifier = 77;
	
	const uint64_t kTokenTag_DecoratorOpen = 78;
	
	const uint64_t kTokenTag_At = 79;
	
	//const uint64_t kTokenTag_ = ;
	
	const char * const TagNames [] =
	{
		
		"DEFAULT",
		"WHITESPACE",
		"COMMENT",
		"STRING_LITERAL<DEFAULT>",
		"STRING_LITERAL<UTF8>",
		"STRING_LITERAL<UTF16>",
		"STRING_LITERAL<UTF32>",
		"RESERVED",
		"CHARACHTER_LITERAL",
		"FLOAT_LITERAL_DEFAULT",
		"FLOAT_LITERAL_32",
		"FLOAT_LITERAL_64",
		"(U)INT_LITERAL_UNSPECIFIED",
		"INT_LITERAL_DEFAULT",
		"INT_LITERAL_8",
		"INT_LITERAL_16",
		"INT_LITERAL_32",
		"INT_LITERAL_64",
		"INT_LITERAL_PTR",
		"UINT_LITERAL_DEFAULT",
		"UINT_LITERAL_8",
		"UINT_LITERAL_16",
		"UINT_LITERAL_32",
		"UINT_LITERAL_64",
		"UINT_LITERAL_PTR",
		"SEMICOLON",
		"COLON",
		"COMMA",
		"SQ_BRACKET_OPEN",
		"SQ_BRACKET_CLOSE",
		"TRI_BRACKET_OPEN",
		"TRI_BRACKET_CLOSE",
		"CURL_BRACKET_OPEN",
		"CURL_BRACKET_CLOSE",
		"PAREN_OPEN",
		"PAREN_CLOSE",
		"POUND",
		"DOUBLE_COLON",
		"DOT",
		"STAR",
		"PLUS",
		"MINUS",
		"SLASH",
		"EQUALS",
		"DOUBLE_EQUALS",
		"AMPERSAND",
		"PLUS_EQUALS",
		"MINUS_EQUALS",
		"STAR_EQUALS",
		"SLASH_EQUALS",
		"TRI_BRACKET_OPEN_EQUALS",
		"TRI_BRACKET_CLOSE_EQUALS",
		"DOUBLE_TRI_BRACKET_OPEN_EQUALS",
		"DOUBLE_TRI_BRACKET_CLOSE_EQUALS",
		"DOUBLE_TRI_BRACKET_OPEN",
		"DOUBLE_TRI_BRACKET_CLOSE",
		"DOUBLE_AMPERSAND",
		"VERTICAL_BAR",
		"DOUBLE_VERTICAL_BAR",
		"AMPERSAND_EQUALS",
		"VERTICAL_BAR_EQUALS",
		"DOUBLE_AMPERSAND_EQUALS",
		"DOUBLE_VERTICAL_BAR_EQUALS",
		"TILDE",
		"QESTION_MARK",
		"EXCLAMATION_MARK",
		"EXCLAMATION_MARK_EQUALS",
		"DOUBLE_PLUS",
		"DOUBLE_MINUS",
		"PERCENT",
		"CARROT",
		"PERCENT_EQUALS",
		"CARROT_EQUALS",
		"MINUS_TRI_BRACKET_CLOSE",
		"TRIPLE_TRI_BRACKET_CLOSE",
		"TRIPLE_TRI_BRACKET_CLOSE_EQUALS",
		"BACK_TICK",
		"IDENT",
		"DECORTATOR_OPEN",
		"AT",
		
	};
	
	/*
	const uint64_t kTokenTag_Semicolon = 21;
	const uint64_t kTokenTag_Colon = 22;
	const uint64_t kTokenTag_Comma = 23;
	const uint64_t kTokenTag_SquareBracket_Open = 24;
	const uint64_t kTokenTag_SquareBracket_Close = 25;
	const uint64_t kTokenTag_TriangleBracket_Open = 26;
	const uint64_t kTokenTag_TriangleBracket_Close = 27;
	const uint64_t kTokenTag_CurlyBracket_Open = 28;
	const uint64_t kTokenTag_CurlyBracket_Close = 29;
	const uint64_t kTokenTag_Parenthesis_Open = 30;
	const uint64_t kTokenTag_Parenthesis_Close = 31;
	const uint64_t kTokenTag_Pound = 32;
	*/
	
}

#endif
