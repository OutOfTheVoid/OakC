#include <Parsing/Language/OakImportStatementConstructor.h>
#include <Parsing/Language/OakASTTags.h>
#include <Parsing/Language/OakParsingUtils.h>

#include <Parsing/ASTElement.h>

#include <Lexing/Language/OakKeywordTokenTags.h>

#include <Tokenization/Language/OakTokenTags.h>
#include <Tokenization/Token.h>

#include <Utils/GlobalSingleton.h>

OakImportStatementConstructor & OakImportStatementConstructor :: Instance ()
{
	
	return GetGlobalSingleton <OakImportStatementConstructor> ();
	
}

OakImportStatementConstructor :: OakImportStatementConstructor ()
{	
}

OakImportStatementConstructor :: ~OakImportStatementConstructor ()
{
}

void OakImportStatementConstructor :: TryConstruct ( ASTConstructionInput & Input, ASTConstructionOutput & Output ) const
{
	
	if ( Input.AvailableTokenCount < 3 )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	const Token * CurrentToken = Input.Tokens [ 0 ];
	
	if ( ! OakParsingUtils :: KeywordCheck ( CurrentToken, OakKeywordTokenTags :: kKeywordAuxTags_Import ) )
	{
		
		Output.Accepted = false;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 1 ];
	uint64_t Tag = CurrentToken -> GetTag ();
	
	if ( ! ( ( Tag == OakTokenTags :: kTokenTag_StringLiteralDefault ) || ( Tag == OakTokenTags :: kTokenTag_StringLiteralu8 ) || ( Tag == OakTokenTags :: kTokenTag_StringLiteralu16 ) || ( Tag == OakTokenTags :: kTokenTag_StringLiteralu32 ) ) )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected filename string after import keyword";
		Output.ErrorProvokingToken = CurrentToken;
		
		return;
		
	}
	
	CurrentToken = Input.Tokens [ 2 ];
	
	if ( CurrentToken -> GetTag () != OakTokenTags :: kTokenTag_Semicolon )
	{
		
		Output.Accepted = false;
		Output.Error = true;
		Output.ErrorSuggestion = "Expected semicolon after import statement";
		Output.ErrorProvokingToken = CurrentToken;
		
	}
	
	ElementData * ImportData = new ElementData ();
	
	ImportData -> ImportFilenameLiteral = Input.Tokens [ 1 ] -> GetSource ();
	ImportData -> StringLiteralTag = Input.Tokens [ 1 ] -> GetTag ();
	
	ASTElement * ImportElement = new ASTElement ();
	
	ImportElement -> AddTokenSection ( & Input.Tokens [ 0 ], 3 );
	ImportElement -> SetTag ( OakASTTags :: kASTTag_ImportStatement );
	ImportElement -> SetData ( ImportData, & ElementDataDestructor );
	
	Output.Accepted = true;
	Output.TokensConsumed = 3;
	Output.ConstructedElement = ImportElement;
	
}

void OakImportStatementConstructor :: ElementDataDestructor ( void * Data )
{
	
	delete reinterpret_cast <ElementData *> ( Data );
	
}
