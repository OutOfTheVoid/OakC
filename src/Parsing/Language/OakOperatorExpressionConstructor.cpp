#include <Parsing/Language/OakOperatorExpressionConstructor.h>
#include <Parsing/Language/OakPrimaryExpressionConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>

#include <Parsing/Language/OakASTTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakOperatorExpressionConstructor OakOperatorExpressionConstructor :: Instance;

typedef struct
{
	
	uint64_t OperatorTag;
	uint32_t Precedence;
	uint64_t ASTTag;
	
} _OperatorEntry_t;

_OperatorEntry_t _OakBareTypeNameConstructor_AllowedLeftUnaryOperatorList [] =
{
	
	{ OakTokenTags :: kTokenTag_DoublePlus, 1, OakASTTags :: kASTTag_Operator_PostfixIncrement },
	{ OakTokenTags :: kTokenTag_DoubleMinus, 1, OakASTTags :: kASTTag_Operator_PostfixDecrement },
	
};

bool _OakBareTypeNameConstructor_TryToken_LeftUnaryOperator ( const Token * Current, const _OperatorEntry_t *& Entry )
{
	
	uint64_t Tag = Current -> GetTag ();
	
	for ( uint64_t I = 0; I < sizeof ( _OakBareTypeNameConstructor_AllowedLeftUnaryOperatorList ) / sizeof ( _OperatorEntry_t ); I ++ )
	{
		
		if ( Tag == _OakBareTypeNameConstructor_AllowedLeftUnaryOperatorList [ I ].OperatorTag )
		{
			
			Entry = & _OakBareTypeNameConstructor_AllowedLeftUnaryOperatorList [ I ];
			
			return true;
			
		}
		
	}
	
	return false;
	
}

_OperatorEntry_t _OakBareTypeNameConstructor_AllowedRightUnaryOperatorList [] =
{
	
	{ OakTokenTags :: kTokenTag_DoublePlus, 2, OakASTTags :: kASTTag_Operator_PrefixIncrement },
	{ OakTokenTags :: kTokenTag_DoubleMinus, 2, OakASTTags :: kASTTag_Operator_PrefixDecrement },
	{ OakTokenTags :: kTokenTag_Tilde, 2, OakASTTags :: kASTTag_Operator_BitwiseNot },
	{ OakTokenTags :: kTokenTag_ExclamationMark, 2, OakASTTags :: kASTTag_Operator_LogicalNot },
	{ OakTokenTags :: kTokenTag_Plus, 2, OakASTTags :: kASTTag_Operator_UnaryNegate },
	{ OakTokenTags :: kTokenTag_Minus, 2, OakASTTags :: kASTTag_Operator_UnaryPositive },
	{ OakTokenTags :: kTokenTag_Ampersand, 2, OakASTTags :: kASTTag_Operator_ReferenceAddressOf },
	{ OakTokenTags :: kTokenTag_Star, 2, OakASTTags :: kASTTag_Operator_PointerDeref },
	
};

bool _OakBareTypeNameConstructor_TryToken_RightUnaryOperator ( const Token * Current, const _OperatorEntry_t *& Entry )
{
	
	uint64_t Tag = Current -> GetTag ();
	
	for ( uint64_t I = 0; I < sizeof ( _OakBareTypeNameConstructor_AllowedRightUnaryOperatorList ) / sizeof ( _OperatorEntry_t ); I ++ )
	{
		
		if ( Tag == _OakBareTypeNameConstructor_AllowedRightUnaryOperatorList [ I ].OperatorTag )
		{
			
			Entry = & _OakBareTypeNameConstructor_AllowedRightUnaryOperatorList [ I ];
			
			return true;
			
		}
		
	}
	
	return false;
	
}

_OperatorEntry_t _OakBareTypeNameConstructor_AllowedLeftBinaryOperatorList [] =
{
	
	{ OakTokenTags :: kTokenTag_Star, 3, OakASTTags :: kASTTag_Operator_Multiply },
	{ OakTokenTags :: kTokenTag_Slash, 3, OakASTTags :: kASTTag_Operator_Divide },
	{ OakTokenTags :: kTokenTag_Percent, 3, OakASTTags :: kASTTag_Operator_Modulo },
	{ OakTokenTags :: kTokenTag_Plus, 4, OakASTTags :: kASTTag_Operator_Add },
	{ OakTokenTags :: kTokenTag_Minus, 4, OakASTTags :: kASTTag_Operator_Subtract },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open, 5, OakASTTags :: kASTTag_Operator_LeftShift },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close, 5, OakASTTags :: kASTTag_Operator_RightShift },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Open, 6, OakASTTags :: kASTTag_Operator_GreaterThan },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Close, 6, OakASTTags :: kASTTag_Operator_LessThan },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Open_Equals, 6, OakASTTags :: kASTTag_Operator_GreaterThanOrEqual },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Close_Equals, 6, OakASTTags :: kASTTag_Operator_LessThanOrEqual },
	{ OakTokenTags :: kTokenTag_ExclamationMark_Equals, 7, OakASTTags :: kASTTag_Operator_NotEqual },
	{ OakTokenTags :: kTokenTag_DoubleEquals, 7, OakASTTags :: kASTTag_Operator_Equal },
	{ OakTokenTags :: kTokenTag_Ampersand, 8, OakASTTags :: kASTTag_Operator_BitwiseAnd },
	{ OakTokenTags :: kTokenTag_Carrot, 9, OakASTTags :: kASTTag_Operator_BitwiseXor },
	{ OakTokenTags :: kTokenTag_VerticalBar, 10, OakASTTags :: kASTTag_Operator_BitwiseOr },
	{ OakTokenTags :: kTokenTag_DoubleAmpersand, 11, OakASTTags :: kASTTag_Operator_LogicalAnd },
	{ OakTokenTags :: kTokenTag_DoubleVerticalBar, 12, OakASTTags :: kASTTag_Operator_LogicalOr },
	
};

bool _OakBareTypeNameConstructor_TryToken_LeftBinaryOperator ( const Token * Current, const _OperatorEntry_t *& Entry )
{
	
	uint64_t Tag = Current -> GetTag ();
	
	for ( uint64_t I = 0; I < sizeof ( _OakBareTypeNameConstructor_AllowedLeftBinaryOperatorList ) / sizeof ( _OperatorEntry_t ); I ++ )
	{
		
		if ( Tag == _OakBareTypeNameConstructor_AllowedLeftBinaryOperatorList [ I ].OperatorTag )
		{
			
			Entry = & _OakBareTypeNameConstructor_AllowedLeftBinaryOperatorList [ I ];
			
			return true;
			
		}
		
	}
	
	return false;
	
}

// Ternary expression here

_OperatorEntry_t _OakBareTypeNameConstructor_AllowedRightBinaryOperatorList [] =
{
	
	{ OakTokenTags :: kTokenTag_Equals, 14, OakASTTags :: kASTTag_Operator_Assignment },
	{ OakTokenTags :: kTokenTag_Star_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundMultiply },
	{ OakTokenTags :: kTokenTag_Slash_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundDivide },
	{ OakTokenTags :: kTokenTag_Percent_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundModulo },
	{ OakTokenTags :: kTokenTag_Plus_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundAdd },
	{ OakTokenTags :: kTokenTag_Minus_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundSubtract },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundLeftShift },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundRightShift },
	{ OakTokenTags :: kTokenTag_Ampersand_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseAnd },
	{ OakTokenTags :: kTokenTag_VerticalBar_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseOr },
	{ OakTokenTags :: kTokenTag_Carrot_Equals, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseXor },
	
};

bool _OakBareTypeNameConstructor_TryToken_RightBinaryOperator ( const Token * Current, const _OperatorEntry_t *& Entry )
{
	
	uint64_t Tag = Current -> GetTag ();
	
	for ( uint64_t I = 0; I < sizeof ( _OakBareTypeNameConstructor_TryToken_RightBinaryOperator ) / sizeof ( _OperatorEntry_t ); I ++ )
	{
		
		if ( Tag == _OakBareTypeNameConstructor_TryToken_RightBinaryOperator [ I ].OperatorTag )
		{
			
			Entry = & _OakBareTypeNameConstructor_TryToken_RightBinaryOperator [ I ];
			
			return true;
			
		}
		
	}
	
	return false;
	
}

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
	
}
