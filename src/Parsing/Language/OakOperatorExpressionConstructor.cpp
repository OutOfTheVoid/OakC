#include <Parsing/Language/OakOperatorExpressionConstructor.h>
#include <Parsing/Language/OakPrimaryExpressionConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>

#include <Parsing/Language/OakASTTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakOperatorExpressionConstructor OakOperatorExpressionConstructor :: Instance;

typedef enum
{
	
	kOperatorAssociativity_Left_Unary, // Operator sits right of term
	kOperatorAssociativity_Right_Unary, // Operator sits left of term
	kOperatorAssociativity_Left_Binary, // Left-associative binary
	kOperatorAssociativity_Right_Binary, // Right-associative binary
	kOperatorAssociativity_Left_Bracket, // Left-associative bracketed
	kOperatorAssociativity_Right_Bracket, // Left-associative bracketed
	kOperatorAssociativity_Left_Double, // Groups three terms together with 1st and 2nd op tokens, right associative
	kOperatorAssociativity_Right_Double, // Groups three terms together with 1st and 2nd op tokens, right associative
	
} OperatorAssociativity;

typedef struct
{
	
	uint64_t OperatorTag;
	uint64_t OperatorTag2;
	
	uint32_t Precedence;
	
	uint64_t ASTTag;
	
	OperatorAssociativity Associativity;
	
} _OperatorEntry_t;

_OperatorEntry_t _Oak_OperatorList [] =
{
	
	{ OakTokenTags :: kTokenTag_Dot, 0, 1, OakASTTags :: kASTTag_Operator_DirectMemberAccess, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_Minus_TriangleBracket_Close, 0, 1, OakASTTags :: kASTTag_Operator_IndirectMemberAccess, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_SquareBracket_Open, OakTokenTags :: kTokenTag_SquareBracket_Close, 1, OakASTTags :: kASTTag_Operator_ArrayAccess, kOperatorAssociativity_Left_Bracket },
	{ OakTokenTags :: kTokenTag_Parenthesis_Open, OakTokenTags :: kTokenTag_Parenthesis_Close, 1, OakASTTags :: kASTTag_Operator_ArrayAccess, kOperatorAssociativity_Left_Bracket },
	{ OakTokenTags :: kTokenTag_DoublePlus, 0, 1, OakASTTags :: kASTTag_Operator_PostfixIncrement, kOperatorAssociativity_Left_Unary },
	{ OakTokenTags :: kTokenTag_DoubleMinus, 0, 1, OakASTTags :: kASTTag_Operator_PostfixDecrement, kOperatorAssociativity_Left_Unary },
	{ OakTokenTags :: kTokenTag_DoublePlus, 0, 2, OakASTTags :: kASTTag_Operator_PrefixIncrement, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_DoubleMinus, 0, 2, OakASTTags :: kASTTag_Operator_PrefixDecrement, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_Tilde, 0, 2, OakASTTags :: kASTTag_Operator_BitwiseNot, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_ExclamationMark, 0, 2, OakASTTags :: kASTTag_Operator_LogicalNot, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_Plus, 0, 2, OakASTTags :: kASTTag_Operator_UnaryNegate, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_Minus, 0, 2, OakASTTags :: kASTTag_Operator_UnaryPositive, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_Ampersand, 0, 2, OakASTTags :: kASTTag_Operator_ReferenceAddressOf, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_Star, 0, 2, OakASTTags :: kASTTag_Operator_PointerDeref, kOperatorAssociativity_Right_Unary },
	{ OakTokenTags :: kTokenTag_Star, 0, 3, OakASTTags :: kASTTag_Operator_Multiply, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_Slash, 0, 3, OakASTTags :: kASTTag_Operator_Divide, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_Percent, 0, 3, OakASTTags :: kASTTag_Operator_Modulo, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_Plus, 0, 4, OakASTTags :: kASTTag_Operator_Add, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_Minus, 0, 4, OakASTTags :: kASTTag_Operator_Subtract, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open, 0, 5, OakASTTags :: kASTTag_Operator_LeftShift, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close, 0, 5, OakASTTags :: kASTTag_Operator_RightShift, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Open, 0, 6, OakASTTags :: kASTTag_Operator_GreaterThan, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Close, 0, 6, OakASTTags :: kASTTag_Operator_LessThan, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Open_Equals, 0, 6, OakASTTags :: kASTTag_Operator_GreaterThanOrEqual, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Close_Equals, 0, 6, OakASTTags :: kASTTag_Operator_LessThanOrEqual, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_ExclamationMark_Equals, 0, 7, OakASTTags :: kASTTag_Operator_NotEqual, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_DoubleEquals, 0, 7, OakASTTags :: kASTTag_Operator_Equal, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_Ampersand, 0, 8, OakASTTags :: kASTTag_Operator_BitwiseAnd, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_Carrot, 0, 9, OakASTTags :: kASTTag_Operator_BitwiseXor, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_VerticalBar, 0, 10, OakASTTags :: kASTTag_Operator_BitwiseOr, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_DoubleAmpersand, 0, 11, OakASTTags :: kASTTag_Operator_LogicalAnd, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_DoubleVerticalBar, 0, 12, OakASTTags :: kASTTag_Operator_LogicalOr, kOperatorAssociativity_Left_Binary },
	{ OakTokenTags :: kTokenTag_QuestionMark, OakTokenTags :: kTokenTag_Colon, 13, OakASTTags :: kASTTag_Operator_Ternary, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Equals, 0, 14, OakASTTags :: kASTTag_Operator_Assignment, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Star_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundMultiply, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Slash_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundDivide, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Percent_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundModulo, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Plus_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundAdd, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Minus_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundSubtract, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundLeftShift, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundRightShift, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Ampersand_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseAnd, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_VerticalBar_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseOr, kOperatorAssociativity_Right_Binary },
	{ OakTokenTags :: kTokenTag_Carrot_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseXor, kOperatorAssociativity_Right_Binary },
	
};

OakOperatorExpressionConstructor :: OakOperatorExpressionConstructor ():
	PrimaryGroup (),
	MajorGroup ()
{
	
	PrimaryGroup.AddConstructorCantidate ( & OakPrimaryExpressionConstructor :: Instance, 0 );
	
	MajorGroup.AddConstructorCantidate ( & OakExpressionConstructor :: Instance, 0 );
	
}

OakOperatorExpressionConstructor :: ~OakOperatorExpressionConstructor ()
{
}

void OakOperatorExpressionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	// TODO: write operator parsing algorithm...
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	// 
	
}
