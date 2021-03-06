#include <Parsing/Language/OakFunctionDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakFunctionParameterListConstructor.h>
#include <Parsing/Language/OakReturnTypeConstructor.h>
#include <Parsing/Language/OakStatementBlockConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Utils/GlobalSingleton.h>

OakFunctionDefinitionConstructor & OakFunctionDefinitionConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakFunctionDefinitionConstructor> ();
	
}

OakFunctionDefinitionConstructor :: OakFunctionDefinitionConstructor ():
	TemplateConstructionGroup ( { { & ( OakTemplateDefinitionConstructor :: Instance () ), 0 } } ),
	ParameterListConstructionGroup ( { { & ( OakFunctionParameterListConstructor :: Instance () ), 0 } } ),
	ReturnTypeConstructionGroup ( { { & ( OakReturnTypeConstructor :: Instance () ), 0 } } ),
	BodyConstructionGroup ( { { & ( OakStatementBlockConstructor :: Instance () ), 0 } } )
{
}

OakFunctionDefinitionConstructor :: ~OakFunctionDefinitionConstructor ()
{
}

void OakFunctionDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 5 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	uint64_t Offset = 0;
	
	bool Public = false;
	bool Inline = false;
	
	const Token * CurrentToken = Input.Tokens [ Offset ];
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Public ) )
	{
		
		Public = true;
		
		Offset ++;
		
		CurrentToken = Input.Tokens [ Offset ];
		
	}
	
	if ( OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Inline ) )
	{
		
		Inline = true;
		
		Offset ++;
		
		CurrentToken = Input.Tokens [ Offset ];
		
	}
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Function ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	Offset ++;
	
	CurrentToken = Input.Tokens [ Offset ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier for function name";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	Offset ++;
	
	ElementData * FunctionData = new ElementData ();
	
	FunctionData -> Name = CurrentToken -> GetSource ();
	FunctionData -> Inline = Inline;
	FunctionData -> Public = Public;
	FunctionData -> Templated = false;
	FunctionData -> ReturnTyped = false;
	
	ASTElement * FunctionElement = new ASTElement ();
	
	FunctionElement -> SetTag ( OakASTTags :: kASTTag_FunctionDefinition );
	FunctionElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	FunctionElement -> SetData ( FunctionData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	
	if ( TemplateConstructionGroup.TryConstruction ( FunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Offset ], TokenCount ) != 0 )
	{
		
		if ( Error )
		{
			
			delete FunctionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		FunctionData -> Templated = true;
		
		ASTElement * TemplateElement = FunctionElement -> GetSubElement ( FunctionElement -> GetSubElementCount () - 1 );
		
		if ( reinterpret_cast <OakTemplateDefinitionConstructor :: ElementData *> ( TemplateElement -> GetData () ) -> DoubleTemplateClose )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Unexpected closing triangle bracket after end of template definition";
			Output.ErrorProvokingToken = TemplateElement -> GetToken ( TemplateElement -> GetTokenSectionCount () - 1, TemplateElement -> GetTokenCount ( TemplateElement -> GetTokenSectionCount () - 1 ) - 1 );
			
			delete FunctionElement;
			
			return;
			
		}
		
		if ( TokenCount < 3 )
		{
			
			delete FunctionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected body for function definition";
			Output.ErrorProvokingToken = NULL;
			
			return;
			
		}
		
	}
	
	if ( Error )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( ParameterListConstructionGroup.TryConstruction ( FunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( Error )
		{
			
			delete FunctionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected function paremeter list or empty brackets";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	else if ( Error )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	if ( ReturnTypeConstructionGroup.TryConstruction ( FunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
		FunctionData -> ReturnTyped = true;
	
	if ( Error )
	{
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Error = false;
	ErrorString = "";
	ErrorToken = NULL;
	
	if ( BodyConstructionGroup.TryConstruction ( FunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		
		if ( Error )
		{
			
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		Output.ErrorSuggestion = "Expected body for method";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = FunctionElement;
	
}

void OakFunctionDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
