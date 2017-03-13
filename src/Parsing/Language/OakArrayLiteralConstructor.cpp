#include <Parsing/Language/OakArrayLiteralConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakPointerTypeConstructor.h>
#include <Parsing/Language/OakReferenceTypeConstructor.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakExpressionConstructor.h>

#include <Parsing/Language/OakLiteralExpressionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakArrayLiteralConstructor OakArrayLiteralConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakArrayLiteralConstructor_TypeGroupEntries [] =
{
	
	{ & OakPointerTypeConstructor :: Instance, 0 },
	{ & OakReferenceTypeConstructor :: Instance, 0 },
	
	{ & OakNamespacedTemplatedTypeNameConstructor :: Instance, 0 },
	{ & OakNamespacedTypeNameConstructor :: Instance, 1 },
	{ & OakTemplatedTypeNameConstructor :: Instance, 1 },
	{ & OakBareTypeNameConstructor :: Instance, 2 },
	
};

ASTConstructionGroup :: StaticInitEntry _OakArrayLiteralConstructor_ExpressionGroupEntries [] =
{
	
	{ & OakExpressionConstructor :: Instance, 0 }
	
};

ASTConstructionGroup :: StaticInitEntry _OakArrayLiteralConstructor_UnsignedIntegerGroupEntries [] =
{
	
	{ & OakLiteralExpressionConstructor :: Instance, 0 }
	
};

OakArrayLiteralConstructor :: OakArrayLiteralConstructor ():
	TypeGroup ( _OakArrayLiteralConstructor_TypeGroupEntries, 6 ),
	ExpressionGroup ( _OakArrayLiteralConstructor_ExpressionGroupEntries, 1 )
{
}

OakArrayLiteralConstructor :: ~OakArrayLiteralConstructor ()
{
}

void OakArrayLiteralConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 2 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_SquareBracket_Open )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	bool InitialCountSpecified = false;
	
	ElementData * LiteralData = new ElementData ();
	
	LiteralData -> ExplicitType = false;
	LiteralData -> ExplicitCount = false;
	
	ASTElement * LiteralElement = new ASTElement ();
	
	LiteralElement -> SetTag ( OakASTTags :: kASTTag_ArrayLiteral );
	LiteralElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	LiteralElement -> SetData ( LiteralData, & ElementDataDestructor );
	
	bool Error = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( ExpressionGroup.TryConstruction ( LiteralElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( Error )
		{
			
			delete LiteralData;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
	
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_SquareBracket_Close )
		{
			
			Output.Accepted = true;
			Output.ConstructedElement = LiteralElement;
			Output.TokensConsumed = 2;
			
			return;
			
		}
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Unexpected token in array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
				
		}
		
	}
	else
		InitialCountSpecified = true;
	
	if ( TokenCount == 0 )
	{
		
		delete LiteralElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "expected closing square bracket in array literal";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Colon )
	{
		
		LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		TokenCount --;
		
		LiteralData -> ExplicitCount = InitialCountSpecified;
		LiteralData -> ExplicitType = true;
		
		if ( TypeGroup.TryConstruction ( LiteralElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
		{
			
			if ( Error )
			{
				
				delete LiteralData;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = ErrorString;
				Output.ErrorProvokingToken = ErrorToken;
				
				return;
				
			}
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected type name after colon in explicitly typed array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected semicolon after type name in explicitly typed array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected semicolon after type name in explicitly typed array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		TokenCount --;
		
	}
	else if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Semicolon )
	{
		
		LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		TokenCount --;
		
		LiteralData -> ExplicitCount = true;
		
	}
	else
	{
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_SquareBracket_Close )
		{
			
			LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			TokenCount --;
			
			Output.Accepted = true;
			Output.ConstructedElement = LiteralElement;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			
			return;
			
		}
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected comma or closing square bracket after element value in array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		TokenCount --;
		
	}
	
	while ( TokenCount != 0 )
	{
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_SquareBracket_Close )
		{
			
			LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			TokenCount --;
			
			Output.Accepted = true;
			Output.ConstructedElement = LiteralElement;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			
			return;
			
		}
		
		if ( ExpressionGroup.TryConstruction ( LiteralElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
		{
			
			if ( Error )
			{
				
				delete LiteralData;
				
				Output.Accepted = false;
				Output.Error = true;
				Output.ErrorSuggestion = ErrorString;
				Output.ErrorProvokingToken = ErrorToken;
				
				return;
				
			}
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected value or closing square bracket after comma in array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing square bracket at end of array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_SquareBracket_Close )
		{
			
			LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
			TokenCount --;
			
			Output.Accepted = true;
			Output.ConstructedElement = LiteralElement;
			Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
			
			return;
			
		}
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected comma or closing square bracket after element value in array literal";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		TokenCount --;
		
	}
	
	delete LiteralElement;
	
	Output.Accepted = false;
	Output.Error = true;
	Output.ErrorSuggestion = "Expected closing square bracket at end of array literal";
	Output.ErrorProvokingToken = CurrentToken;
	
}

void OakArrayLiteralConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
