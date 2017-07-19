#include <Parsing/Language/OakConstStatementConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakReferenceTypeConstructor.h>

#include <Parsing/Language/OakBareTypeNameConstructor.h>
#include <Parsing/Language/OakTemplatedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTypeNameConstructor.h>
#include <Parsing/Language/OakNamespacedTemplatedTypeNameConstructor.h>

#include <Parsing/Language/OakVoidTypeConstructor.h>

#include <Parsing/Language/OakExpressionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakConstStatementConstructor & OakConstStatementConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakConstStatementConstructor> ();
	
}

OakConstStatementConstructor :: OakConstStatementConstructor ():
	TypeGroup ( 
	{
		
		{ & ( OakReferenceTypeConstructor :: Instance () ), 0 },
		
		{ & ( OakNamespacedTemplatedTypeNameConstructor :: Instance () ), 0 },
		{ & ( OakNamespacedTypeNameConstructor :: Instance () ), 1 },
		{ & ( OakTemplatedTypeNameConstructor :: Instance () ), 1 },
		{ & ( OakBareTypeNameConstructor :: Instance () ), 2 },
		
		{ & ( OakVoidTypeConstructor :: Instance () ), 2 },
		
	} ),
	InitializerValueGroup ( { { & ( OakExpressionConstructor :: Instance () ), 0 } } )
{
}

OakConstStatementConstructor :: ~OakConstStatementConstructor ()
{
}

void OakConstStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 5 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	uint64_t Offset = 0;
	bool Public;
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Const ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Offset ++;
	
	CurrentToken = Input.Tokens [ Offset ];
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Public ) )
	{
		
		Offset ++;
		
		Public = true;
		
		CurrentToken = Input.Tokens [ Offset ];
		
	}
	
	CurrentToken = Input.Tokens [ Offset ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Offset ++;
	
	CurrentToken = Input.Tokens [ Offset ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Colon )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Offset ++;
	
	ElementData * ConstData = new ElementData ();
	
	ConstData -> Name = Input.Tokens [ Offset - 2 ] -> GetSource ();
	ConstData -> Public = Public;
	
	ASTElement * ConstElement = new ASTElement ();
	
	ConstElement -> SetTag ( OakASTTags :: kASTTag_ConstStatement );
	ConstElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	ConstElement -> SetData ( ConstData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( ConstElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete ConstElement;
		
		if ( ConstructionError )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected type name after colon in constant";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ConstElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete ConstElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected assignment after const statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Equals )
	{
		
		delete ConstElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected assignment after const statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	TokenCount --;
	
	if ( InitializerValueGroup.TryConstruction ( ConstElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete ConstElement;
		
		if ( ConstructionError )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected expression after assignment operator in struct binding";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete ConstElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete ConstElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon after const statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		delete ConstElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon after const statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ConstElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = ConstElement;
	
}

void OakConstStatementConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
