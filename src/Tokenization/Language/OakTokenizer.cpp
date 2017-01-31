#include <Tokenization/Language/OakTokenizer.h>

#include <Tokenization/CharMatchSplitRule.h>
#include <Tokenization/CharMatchRunSplitRule.h>
#include <Tokenization/StringMatchSplitRule.h>
#include <Tokenization/MultiStringMatchSplitRule.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Tokenization/Language/OakMultilineCommentSplitRule.h>
#include <Tokenization/Language/OakSingleLineCommentSplitRule.h>
#include <Tokenization/Language/OakStringSplitRule.h>
#include <Tokenization/Language/OakFloatingPointSplitRule.h>
#include <Tokenization/Language/OakIntegerSplitRule.h>
#include <Tokenization/Language/OakIdentifierSplitRule.h>

const Tokenizer * OakTokenizer :: OakTokenizerInstance = NULL;

const Tokenizer & OakTokenizer :: GetOakTokenizer ()
{
	
	if ( OakTokenizerInstance != NULL )
		return * OakTokenizerInstance;
	
	Tokenizer * NewTokenizer = new Tokenizer ();
	
	// Comments
	ITokenSplitRule * SingleLineCommentRule = new OakSingleLineCommentSplitRule ();
	ITokenSplitRule * MultilineCommentRule = new OakMultilineCommentSplitRule ();
	
	// Whitespace
	ITokenSplitRule * WhitespaceRule = new CharMatchRunSplitRule ( U"\u0020\u0009\u000a\u000b\u000c\u000d\u0085\u2028\u2029 \n", 10, false, OakTokenTags :: kTokenTag_Whitespace );
	
	// String literal
	ITokenSplitRule * StringLiteralRule = new OakStringSplitRule ();
	
	// Float literal
	ITokenSplitRule * FloatLiteralRule = new OakFloatingPointSplitRule ();
	
	// Integer literal
	ITokenSplitRule * IntegerLiteralRule = new OakIntegerSplitRule ();
	
	// Semicolon
	ITokenSplitRule * SemicolonRule = new CharMatchSplitRule ( U';', OakTokenTags :: kTokenTag_Semicolon );
	// Comma
	ITokenSplitRule * CommaRule = new CharMatchSplitRule ( U',', OakTokenTags :: kTokenTag_Comma );
	// Square bracket open
	ITokenSplitRule * SquareBracketOpenRule = new CharMatchSplitRule ( U'[', OakTokenTags :: kTokenTag_SquareBracket_Open );
	// Square bracket close
	ITokenSplitRule * SquareBracketCloseRule = new CharMatchSplitRule ( U']', OakTokenTags :: kTokenTag_SquareBracket_Close );
	// Curly bracket open
	ITokenSplitRule * CurlyBracketOpenRule = new CharMatchSplitRule (  U'{', OakTokenTags :: kTokenTag_CurlyBracket_Open );
	// Curly bracket close
	ITokenSplitRule * CurlyBracketCloseRule = new CharMatchSplitRule (  U'}', OakTokenTags :: kTokenTag_CurlyBracket_Close );
	// Parenthesis open
	ITokenSplitRule * ParenthesisOpenRule = new CharMatchSplitRule (  U'(', OakTokenTags :: kTokenTag_Parenthesis_Open );
	// Parenthesis close
	ITokenSplitRule * ParenthesisCloseRule = new CharMatchSplitRule (  U')', OakTokenTags :: kTokenTag_Parenthesis_Close );
	// Pound
	ITokenSplitRule * PoundRule = new CharMatchSplitRule (  U'#', OakTokenTags :: kTokenTag_Pound );
	// Double Colon
	ITokenSplitRule * DoubleColonRule = new StringMatchSplitRule (  U"::", OakTokenTags :: kTokenTag_DoubleColon );
	// Dot
	ITokenSplitRule * DotRule = new CharMatchSplitRule ( U'.', OakTokenTags :: kTokenTag_Dot );
	// Double Equals
	ITokenSplitRule * DoubleEqualsRule = new StringMatchSplitRule ( U"==", OakTokenTags :: kTokenTag_DoubleEquals );
	// Plus Equals
	ITokenSplitRule * PlusEqualsRule = new StringMatchSplitRule ( U"+=", OakTokenTags :: kTokenTag_PlusEquals );
	// Minus Equals
	ITokenSplitRule * MinusEqualsRule = new StringMatchSplitRule ( U"-=", OakTokenTags :: kTokenTag_MinusEquals );
	// Star Equals
	ITokenSplitRule * StarEqualsRule = new StringMatchSplitRule ( U"*=", OakTokenTags :: kTokenTag_StarEquals );
	// Slash Equals
	ITokenSplitRule * SlashEqualsRule = new StringMatchSplitRule ( U"/=", OakTokenTags :: kTokenTag_SlashEquals );
	// Double Triangle Bracket Open Equals
	ITokenSplitRule * DoubleTriangleBracketOpenEqualsRule = new StringMatchSplitRule ( U"<<=", OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open_Equals );
	// Double Triangle Bracket Close Equals
	ITokenSplitRule * DoubleTriangleBracketCloseEqualsRule = new StringMatchSplitRule ( U">>=", OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close_Equals );
	// Double Ampersand Equals
	ITokenSplitRule * DoubleAmpersandEqualsRule = new StringMatchSplitRule ( U"&&=", OakTokenTags :: kTokenTag_DoubleAmpersand_Equals );
	// Double Vertical Bar Equals
	ITokenSplitRule * DoubleVerticalBarEqualsRule = new StringMatchSplitRule ( U"||=", OakTokenTags :: kTokenTag_DoubleVerticalBar_Equals );
	// Tilde
	ITokenSplitRule * TildeRule = new CharMatchSplitRule ( U'~', OakTokenTags :: kTokenTag_Tilde );
	// Question Mark
	ITokenSplitRule * QuestionMarkRule = new CharMatchSplitRule ( U'?', OakTokenTags :: kTokenTag_QuestionMark );
	// Exclamation Mark Equals
	ITokenSplitRule * ExclamationMarkEqualsRule = new StringMatchSplitRule ( U"!=", OakTokenTags :: kTokenTag_ExclamationMark_Equals );
	
	// Triangle Bracket Open Double Equals
	ITokenSplitRule * TriangleBracketOpenEqualsRule = new StringMatchSplitRule ( U"<=", OakTokenTags :: kTokenTag_TriangleBracket_Open_Equals );
	// Triangle Bracket Close Double Equals
	ITokenSplitRule * TriangleBracketCloseEqualsRule = new StringMatchSplitRule ( U">=", OakTokenTags :: kTokenTag_TriangleBracket_Close_Equals );
	// Triangle bracket open
	ITokenSplitRule * DoubleTriangleBracketOpenRule = new StringMatchSplitRule (  U"<<", OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open );
	// Triangle bracket close
	ITokenSplitRule * DoubleTriangleBracketCloseRule = new StringMatchSplitRule (  U">>", OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close );
	// Colon
	ITokenSplitRule * ColonRule = new CharMatchSplitRule ( U':', OakTokenTags :: kTokenTag_Colon );
	// Equals
	ITokenSplitRule * EqualsRule = new CharMatchSplitRule ( U'=', OakTokenTags :: kTokenTag_Equals );
	// Star
	ITokenSplitRule * StarRule = new CharMatchSplitRule ( U'*', OakTokenTags :: kTokenTag_Star );
	// Plus
	ITokenSplitRule * PlusRule = new CharMatchSplitRule ( U'+', OakTokenTags :: kTokenTag_Plus );
	// Minus
	ITokenSplitRule * MinusRule = new CharMatchSplitRule ( U'-', OakTokenTags :: kTokenTag_Minus );
	// Slash
	ITokenSplitRule * SlashRule = new CharMatchSplitRule ( U'/', OakTokenTags :: kTokenTag_Slash );
	// Double Ampersand
	ITokenSplitRule * DoubleAmpersandRule = new StringMatchSplitRule ( U"&&", OakTokenTags :: kTokenTag_DoubleAmpersand );
	// Double Vertical Bar
	ITokenSplitRule * DoubleVerticalBarRule = new StringMatchSplitRule ( U"||", OakTokenTags :: kTokenTag_DoubleVerticalBar );
	// Ampersand Equals
	ITokenSplitRule * AmpersandEqualsRule = new StringMatchSplitRule ( U"&=", OakTokenTags :: kTokenTag_Ampersand_Equals );
	// Vertical Bar Equals
	ITokenSplitRule * VerticalBarEqualsRule = new StringMatchSplitRule ( U"|=", OakTokenTags :: kTokenTag_VerticalBar_Equals );
	// Exclamation Mark
	ITokenSplitRule * ExclamationMarkRule = new CharMatchSplitRule ( U'!', OakTokenTags :: kTokenTag_ExclamationMark );
	
	// Triangle bracket open
	ITokenSplitRule * TriangleBracketOpenRule = new CharMatchSplitRule (  U'<', OakTokenTags :: kTokenTag_TriangleBracket_Open );
	// Triangle bracket close
	ITokenSplitRule * TriangleBracketCloseRule = new CharMatchSplitRule (  U'>', OakTokenTags :: kTokenTag_TriangleBracket_Close );
	// Ampersand
	ITokenSplitRule * AmpersandRule = new CharMatchSplitRule ( U'&', OakTokenTags :: kTokenTag_Ampersand );
	// Vertical Bar
	ITokenSplitRule * VerticalBarRule = new CharMatchSplitRule ( U'|', OakTokenTags :: kTokenTag_VerticalBar );
	
	
	ITokenSplitRule * IdentifierRule = new OakIdentifierSplitRule ();
	
	NewTokenizer -> AddSplitRule ( SingleLineCommentRule, 0 );
	NewTokenizer -> AddSplitRule ( MultilineCommentRule, 0 );
	
	NewTokenizer -> AddSplitRule ( WhitespaceRule, 1 );
	NewTokenizer -> AddSplitRule ( IdentifierRule, 2 );
	
	NewTokenizer -> AddSplitRule ( StringLiteralRule, 2 );
	NewTokenizer -> AddSplitRule ( FloatLiteralRule, 2 );
	NewTokenizer -> AddSplitRule ( IntegerLiteralRule, 2 );
	
	NewTokenizer -> AddSplitRule ( SemicolonRule, 3 );
	NewTokenizer -> AddSplitRule ( CommaRule, 3 );
	NewTokenizer -> AddSplitRule ( SquareBracketOpenRule, 3 );
	NewTokenizer -> AddSplitRule ( SquareBracketCloseRule, 3 );
	NewTokenizer -> AddSplitRule ( CurlyBracketOpenRule, 3 );
	NewTokenizer -> AddSplitRule ( CurlyBracketCloseRule, 3 );
	NewTokenizer -> AddSplitRule ( ParenthesisOpenRule, 3 );
	NewTokenizer -> AddSplitRule ( ParenthesisCloseRule, 3 );
	NewTokenizer -> AddSplitRule ( PoundRule, 3 );
	NewTokenizer -> AddSplitRule ( DoubleColonRule, 3 );
	NewTokenizer -> AddSplitRule ( DotRule, 3 );
	NewTokenizer -> AddSplitRule ( PlusEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( MinusEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( StarEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( SlashEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( DoubleTriangleBracketOpenEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( DoubleTriangleBracketCloseEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( DoubleAmpersandEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( DoubleVerticalBarEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( DoubleEqualsRule, 3 );
	NewTokenizer -> AddSplitRule ( TildeRule, 3 );
	NewTokenizer -> AddSplitRule ( QuestionMarkRule, 3 );
	NewTokenizer -> AddSplitRule ( ExclamationMarkEqualsRule, 3 );
	
	NewTokenizer -> AddSplitRule ( TriangleBracketOpenEqualsRule, 4 );
	NewTokenizer -> AddSplitRule ( TriangleBracketCloseEqualsRule, 4 );
	NewTokenizer -> AddSplitRule ( DoubleTriangleBracketOpenRule, 4 );
	NewTokenizer -> AddSplitRule ( DoubleTriangleBracketCloseRule, 4 );
	NewTokenizer -> AddSplitRule ( ColonRule, 4 );
	NewTokenizer -> AddSplitRule ( EqualsRule, 4 );
	NewTokenizer -> AddSplitRule ( StarRule, 4 );
	NewTokenizer -> AddSplitRule ( PlusRule, 4 );
	NewTokenizer -> AddSplitRule ( MinusRule, 4 );
	NewTokenizer -> AddSplitRule ( SlashRule, 4 );
	NewTokenizer -> AddSplitRule ( DoubleAmpersandRule, 4 );
	NewTokenizer -> AddSplitRule ( DoubleVerticalBarRule, 4 );
	NewTokenizer -> AddSplitRule ( AmpersandEqualsRule, 4 );
	NewTokenizer -> AddSplitRule ( VerticalBarEqualsRule, 4 );
	NewTokenizer -> AddSplitRule ( ExclamationMarkRule, 4 );
	
	NewTokenizer -> AddSplitRule ( TriangleBracketOpenRule, 5 );
	NewTokenizer -> AddSplitRule ( TriangleBracketCloseRule, 5 );
	NewTokenizer -> AddSplitRule ( AmpersandRule, 5 );
	NewTokenizer -> AddSplitRule ( VerticalBarRule, 5 );
	
	OakTokenizerInstance = NewTokenizer;
	
	return * OakTokenizerInstance;
	
}
