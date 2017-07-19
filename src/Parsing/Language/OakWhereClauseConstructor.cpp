#include <Parsing/Language/OakWhereClauseConstructor.h>
#include <Parsing/Language/OakParsingUtils.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Parsing/Language/OakTemplateDefinitionConstructor.h>

#include <Utils/GlobalSingleton.h>

OakWhereClauseConstructor & OakWhereClauseConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakWhereClauseConstructor> ();
	
}


OakWhereClauseConstructor :: OakWhereClauseConstructor ():
	TemplateGroup ( { { & ( OakTemplateDefinitionConstructor :: Instance () ), 0 } } )
{
}

OakWhereClauseConstructor :: ~OakWhereClauseConstructor ()
{
}

void OakWhereClauseConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 4 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Where ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	ASTElement * WhereElement = new ASTElement ();
	
	WhereElement -> SetTag ( OakASTTags :: kASTTag_WhereClause );
	WhereElement -> AddTokenSection ( & Input.Tokens [ 0 ], 1 );
	
	bool ConstructionError = false;
	std :: string ErrorString;
	const Token * ErrorToken = NULL;
	uint64_t TokenCount = Input.AvailableTokenCount - 1;
	
	if ( TemplateGroup.TryConstruction ( WhereElement, 1, ConstructionError, ErrorString, ErrorToken, & Input.Tokens [ Input.AvailableTokenCount - TokenCount ], TokenCount ) == 0 )
	{
		
		if ( ConstructionError )
		{
			
			delete WhereElement;
			
			Output.Accepted = false;
			Output.Error = true;
			Output.ErrorSuggestion = ErrorString;
			Output.ErrorProvokingToken = ErrorToken;
			
			return;
			
		}
		
	}
	
	if ( ConstructionError )
	{
		
		delete WhereElement;
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = ErrorString;
		Output.ErrorProvokingToken = ErrorToken;
		
		return;
		
	}
	
	Output.Accepted = true;
	Output.ConstructedElement = WhereElement;
	Output.TokensConsumed = Input.AvailableTokenCount - TokenCount;
	
}
