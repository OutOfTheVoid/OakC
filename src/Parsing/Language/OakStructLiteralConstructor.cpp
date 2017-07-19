#include <Parsing/Language/OakStructLiteralConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakStructLiteralMemberValueConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakStructLiteralConstructor & OakStructLiteralConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakStructLiteralConstructor> ();
	
}

OakStructLiteralConstructor :: OakStructLiteralConstructor ():
	StructTypeGroup ( 
	{
		
		{ & ( OakNamespacedTemplatedTypeNameConstructor :: Instance () ), 0 },
		{ & ( OakNamespacedTypeNameConstructor :: Instance () ), 1 },
		{ & ( OakTemplatedTypeNameConstructor :: Instance () ), 1 },
		{ & ( OakBareTypeNameConstructor :: Instance () ), 2 },
		
	} ),
	MemberValueGroup ( { { & ( OakStructLiteralMemberValueConstructor :: Instance () ), 0 } } )
{
}

OakStructLiteralConstructor :: ~OakStructLiteralConstructor ()
{
}

void OakStructLiteralConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * LiteralElement = new ASTElement ();
	
	LiteralElement -> SetTag ( OakASTTags :: kASTTag_StructLiteral );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount;
	
	if ( StructTypeGroup.TryConstruction ( LiteralElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 0 ], TokenCount ) == 0 )
	{
		
		delete LiteralElement;
		
		if ( Error )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		Output.Accepted = false;
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete LiteralElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount < 3 )
	{
		
		delete LiteralElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for struct literal";
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		delete LiteralElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected colon after type in struct literal";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	TokenCount --;
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		delete LiteralElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected open curly bracket after colon in struct literal";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount - 1 ], 2 );
	
	TokenCount --;
	
	while ( MemberValueGroup.TryConstruction ( LiteralElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		if ( Error )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete LiteralElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing curly bracket at end of struct literal";
			Output.ErrorProvokingToken = NULL;
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
			break;
		
		LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		TokenCount --;
		
	}
	
	if ( Error )
	{
		
		delete LiteralElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete LiteralElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of struct literal";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	LiteralElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = LiteralElement;
	
}



