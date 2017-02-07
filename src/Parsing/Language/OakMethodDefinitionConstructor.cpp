#include <Parsing/Language/OakMethodDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakMethodParameterListConstructor.h>
#include <Parsing/Language/OakReturnTypeConstructor.h>
#include <Parsing/Language/OakStatementBlockConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakTemplateDefinitionConstructor _OakMethodDefinitionConstructor_OakTemplateDefinitionConstructorInstance;
OakMethodParameterListConstructor _OakMethodDefinitionConstructor_OakMethodParameterListConstructorInstance;
OakReturnTypeConstructor _OakMethodDefinitionConstructor_OakReturnTypeConstructorInstance;
OakStatementBlockConstructor _OakMethodDefinitionConstructor_OakStatementBlockConstructorInstance;

OakMethodDefinitionConstructor :: OakMethodDefinitionConstructor ():
	TemplateConstructionGroup (),
	ParameterListConstructionGroup (),
	ReturnTypeConstructionGroup (),
	BodyConstructionGroup ()
{
	
	TemplateConstructionGroup.AddConstructorCantidate ( & _OakMethodDefinitionConstructor_OakTemplateDefinitionConstructorInstance, 0 );
	ParameterListConstructionGroup.AddConstructorCantidate ( & _OakMethodDefinitionConstructor_OakMethodParameterListConstructorInstance, 0 );
	ReturnTypeConstructionGroup.AddConstructorCantidate ( & _OakMethodDefinitionConstructor_OakReturnTypeConstructorInstance, 0 );
	BodyConstructionGroup.AddConstructorCantidate ( & _OakMethodDefinitionConstructor_OakStatementBlockConstructorInstance, 0 );
	
}

OakMethodDefinitionConstructor :: ~OakMethodDefinitionConstructor ()
{
}

void OakMethodDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	LOG_VERBOSE ( "+A" );
	
	if ( Input.AvailableTokenCount < 6 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	LOG_VERBOSE ( "+B" );
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Function ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	LOG_VERBOSE ( "+C" );
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier for function name";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	LOG_VERBOSE ( "+D" );
	
	ElementData * MethodData = new ElementData ();
	
	MethodData -> Name = CurrentToken -> GetSource ();
	MethodData -> Templated = false;
	MethodData -> ReturnTyped = false;
	
	ASTElement * MethodElement = new ASTElement ();
	
	MethodElement -> SetTag ( OakASTTags :: kASTTag_MethodDefinition );
	MethodElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	MethodElement -> SetData ( MethodData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( TemplateConstructionGroup.TryConstruction ( MethodElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 2 ], TokenCount ) != 0 )
	{
		
		LOG_VERBOSE ( "+D_A" );
		
		MethodData -> Templated = true;
		
		ASTElement * TemplateElement = MethodElement -> GetSubElement ( MethodElement -> GetSubElementCount () - 1 );
		
		if ( reinterpret_cast <OakTemplateDefinitionConstructor :: ElementData *> ( TemplateElement -> GetData () ) -> DoubleTemplateClose )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Unexpected closing triangle bracket after end of template definition";
			Output.ErrorProvokingToken = TemplateElement -> GetToken ( TemplateElement -> GetTokenSectionCount () - 1, TemplateElement -> GetTokenCount ( TemplateElement -> GetTokenSectionCount () - 1 ) - 1 );
			
			delete MethodElement;
			
			return;
			
		}
		
		LOG_VERBOSE ( "+D_B" );
		
		if ( TokenCount < 2 )
		{
			
			delete MethodElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected body for method definition";
			Output.ErrorProvokingToken = NULL;
			
			return;
			
		}
		
		LOG_VERBOSE ( "+D_C" );
		
	}
	else if ( Error )
	{
		
		delete MethodElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	LOG_VERBOSE ( "+E" );
	
	if ( ParameterListConstructionGroup.TryConstruction ( MethodElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete MethodElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	else if ( Error )
	{
		
		delete MethodElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	LOG_VERBOSE ( "+F" );
	
	if ( ReturnTypeConstructionGroup.TryConstruction ( MethodElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
		MethodData -> ReturnTyped = true;
	
	if ( Error )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Error = false;
	ErrorString = "";
	ErrorToken = NULL;
	
	LOG_VERBOSE ( "+G" );
	
	if ( BodyConstructionGroup.TryConstruction ( MethodElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		delete MethodElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for method";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	if ( Error )
	{
		
		delete MethodElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	LOG_VERBOSE ( "+H" );
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = MethodElement;
	
}

void OakMethodDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
