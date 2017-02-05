#include <Parsing/Language/OakFunctionDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakFunctionParameterListConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

OakTemplateDefinitionConstructor _OakFunctionDefinitionConstructor_OakTemplateDefinitionConstructorInstance;
OakFunctionParameterListConstructor _OakFunctionDefinitionConstructor_OakFunctionParameterListConstructorInstance;

OakFunctionDefinitionConstructor :: OakFunctionDefinitionConstructor ():
	TemplateConstructionGroup (),
	ParameterListConstructionGroup (),
	FunctionBodyConstructionGroup ()
{
	
	TemplateConstructionGroup.AddConstructorCantidate ( & _OakFunctionDefinitionConstructor_OakTemplateDefinitionConstructorInstance, 0 );
	ParameterListConstructionGroup.AddConstructorCantidate ( & _OakFunctionDefinitionConstructor_OakFunctionParameterListConstructorInstance, 0 );
	
}

OakFunctionDefinitionConstructor :: ~OakFunctionDefinitionConstructor ()
{
}

void OakFunctionDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 6 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Function ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier for function name";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ElementData * FunctionData = new ElementData ();
	
	FunctionData -> Name = CurrentToken -> GetSource ();
	FunctionData -> Templated = false;
	
	ASTElement * FunctionElement = new ASTElement ();
	
	FunctionElement -> SetTag ( OakASTTags :: kASTTag_FunctionDefinition );
	FunctionElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	FunctionElement -> SetData ( FunctionData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( TemplateConstructionGroup.TryConstruction ( FunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 2 ], TokenCount ) != 0 )
	{
		
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
		
		if ( TokenCount < 2 )
		{
			
			delete FunctionElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected body for function definition";
			Output.ErrorProvokingToken = NULL;
			
			return;
			
		}
		
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
	
	if ( ParameterListConstructionGroup.TryConstruction ( FunctionElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 2 ], TokenCount ) == 0 )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
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
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for function definition";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	FunctionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Error = false;
	ErrorString = "";
	ErrorToken = NULL;
	
	FunctionBodyConstructionGroup.TryConstruction ( FunctionElement, 0xFFFFFFFFFFFFFFFF, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount );
	
	if ( Error )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete FunctionElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of function body";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	FunctionElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = FunctionElement;
	
}

void OakFunctionDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
