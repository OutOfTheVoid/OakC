#include <Parsing/Language/OakMethodDefinitionConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakMethodParameterListConstructor.h>
#include <Parsing/Language/OakReturnTypeConstructor.h>
#include <Parsing/Language/OakStatementBlockConstructor.h>
#include <Parsing/Language/OakTemplateDefinitionConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#include <Logging/Logging.h>

OakMethodDefinitionConstructor OakMethodDefinitionConstructor :: Instance;

ASTConstructionGroup :: StaticInitEntry _OakMethodDefinitionConstructor_TemplateConstructionGroupEntries [] = { { & OakTemplateDefinitionConstructor :: Instance, 0 } };
ASTConstructionGroup :: StaticInitEntry _OakMethodDefinitionConstructor_ParameterListConstructionEntries [] = { { & OakMethodParameterListConstructor :: Instance, 0 } };
ASTConstructionGroup :: StaticInitEntry _OakMethodDefinitionConstructor_ReturnTypeConstructionEntries [] = { { & OakReturnTypeConstructor :: Instance, 0 } };
ASTConstructionGroup :: StaticInitEntry _OakMethodDefinitionConstructor_BodyConstructionGroupEntries [] = { { & OakStatementBlockConstructor :: Instance, 0 } };

OakMethodDefinitionConstructor :: OakMethodDefinitionConstructor ():
	TemplateConstructionGroup ( _OakMethodDefinitionConstructor_TemplateConstructionGroupEntries, 1 ),
	ParameterListConstructionGroup ( _OakMethodDefinitionConstructor_ParameterListConstructionEntries, 1 ),
	ReturnTypeConstructionGroup ( _OakMethodDefinitionConstructor_ReturnTypeConstructionEntries, 1 ),
	BodyConstructionGroup ( _OakMethodDefinitionConstructor_BodyConstructionGroupEntries, 1 )
{
}

OakMethodDefinitionConstructor :: ~OakMethodDefinitionConstructor ()
{
}

void OakMethodDefinitionConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
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
	
	ElementData * MethodData = new ElementData ();
	
	MethodData -> Name = CurrentToken -> GetSource ();
	MethodData -> ReturnTyped = false;
	MethodData -> Templated = false;
	MethodData -> Public = Public;
	MethodData -> Inline = Inline;
	
	ASTElement * MethodElement = new ASTElement ();
	
	MethodElement -> SetTag ( OakASTTags :: kASTTag_MethodDefinition );
	MethodElement -> AddTokenSection ( & Input.Tokens [ 0 ], Offset );
	MethodElement -> SetData ( MethodData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - Offset;
	
	if ( TemplateConstructionGroup.TryConstruction ( MethodElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Offset ], TokenCount ) != 0 )
	{
		
		if ( Error )
		{
			
			delete MethodElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
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
		
		if ( TokenCount < 3 )
		{
			
			delete MethodElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected body for method definition";
			Output.ErrorProvokingToken = NULL;
			
			return;
			
		}
		
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
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = MethodElement;
	
}

void OakMethodDefinitionConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
