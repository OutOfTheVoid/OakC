#include <Parsing/Language/OakEnumConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>
#include <Parsing/Language/OakEnumBranchConstructor.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>

#ifndef NULL
	#define NULL nullptr
#endif

#include <Utils/GlobalSingleton.h>

OakEnumConstructor & OakEnumConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakEnumConstructor> ();
	
}

OakEnumConstructor :: OakEnumConstructor ():
	TemplateGroup ( { { & ( OakTemplateDefinitionConstructor :: Instance () ), 0 } } ),
	EnumBodyGroup ( { { & ( OakEnumBranchConstructor :: Instance () ), 0 } } )
{
}

OakEnumConstructor :: ~OakEnumConstructor ()
{
}

void OakEnumConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Enum ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Ident ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected identifier for enum name";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	ElementData * EnumData = new ElementData ();
	
	EnumData -> Name = CurrentToken -> GetSource ();
	
	ASTElement * EnumElement = new ASTElement ();
	
	EnumElement -> SetTag ( OakASTTags :: kASTTag_Enum );
	EnumElement -> AddTokenSection ( & Input.Tokens [ 0 ], 2 );
	EnumElement -> SetData ( EnumData, & ElementDataDestructor );
	
	bool Error = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 2;
	
	if ( TemplateGroup.TryConstruction ( EnumElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ 2 ], TokenCount ) != 0 )
	{
		
		EnumData -> Templated = true;
		
		ASTElement * TemplateElement = EnumElement -> GetSubElement ( EnumElement -> GetSubElementCount () - 1 );
		
		if ( reinterpret_cast <OakTemplateDefinitionConstructor :: ElementData *> ( TemplateElement -> GetData () ) -> DoubleTemplateClose || reinterpret_cast <OakTemplateDefinitionConstructor :: ElementData *> ( TemplateElement -> GetData () ) -> TripleTemplateClose )
		{
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Unexpected closing triangle bracket after end of template definition";
			Output.ErrorProvokingToken = TemplateElement -> GetToken ( TemplateElement -> GetTokenSectionCount () - 1, TemplateElement -> GetTokenCount ( TemplateElement -> GetTokenSectionCount () - 1 ) - 1 );
			
			delete EnumElement;
			
			return;
			
		}
		
	}
	else if ( Error )
	{
		
		delete EnumElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	else
		EnumData -> Templated = false;
	
	if ( TokenCount < 2 )
	{
		
		delete EnumElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for enum definition";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Open )
	{
		
		delete EnumElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected body for enum definition";
		Output.ErrorProvokingToken = NULL;
		
		return;
		
	}
	
	EnumElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	if ( TokenCount == 0 )
	{
		
		delete EnumElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of enum body";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	Error = false;
	ErrorString = "";
	ErrorToken = NULL;
	
	while ( EnumBodyGroup.TryConstruction ( EnumElement, 1, Error, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) != 0 )
	{
		
		if ( Error )
		{
			
			delete EnumElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
		if ( TokenCount == 0 )
		{
			
			delete EnumElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing curly bracket at end of enum body";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
		CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Comma )
			break;
			
		TokenCount --;
		
		if ( TokenCount == 0 )
		{
			
			delete EnumElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = "Expected closing curly bracket at end of enum body";
			Output.ErrorProvokingToken = CurrentToken;
			
			return;
			
		}
		
	}
	
	if ( Error )
	{
		
		delete EnumElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_CurlyBracket_Close )
	{
		
		delete EnumElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected closing curly bracket at end of enum body";
		Output.ErrorProvokingToken = Input.Tokens [ Input.AvailableTokenCount - TokenCount ];
		
		return;
		
	}
	
	EnumElement -> AddTokenSection ( & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], 1 );
	
	TokenCount --;
	
	Output.Accepted = true;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	Output.ConstructedElement = EnumElement;
	
}

void OakEnumConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <OakEnumConstructor :: ElementData *> ( Data );
	
}
