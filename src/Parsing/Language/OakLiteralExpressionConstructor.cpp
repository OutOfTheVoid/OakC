#include <Parsing/Language/OakLiteralExpressionConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakParsingUtils.h>

#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/TestSet.h>

OakLiteralExpressionConstructor OakLiteralExpressionConstructor :: Instance;

const uint64_t _OakLiteralExpressionConstructor_ValidLiteralTags [] =
{
	
	OakTokenTags :: kTokenTag_StringLiteralDefault,
	OakTokenTags :: kTokenTag_StringLiteralu8,
	OakTokenTags :: kTokenTag_StringLiteralu16,
	OakTokenTags :: kTokenTag_StringLiteralu32,
	OakTokenTags :: kTokenTag_CharLiteral,
	OakTokenTags :: kTokenTag_FloatLiteralDefaultSize,
	OakTokenTags :: kTokenTag_FloatLiteral32,
	OakTokenTags :: kTokenTag_FloatLiteral64,
	OakTokenTags :: kTokenTag_IndeterminateIntegerLiteral,
	OakTokenTags :: kTokenTag_SignedIntegerLiteralDefault,
	OakTokenTags :: kTokenTag_SignedIntegerLiteral8,
	OakTokenTags :: kTokenTag_SignedIntegerLiteral16,
	OakTokenTags :: kTokenTag_SignedIntegerLiteral32,
	OakTokenTags :: kTokenTag_SignedIntegerLiteral64,
	OakTokenTags :: kTokenTag_UnsignedIntegerLiteralDefault,
	OakTokenTags :: kTokenTag_UnsignedIntegerLiteral8,
	OakTokenTags :: kTokenTag_UnsignedIntegerLiteral16,
	OakTokenTags :: kTokenTag_UnsignedIntegerLiteral32,
	OakTokenTags :: kTokenTag_UnsignedIntegerLiteral64,
	
};

const TestSet <uint64_t> _OakLiteralExpressionConstructor_LiteralTagTestSet ( _OakLiteralExpressionConstructor_ValidLiteralTags, 19, false );

OakLiteralExpressionConstructor :: OakLiteralExpressionConstructor ()
{
}

OakLiteralExpressionConstructor :: ~OakLiteralExpressionConstructor ()
{
}

void OakLiteralExpressionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! ( _OakLiteralExpressionConstructor_LiteralTagTestSet.Contains ( CurrentToken -> GetTag () ) || OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Null ) || OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_True ) || OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_False ) ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * LiteralElement = new ASTElement ();
	
	LiteralElement -> SetTag ( OakASTTags :: kASTTag_LiteralExpression );
	LiteralElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	Output.Accepted = true;
	Output.ConstructedElement = LiteralElement;
	Output.TokensConsumed = 1;
	
}

