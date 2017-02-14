#include <Parsing/Language/OakBindingStatementConstructor.h>
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

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakBindingStatementConstructor OakBindingStatementConstructor :: Instance;

OakBindingStatementConstructor :: OakBindingStatementConstructor ():
	TypeGroup (),
	InitializerValueGroup ()
{
	
	TypeGroup.AddConstructorCantidate ( & OakPointerTypeConstructor :: Instance, 0 );
	TypeGroup.AddConstructorCantidate ( & OakReferenceTypeConstructor :: Instance, 0 );
	
	TypeGroup.AddConstructorCantidate ( & OakNamespacedTemplatedTypeNameConstructor :: Instance, 0 );
	TypeGroup.AddConstructorCantidate ( & OakNamespacedTypeNameConstructor :: Instance, 1 );
	TypeGroup.AddConstructorCantidate ( & OakTemplatedTypeNameConstructor :: Instance, 1 );
	TypeGroup.AddConstructorCantidate ( & OakBareTypeNameConstructor :: Instance, 2 );
	
	InitializerValueGroup.AddConstructorCantidate ( & OakExpressionConstructor :: Instance, 0 );
	
}

OakBindingStatementConstructor :: ~OakBindingStatementConstructor ()
{
	
	
	
}

void OakBindingStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 5 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	uint64_t Offset = 0;
	bool Mutable = false;
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Bind ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Offset ++;
	
	CurrentToken = Input.Tokens [ Offset ];
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Mut ) )
	{
		
		Offset ++;
		
		Mutable = true;
		
		CurrentToken = Input.Tokens [ Offset ];
		
	}
	
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
	
	ElementData * BindingData = new ElementData ();
	
	BindingData -> Name = Input.Tokens [ Mutable ? 2 : 1 ] -> GetSource ();
	BindingData -> Initialized = false;
	BindingData -> Mutable = Mutable;
	
	ASTElement * BindingElement = new ASTElement ();
	
	BindingElement -> SetTag ( OakASTTags :: kASTTag_StructBinding );
	BindingElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	BindingElement -> SetData ( BindingData, & ElementDataDestructor );
	
	bool ConstructionError = false;
	uint64_t TokenCount = Input.AvailableTokenCount - 3;
	const Token * ErrorToken = NULL;
	std :: string ErrorString;
	
	if ( TypeGroup.TryConstruction ( BindingElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete BindingElement;
		
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
		Output.ErrorSuggestion = "Expected type name after colon in struct binding";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	if ( ConstructionError )
	{
		
		delete BindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete BindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon or assignment after variable binding statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () == OakTokenTags :: kTokenTag_Semicolon )
	{
		
		BindingData -> Initialized = false;
		
		BindingElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
		
		Output.Accepted = true;
		Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
		Output.ConstructedElement = BindingElement;
		
		return;
		
	}
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Equals )
	{
		
		delete BindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon or assignment after variable binding statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	BindingData -> Initialized = true;
	
	TokenCount --;
	
	if ( InitializerValueGroup.TryConstruction ( BindingElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete BindingElement;
		
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
		
		delete BindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( TokenCount == 0 )
	{
		
		delete BindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon after variable binding statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		delete BindingElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon after variable binding statement";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	BindingElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = BindingElement;
	
}

void OakBindingStatementConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
