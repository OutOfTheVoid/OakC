#include <Parsing/Language/OakOperatorExpressionConstructor.h>

#include <Parsing/Language/OakPrimaryExpressionConstructor.h>
#include <Parsing/Language/OakExpressionConstructor.h>
#include <Parsing/Language/OakFunctionCallParameterListConstructor.h>
#include <Parsing/Language/OakMemberAccessNameConstructor.h>

#include <Parsing/Language/OakASTTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#ifndef NULL
	#define NULL nullptr
#endif

OakOperatorExpressionConstructor OakOperatorExpressionConstructor :: Instance;

typedef enum
{
	
	kOperatorAssociativity_Left_Unary = 0, // Operator sits right of term
	kOperatorAssociativity_Left_Unary_AsPrimary = 1, // Operator sits right of term, becomes a primary
	kOperatorAssociativity_Right_Unary = 2, // Operator sits left of term
	kOperatorAssociativity_Left_Binary = 3, // Left-associative binary
	kOperatorAssociativity_Right_Binary = 4, // Right-associative binary
	kOperatorAssociativity_Left_Bracket = 5, // Left-associative bracketed
	kOperatorAssociativity_Right_Bracket = 6, // Right-associative bracketed ( NOT USED )
	
	kOperatorAssociativity_Left_Double = 7, // Groups three terms together with 1st and 2nd op tokens, left associative ( NOT DONE )
	kOperatorAssociativity_Right_Double = 8, // Groups three terms together with 1st and 2nd op tokens, right associative ( NOT DONE )
	
	 // NOT ACTUAL OPERATOR TYPES! EXIST FOR ALGORITHM ONLY
	kOperatorAssociativity_PrimaryExpression = 9,
	kOperatorAssociativity_Initial = 10
	
} OperatorAssociativity;

inline bool _OakOperatorExpressionConstructor_AssociativityIsLeft ( OperatorAssociativity Associativity )
{
	
	return ( Associativity == kOperatorAssociativity_Left_Unary ) || ( Associativity == kOperatorAssociativity_Left_Unary_AsPrimary ) || ( Associativity == kOperatorAssociativity_Left_Binary ) || ( Associativity == kOperatorAssociativity_Left_Bracket ) || ( Associativity == kOperatorAssociativity_Left_Double ); 
	
}

typedef struct OperatorEntry_Struct
{
	
	uint64_t OperatorTag;
	uint64_t OperatorTag2;
	
	uint32_t Precedence;
	uint64_t ASTTag;
	OperatorAssociativity Associativity;
	
	struct OperatorEntry_Struct * FailureMutation;
	
	ASTConstructionGroup * SpecialGroup;
	
	bool First;
	
} _OperatorEntry_t;

ASTConstructionGroup :: StaticInitEntry _OakOperatorExpressionConstructor_FunctionCallParamListGroup_Entries [] =
{
	
	{ & OakFunctionCallParameterListConstructor :: Instance, 0 }
	
};

ASTConstructionGroup _OakOperatorExpressionConstructor_FunctionCallParamListGroup ( _OakOperatorExpressionConstructor_FunctionCallParamListGroup_Entries, 1 );

ASTConstructionGroup :: StaticInitEntry _OakOperatorExpressionConstructor_MemberAccessNameGroup_Entries [] =
{
	
	{ & OakMemberAccessNameConstructor :: Instance, 0 }
	
};

ASTConstructionGroup _OakOperatorExpressionConstructor_MemberAccessNameGroup ( _OakOperatorExpressionConstructor_MemberAccessNameGroup_Entries, 1 );

_OperatorEntry_t _OakOperatorExpressionConstructor_OperatorList [] =
{
	// 0
	{ OakTokenTags :: kTokenTag_SquareBracket_Open, OakTokenTags :: kTokenTag_SquareBracket_Close, 1, OakASTTags :: kASTTag_Operator_ArrayAccess, kOperatorAssociativity_Left_Bracket, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Parenthesis_Open, OakTokenTags :: kTokenTag_Parenthesis_Close, 1, OakASTTags :: kASTTag_Operator_FunctionCall, kOperatorAssociativity_Left_Bracket, NULL, & _OakOperatorExpressionConstructor_FunctionCallParamListGroup, true },
	{ OakTokenTags :: kTokenTag_DoublePlus, 0, 1, OakASTTags :: kASTTag_Operator_PostfixIncrement, kOperatorAssociativity_Left_Unary, & _OakOperatorExpressionConstructor_OperatorList [ 5 ], NULL, true },
	{ OakTokenTags :: kTokenTag_DoubleMinus, 0, 1, OakASTTags :: kASTTag_Operator_PostfixDecrement, kOperatorAssociativity_Left_Unary, & _OakOperatorExpressionConstructor_OperatorList [ 6 ], NULL, true },
	{ OakTokenTags :: kTokenTag_Dot, 0, 1, OakASTTags :: kASTTag_Operator_MemberAccess, kOperatorAssociativity_Left_Unary_AsPrimary, NULL, & _OakOperatorExpressionConstructor_MemberAccessNameGroup, true },
	// 5
	{ OakTokenTags :: kTokenTag_DoublePlus, 0, 2, OakASTTags :: kASTTag_Operator_PrefixIncrement, kOperatorAssociativity_Right_Unary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_DoubleMinus, 0, 2, OakASTTags :: kASTTag_Operator_PrefixDecrement, kOperatorAssociativity_Right_Unary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Tilde, 0, 2, OakASTTags :: kASTTag_Operator_BitwiseNot, kOperatorAssociativity_Right_Unary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_ExclamationMark, 0, 2, OakASTTags :: kASTTag_Operator_LogicalNot, kOperatorAssociativity_Right_Unary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Plus, 0, 2, OakASTTags :: kASTTag_Operator_UnaryPositive, kOperatorAssociativity_Right_Unary, & _OakOperatorExpressionConstructor_OperatorList [ 15 ], NULL, true },
	// 10
	{ OakTokenTags :: kTokenTag_Minus, 0, 2, OakASTTags :: kASTTag_Operator_UnaryNegate, kOperatorAssociativity_Right_Unary, & _OakOperatorExpressionConstructor_OperatorList [ 16 ], NULL, true },
	{ OakTokenTags :: kTokenTag_Ampersand, 0, 2, OakASTTags :: kASTTag_Operator_Reference, kOperatorAssociativity_Right_Unary, & _OakOperatorExpressionConstructor_OperatorList [ 26 ], NULL, true },
	{ OakTokenTags :: kTokenTag_Star, 0, 3, OakASTTags :: kASTTag_Operator_Multiply, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Slash, 0, 3, OakASTTags :: kASTTag_Operator_Divide, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Percent, 0, 3, OakASTTags :: kASTTag_Operator_Modulo, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	// 15
	{ OakTokenTags :: kTokenTag_Plus, 0, 4, OakASTTags :: kASTTag_Operator_Add, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Minus, 0, 4, OakASTTags :: kASTTag_Operator_Subtract, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open, 0, 5, OakASTTags :: kASTTag_Operator_LeftShift, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close, 0, 5, OakASTTags :: kASTTag_Operator_RightShift, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_TripleTriangleBracket_Close, 0, 5, OakASTTags :: kASTTag_Operator_LogicalRightShift, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	// 20
	{ OakTokenTags :: kTokenTag_TriangleBracket_Open, 0, 6, OakASTTags :: kASTTag_Operator_GreaterThan, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Close, 0, 6, OakASTTags :: kASTTag_Operator_LessThan, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Open_Equals, 0, 6, OakASTTags :: kASTTag_Operator_GreaterThanOrEqual, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_TriangleBracket_Close_Equals, 0, 6, OakASTTags :: kASTTag_Operator_LessThanOrEqual, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_ExclamationMark_Equals, 0, 7, OakASTTags :: kASTTag_Operator_NotEqual, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	// 25
	{ OakTokenTags :: kTokenTag_DoubleEquals, 0, 7, OakASTTags :: kASTTag_Operator_Equal, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Ampersand, 0, 8, OakASTTags :: kASTTag_Operator_BitwiseAnd, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Carrot, 0, 9, OakASTTags :: kASTTag_Operator_BitwiseXor, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_VerticalBar, 0, 10, OakASTTags :: kASTTag_Operator_BitwiseOr, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_DoubleAmpersand, 0, 11, OakASTTags :: kASTTag_Operator_LogicalAnd, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	// 30
	{ OakTokenTags :: kTokenTag_DoubleVerticalBar, 0, 12, OakASTTags :: kASTTag_Operator_LogicalOr, kOperatorAssociativity_Left_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_QuestionMark, 0, 13, OakASTTags :: kASTTag_Operator_Ternary, kOperatorAssociativity_Right_Double, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Colon, 0, 13, OakASTTags :: kASTTag_Operator_Ternary, kOperatorAssociativity_Right_Double, NULL, NULL, false },
	{ OakTokenTags :: kTokenTag_Equals, 0, 14, OakASTTags :: kASTTag_Operator_Assignment, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Star_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundMultiply, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	// 35
	{ OakTokenTags :: kTokenTag_Slash_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundDivide, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Percent_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundModulo, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Plus_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundAdd, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Minus_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundSubtract, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Open_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundLeftShift, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	// 40
	{ OakTokenTags :: kTokenTag_DoubleTriangleBracket_Close_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundRightShift, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_TripleTriangleBracket_Close_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundLogicalRightShift, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Ampersand_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseAnd, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_VerticalBar_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseOr, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_Carrot_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundBitwiseXor, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	// 45
	{ OakTokenTags :: kTokenTag_DoubleAmpersand_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundLogicalAnd, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	{ OakTokenTags :: kTokenTag_DoubleVerticalBar_Equals, 0, 14, OakASTTags :: kASTTag_Operator_CompoundLogicalOr, kOperatorAssociativity_Right_Binary, NULL, NULL, true },
	
};

bool _OakOperatorExpressionConstructor_FollowingOperatorRules [ 11 ][ 10 ] = 
{
	
	// <Following>                                                                         | <Previous>
	//-------------------------------------------------------------------------------------------------
	// U-L		U-L(P)	U-R		B-L		B-R		BR-L	BR-R	D-L		D-R		Primary    |
	{ true,		true,	false,	true,	true,	false,	true,	true,	true,	false	}, // U-L
	{ true,		true,	false,	true,	true,	true,	false,	true,	true,	false	}, // U-L(P)
	{ false,	false,	true,	false,	false,	false,	false,	false,	false,	true	}, // U-R
	{ false,	true,	true,	false,	false,	false,	true,	false,	false,	true	}, // B-L
	{ false,	true,	true,	false,	false,	false,	true,	false,	false,	true	}, // B-R
	{ false,	true,	false,	true,	true,	true,	false,	true,	true,	false	}, // BR-L
	{ false,	false,	true,	true,	false,	false,	true,	false,	false,	true	}, // BR-R
	{ false,	true,	true,	false,	false,	false,	true,	false,	false,	true	}, // D-L
	{ false,	true,	true,	false,	false,	false,	true,	false,	false,	true	}, // D-R
	{ true,		true,	false,	true,	true,	true,	false,	true,	true,	false	}, // Primary
	{ false,	false,	true,	false,	false,	false,	true,	false,	false,	true	} //  Initial
	
};

void _OakOperatorExpressionConstructor_FindOperator ( uint64_t TokenTag, const bool AllowedAssociativity [], const _OperatorEntry_t *& OperatorData )
{
	
	for ( uint32_t I = 0; I < ( sizeof ( _OakOperatorExpressionConstructor_OperatorList ) / sizeof ( _OperatorEntry_t ) ); I ++ )
	{
		
		if ( ! AllowedAssociativity [ _OakOperatorExpressionConstructor_OperatorList [ I ].Associativity ] )
			continue;
		
		if ( _OakOperatorExpressionConstructor_OperatorList [ I ].OperatorTag == TokenTag )
		{
			
			OperatorData = & _OakOperatorExpressionConstructor_OperatorList [ I ];
			
			return;
			
		}
		
	}
	
	OperatorData = NULL;
	
}

typedef struct
{
	
	bool Operator;
	
	union
	{
		
		struct
		{
			
			const _OperatorEntry_t * Operator;
			ASTElement * SpecialExpression;
			uint64_t SourceTokenIndex;
			uint64_t SourceTokenIndex2;
			
		} OperatorInfo;
		
		ASTElement * Primary;
		
	} Element;
	
} ExpressionElement;

void CleanupExpressionElements ( std :: vector <ExpressionElement> & ExpressionElements )
{
	
	for ( uint64_t I = 0; I < ExpressionElements.size (); I ++ )
	{
		
		if ( ! ExpressionElements [ I ].Operator )
			delete ExpressionElements [ I ].Element.Primary;
		else
			if ( ExpressionElements [ I ].Element.OperatorInfo.SpecialExpression != NULL )
				delete ExpressionElements [ I ].Element.OperatorInfo.SpecialExpression;
		
	}
	
}

ASTConstructionGroup :: StaticInitEntry _OakOperatorExpressionConstructor_PrimaryGroupEntries [] = { { & OakPrimaryExpressionConstructor :: Instance, 0 } };
ASTConstructionGroup :: StaticInitEntry _OakOperatorExpressionConstructor_ExpressionGroupEntries [] = { { & OakExpressionConstructor :: Instance, 0 } };

OakOperatorExpressionConstructor :: OakOperatorExpressionConstructor ():
	PrimaryGroup ( _OakOperatorExpressionConstructor_PrimaryGroupEntries, 1 ),
	ExpressionGroup ( _OakOperatorExpressionConstructor_ExpressionGroupEntries, 1 )
{
}

OakOperatorExpressionConstructor :: ~OakOperatorExpressionConstructor ()
{
}

void OakOperatorExpressionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount == 0 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount;
	
	std :: vector <ExpressionElement> ExpressionElements;
	
	const Token * CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	const _OperatorEntry_t * OperatorEntry = NULL;
	
	OperatorAssociativity LastAssociativity = kOperatorAssociativity_Initial;
	
	while ( true )
	{
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( TokenCount == 0 )
			break;
		
		_OakOperatorExpressionConstructor_FindOperator ( CurrentToken -> GetTag (), _OakOperatorExpressionConstructor_FollowingOperatorRules [ LastAssociativity ], OperatorEntry );
		
		if ( OperatorEntry != NULL )
		{
			
			const Token * OldCurrent = CurrentToken;
			
			ExpressionElement NewElement;
			
			NewElement.Operator = true;
			NewElement.Element.OperatorInfo.Operator = OperatorEntry;
			NewElement.Element.OperatorInfo.SpecialExpression = NULL;
			NewElement.Element.OperatorInfo.SourceTokenIndex = Input.AvailableTokenCount - TokenCount;
			
			if ( ( OperatorEntry -> Associativity == kOperatorAssociativity_Left_Bracket ) || ( OperatorEntry -> Associativity == kOperatorAssociativity_Right_Bracket ) )
			{
				
				bool Discard = false;
				
				if ( ExpressionElements.size () == 0 )
					Discard = true;
				else if ( ExpressionElements [ ExpressionElements.size () - 1 ].Operator && ( ExpressionElements [ ExpressionElements.size () - 1 ].Element.OperatorInfo.Operator -> Associativity != kOperatorAssociativity_Left_Unary_AsPrimary ) )
					Discard = true;
				
				if ( ! Discard )
				{
					
					ASTElement * SpecialExpressionElement = NULL;
					
					if ( OperatorEntry -> SpecialGroup != NULL )
					{
						
						SpecialExpressionElement = OperatorEntry -> SpecialGroup -> TryConstructSingleNoParent ( OakASTTags :: kASTTag_OperatorExpressionContainer, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
							
						if ( Error )
						{
							
							CleanupExpressionElements ( ExpressionElements );
							
							Output.Accepted = false;
							Output.Error = true;
							Output.ErrorSuggestion = ErrorString;
							Output.ErrorProvokingToken = ErrorToken;
							
							return;
							
						}
						
					}
					else
					{
						
						TokenCount --;
						
						SpecialExpressionElement = ExpressionGroup.TryConstructSingleNoParent ( OakASTTags :: kASTTag_OperatorExpressionContainer, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
						
						if ( Error )
						{
							
							CleanupExpressionElements ( ExpressionElements );
							
							Output.Accepted = false;
							Output.Error = true;
							Output.ErrorSuggestion = ErrorString;
							Output.ErrorProvokingToken = ErrorToken;
							
							return;
							
						}
						
						if ( TokenCount == 0 )
						{
							
							CleanupExpressionElements ( ExpressionElements );
							
							Output.Accepted = false;
							Output.Error = true;
							Output.ErrorSuggestion = "Expected matching closing bracket in operator";
							Output.ErrorProvokingToken = OldCurrent;
							
							return;
							
						}
						
						CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
						NewElement.Element.OperatorInfo.SourceTokenIndex2 = Input.AvailableTokenCount - TokenCount;
						
						TokenCount --;
						
						if ( CurrentToken -> GetTag () != OperatorEntry -> OperatorTag2 )
						{
							
							CleanupExpressionElements ( ExpressionElements );
							
							Output.Accepted = false;
							Output.Error = true;
							Output.ErrorSuggestion = "Expected matching closing bracket in bracket operator";
							Output.ErrorProvokingToken = OldCurrent;
							
							return;
							
						}
						
					}
					
					NewElement.Element.OperatorInfo.SpecialExpression = SpecialExpressionElement;
					
					ExpressionElements.push_back ( NewElement );
					
					LastAssociativity = OperatorEntry -> Associativity;
					
					continue;
					
				}
				
			}
			else if ( ( OperatorEntry -> Associativity == kOperatorAssociativity_Left_Double ) || ( OperatorEntry -> Associativity == kOperatorAssociativity_Right_Double ) )
			{
				
				bool Invalid = true;
				
				if ( ! OperatorEntry -> First )
				{
					
					for ( int64_t I = ExpressionElements.size () - 1; I >= 0; I -- )
					{
						
						if ( ExpressionElements [ I ].Operator )
						{
							
							if ( ( ExpressionElements [ I ].Element.OperatorInfo.Operator -> Associativity == kOperatorAssociativity_Left_Double ) || ( ExpressionElements [ I ].Element.OperatorInfo.Operator -> Associativity == kOperatorAssociativity_Right_Double ) )
							{
								
								if ( ( ExpressionElements [ I ].Element.OperatorInfo.Operator -> Associativity != OperatorEntry -> Associativity ) || ( ! ExpressionElements [ I ].Element.OperatorInfo.Operator -> First ) )
								{
									
									Invalid = false;
									
									break;
									
								}
								else
									break;
								
							}
							
						}
						
					}
					
				}
				
				if ( ! Invalid )
				{
					
					TokenCount --;
					
					ExpressionElements.push_back ( NewElement );
					
					LastAssociativity = OperatorEntry -> Associativity;
					
					continue;
					
				}
				
			}
			else
			{
				
				TokenCount --;
				
				ASTElement * SpecialExpressionElement = NULL;
				
				if ( OperatorEntry -> SpecialGroup != NULL )
				{
					
					SpecialExpressionElement = OperatorEntry -> SpecialGroup -> TryConstructSingleNoParent ( OakASTTags :: kASTTag_OperatorExpressionContainer, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
					
					if ( Error )
					{
						
						CleanupExpressionElements ( ExpressionElements );
						
						Output.Accepted = false;
						Output.Error = true;
						Output.ErrorSuggestion = ErrorString;
						Output.ErrorProvokingToken = ErrorToken;
						
						return;
						
					}
					
				}
				
				NewElement.Element.OperatorInfo.SpecialExpression = SpecialExpressionElement;
				
				ExpressionElements.push_back ( NewElement );
				
				LastAssociativity = OperatorEntry -> Associativity;
				
				continue;
				
			}
			
		}
		
		if ( ! _OakOperatorExpressionConstructor_FollowingOperatorRules [ LastAssociativity ] [ kOperatorAssociativity_PrimaryExpression ] )
			break;
		
		ASTElement * PrimaryElement = PrimaryGroup.TryConstructSingleNoParent ( OakASTTags :: kASTTag_OperatorExpressionContainer, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
		
		if ( PrimaryElement != NULL )
		{
			
			ExpressionElement NewElement;
			
			NewElement.Operator = false;
			NewElement.Element.Primary = PrimaryElement;
			
			LastAssociativity = kOperatorAssociativity_PrimaryExpression;
			
			ExpressionElements.push_back ( NewElement );
			
			continue;
			
		}
		else
		{
			
			if ( Error )
			{
				
				CleanupExpressionElements ( ExpressionElements );
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = ErrorString;
				Output.ErrorProvokingToken = ErrorToken;
				
				return;
				
			}
			
		}
		
		break;
		
	}
	
	if ( ExpressionElements.size () == 0 )
	{
		
		CleanupExpressionElements ( ExpressionElements );
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( ExpressionElements.size () == 1 )
	{
		
		if ( ExpressionElements [ 0 ].Operator )
		{
			
			CleanupExpressionElements ( ExpressionElements );
			
			Output.Accepted = false;
			
			return;
			
		}
		
		Output.Accepted = true;
		Output.ConstructedElement = ExpressionElements [ 0 ].Element.Primary;
		Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
		
		return;
		
	}
	
	while ( ExpressionElements.size () != 1 )
	{
		
		uint32_t LowestPrecedence = 0xFFFFFFFF;
		uint64_t LowestPrecedenceIndex = 0;
		const _OperatorEntry_t * LowestPrecedenceOperator = NULL;
		
		int32_t I;
		
		for ( I = 0; I < static_cast <int32_t> ( ExpressionElements.size () ); I ++ )
		{
			
			if ( ExpressionElements [ I ].Operator )
			{
				
				if ( ( ExpressionElements [ I ].Element.OperatorInfo.Operator -> Precedence < LowestPrecedence ) && _OakOperatorExpressionConstructor_AssociativityIsLeft ( ExpressionElements [ I ].Element.OperatorInfo.Operator -> Associativity ) )
				{
					
					LowestPrecedenceIndex = I;
					LowestPrecedence = ExpressionElements [ I ].Element.OperatorInfo.Operator -> Precedence;
					LowestPrecedenceOperator = ExpressionElements [ I ].Element.OperatorInfo.Operator;
					
				}
				
			}
			
		}
		
		for ( I = ExpressionElements.size () - 1; I >= 0; I -- )
		{
			
			if ( ExpressionElements [ I ].Operator )
			{
				
				if ( ( ExpressionElements [ I ].Element.OperatorInfo.Operator -> Precedence < LowestPrecedence ) && ! _OakOperatorExpressionConstructor_AssociativityIsLeft ( ExpressionElements [ I ].Element.OperatorInfo.Operator -> Associativity ) )
				{
					
					LowestPrecedenceIndex = I;
					LowestPrecedence = ExpressionElements [ I ].Element.OperatorInfo.Operator -> Precedence;
					LowestPrecedenceOperator = ExpressionElements [ I ].Element.OperatorInfo.Operator;
					
				}
				
			}
			
		}
		
		if ( LowestPrecedenceOperator == NULL )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected operator between primaries in expression";
			Output.ErrorProvokingToken = Input.Tokens [ 0 ];
			
			CleanupExpressionElements ( ExpressionElements );
			
			return;
			
		}
		
		ExpressionElement & Current = ExpressionElements [ LowestPrecedenceIndex ];
		
		switch ( LowestPrecedenceOperator -> Associativity )
		{
			
			case kOperatorAssociativity_Left_Unary_AsPrimary:
			case kOperatorAssociativity_Left_Unary:
			{
				
				if ( LowestPrecedenceIndex == 0 )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted unary left-associative operator after operator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					if ( Current.Element.OperatorInfo.SpecialExpression != NULL )
						delete Current.Element.OperatorInfo.SpecialExpression;
					
					Current.Element.OperatorInfo.SpecialExpression = NULL;
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ExpressionElement & Previous = ExpressionElements [ LowestPrecedenceIndex - 1 ];
				
				if ( Previous.Operator )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted unary left-associative operator after operator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Previous.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					if ( Current.Element.OperatorInfo.SpecialExpression != NULL )
						delete Current.Element.OperatorInfo.SpecialExpression;
					
					Current.Element.OperatorInfo.SpecialExpression = NULL;
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ASTElement * OperationElement = new ASTElement ();
				
				OperationElement -> SetTag ( LowestPrecedenceOperator -> ASTTag );
				OperationElement -> AddTokenSection ( & Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ], 1 );
				OperationElement -> AddSubElement ( Previous.Element.Primary );
				OperationElement -> AddSubElement ( Current.Element.OperatorInfo.SpecialExpression );
				
				ExpressionElements [ LowestPrecedenceIndex - 1 ].Operator = false;
				ExpressionElements [ LowestPrecedenceIndex - 1 ].Element.Primary = OperationElement;
				ExpressionElements.erase ( ExpressionElements.begin () + LowestPrecedenceIndex );
				
			}
			break;
			
			case kOperatorAssociativity_Right_Unary:
			{
				
				if ( LowestPrecedenceIndex == ExpressionElements.size () - 1 )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted unary right-associative operator at end of expression";
						Output.ErrorProvokingToken = Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				if ( LowestPrecedenceIndex != 0 )
				{
					
					ExpressionElement & Previous = ExpressionElements [ LowestPrecedenceIndex - 1 ];
					
					if ( ! Previous.Operator )
					{
						
						if ( LowestPrecedenceOperator -> FailureMutation == NULL )
						{
							
							CleanupExpressionElements ( ExpressionElements );
						
							Output.Error = true;
							Output.Accepted = false;
							Output.ErrorSuggestion = "Unexpexted unary right-associative operator after expression";
							Output.ErrorProvokingToken = Input.Tokens [ Previous.Element.OperatorInfo.SourceTokenIndex ];
							
							return;
							
						}
						
						Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
						
						break;
						
					}
					
				}
				
				ExpressionElement & Next = ExpressionElements [ LowestPrecedenceIndex + 1 ];
				
				if ( Next.Operator )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted unary right-associative operator before operator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Next.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ASTElement * OperationElement = new ASTElement ();
				
				OperationElement -> SetTag ( LowestPrecedenceOperator -> ASTTag );
				OperationElement -> AddTokenSection ( & Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ], 1 );
				OperationElement -> AddSubElement ( Next.Element.Primary );
				OperationElement -> AddSubElement ( Current.Element.OperatorInfo.SpecialExpression );
				
				ExpressionElements [ LowestPrecedenceIndex ].Element.Primary = OperationElement;
				ExpressionElements [ LowestPrecedenceIndex ].Operator = false;
				ExpressionElements.erase ( ExpressionElements.begin () + LowestPrecedenceIndex + 1 );
				
			}
			break;
			
			case kOperatorAssociativity_Left_Binary:
			{
				
				if ( LowestPrecedenceIndex == ExpressionElements.size () - 1 )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted binary left-associative operator at end of expression";
						Output.ErrorProvokingToken = Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				if ( LowestPrecedenceIndex == 0 )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted binary left-associative operator at beginning of expression";
						Output.ErrorProvokingToken = Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ExpressionElement & Current = ExpressionElements [ LowestPrecedenceIndex ];
				ExpressionElement & Previous = ExpressionElements [ LowestPrecedenceIndex - 1 ];
				ExpressionElement & Next = ExpressionElements [ LowestPrecedenceIndex + 1 ];
				
				if ( Next.Operator )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted operator after left-associative operator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Next.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				if ( Previous.Operator )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted operator before left-associative operator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Next.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ASTElement * OperationElement = new ASTElement ();
				
				OperationElement -> SetTag ( LowestPrecedenceOperator -> ASTTag );
				OperationElement -> AddTokenSection ( & Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ], 1 );
				OperationElement -> AddSubElement ( Previous.Element.Primary );
				OperationElement -> AddSubElement ( Next.Element.Primary );
				
				ExpressionElements [ LowestPrecedenceIndex - 1 ].Element.Primary = OperationElement;
				ExpressionElements.erase ( ExpressionElements.begin () + LowestPrecedenceIndex, ExpressionElements.begin () + LowestPrecedenceIndex + 2 );
				
			}
			break;
			
			case kOperatorAssociativity_Right_Binary:
			{
				
				if ( LowestPrecedenceIndex == ExpressionElements.size () - 1 )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted binary right-associative operator at end of expression";
						Output.ErrorProvokingToken = Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				if ( LowestPrecedenceIndex == 0 )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted binary right-associative operator at beginning of expression";
						Output.ErrorProvokingToken = Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ExpressionElement & Current = ExpressionElements [ LowestPrecedenceIndex ];
				ExpressionElement & Previous = ExpressionElements [ LowestPrecedenceIndex - 1 ];
				ExpressionElement & Next = ExpressionElements [ LowestPrecedenceIndex + 1 ];
				
				if ( Next.Operator )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted operator after right-associative operator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Next.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				if ( Previous.Operator )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted operator before right-associative operator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Next.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ASTElement * OperationElement = new ASTElement ();
				
				OperationElement -> SetTag ( LowestPrecedenceOperator -> ASTTag );
				OperationElement -> AddTokenSection ( & Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ], 1 );
				OperationElement -> AddSubElement ( Previous.Element.Primary );
				OperationElement -> AddSubElement ( Next.Element.Primary );
				
				ExpressionElements [ LowestPrecedenceIndex - 1 ].Element.Primary = OperationElement;
				ExpressionElements.erase ( ExpressionElements.begin () + LowestPrecedenceIndex, ExpressionElements.begin () + LowestPrecedenceIndex + 2 );
				
			}
			break;
			
			case kOperatorAssociativity_Left_Bracket:
			{
				
				if ( LowestPrecedenceIndex == 0 )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted unary left-associative bracket operator after ooperator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ExpressionElement & Previous = ExpressionElements [ LowestPrecedenceIndex - 1 ];
				
				if ( Previous.Operator )
				{
					
					if ( LowestPrecedenceOperator -> FailureMutation == NULL )
					{
						
						CleanupExpressionElements ( ExpressionElements );
					
						Output.Error = true;
						Output.Accepted = false;
						Output.ErrorSuggestion = "Unexpexted unary left-associative bracket operator after ooperator in expression";
						Output.ErrorProvokingToken = Input.Tokens [ Previous.Element.OperatorInfo.SourceTokenIndex ];
						
						return;
						
					}
					
					Current.Element.OperatorInfo.Operator = LowestPrecedenceOperator -> FailureMutation;
					
					break;
					
				}
				
				ASTElement * OperationElement = new ASTElement ();
				
				OperationElement -> SetTag ( LowestPrecedenceOperator -> ASTTag );
				OperationElement -> AddTokenSection ( & Input.Tokens [ Current.Element.OperatorInfo.SourceTokenIndex ], 1 );
				OperationElement -> AddSubElement ( Previous.Element.Primary );
				OperationElement -> AddSubElement ( Current.Element.OperatorInfo.SpecialExpression );
				
				ExpressionElements [ LowestPrecedenceIndex - 1 ].Element.Primary = OperationElement;
				ExpressionElements.erase ( ExpressionElements.begin () + LowestPrecedenceIndex );
				
			}
			break;
			
			// None of these exist yet, so...
			case kOperatorAssociativity_Right_Bracket: break;
			case kOperatorAssociativity_Left_Double: break;
			
			case kOperatorAssociativity_Right_Double:
			{
				
				// TODO: Finish
				
			}
			break;
			
			default:
			break;
			
		}
		
	}
	
	ASTElement * OperatorExpressionElement = new ASTElement ();
	
	OperatorExpressionElement -> SetTag ( OakASTTags :: kASTTag_OperatorExpressionContainer );
	OperatorExpressionElement -> AddSubElement ( ExpressionElements [ 0 ].Element.Primary );
	
	Output.Accepted = true;
	Output.ConstructedElement = OperatorExpressionElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
